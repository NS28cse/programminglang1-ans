# BugBackupScores　点数の控え（第13回）

ソース: [scores.h](scores.h)，[scores.c](scores.c)，[main.c](main.c)

> [!IMPORTANT]
> この題材の誤りは**未定義動作**（解放後の使用と二重解放）で，表示される値や止まり方は環境・構成・実行ごとに変わる。下の症状は Debug 構成の MSVC と，Linux の GCC で確かめたもの。

## 対象の回と前提

- 第13回（メモリ管理）。講義 7.1「動的なメンバを持つ場合」（「構造体を代入してもポインタメンバの参照先まではコピーされません」）と，課題2 の「追加：独立したコピー」（`DynamicCopy`）の後。
- 学生が知っていること: `malloc`・`calloc`・`free`，構造体の代入，ポインタメンバ，所有者の考え方，分割コンパイル（第12回），ブレークポイント（F9）・F5・F10・**Locals**・**Watch 1**（第13回の演習）。
  ステップイン（F11）は授業では未習（第14回の講義）。
- 入力も引数もない。

## プログラムがするはずのこと

今日の点数 `today`（70・85・90）の控え `backup` を作る。`today` を解放した後も `backup` は使えるようにし，`backup` の点数と平均を表示してから `backup` も解放する。期待する表示:

```text
backup: 70 85 90
mean=81.7
```

## 症状

**Startup Item** で `debugging BugBackupScores` を選び，Ctrl+F5 で実行する。

- Debug 構成の MSVC: 解放した領域は Debug の C ランタイムが 0xDD で埋めるので，`backup: -572662307 -572662307 -572662307` のように 0xDDDDDDDD を `int` として読んだ値が出ることが多い。続く 2 回目の `free` で **Debug Assertion Failed!** のダイアログ（式は `_CrtIsValidHeapPointer(block)` など）が出て止まることが多い。
- Linux の GCC（Debug，サニタイザーなし）: 意味のない値が表示され，2 回目の `free` で異常終了する（終了コード 134）。値は実行ごとに変わる:

  ```text
  backup: 1591166219 5 -541139842
  mean=350008794.0
  free(): double free detected in tcache 2
  ```

- AddressSanitizer 付き（`-DSOFTPRAC_SANITIZE=ON`）: 解放後の最初の読み取りで止まる。

  ```text
  ==...==ERROR: AddressSanitizer: heap-use-after-free on address ...
  READ of size 4 at ... thread T0
      #0 ... in scores_print .../scores.c:31
      #1 ... in main .../main.c:22
  ```

未定義動作なので，バグ入りの版は自動テストで実行しない（直した版だけをテストする）。

## 学生への渡し方

- 渡すもの: `scores.h`・`scores.c`・`main.c` の 3 ファイル（空のプロジェクトに 3 つとも追加する）。
- 最初に言うこと: 「点数の控えを作ってから元を解放し，控えを表示するプログラムです。70 85 90 のはずが，意味のない値が出て，最後にエラーで止まります。`today` と `backup` がそれぞれどの領域を指しているかを確かめてください」
- 言わないこと: 構造体の代入がポインタだけをコピーすること。

## 探し方

1. **症状から範囲を絞る**: 値が壊れているのは表示の時点。表示の前に `today` を解放しているので，「`backup` は解放された領域を読んでいるのでは」と見当を付ける。
2. **代入の直後で止める**: `scores_destroy(&today);` の行に F9，F5。**Locals** で `today` と `backup` を展開し，`data` の値（アドレス）を比べる。同じアドレスで，指す先の値も同じ `{70}`。
3. **仮説**: 「`Scores backup = today;` は構造体のメンバをコピーするだけで，`data` が指す配列はコピーされない。`today` と `backup` は 1 つの配列を共有している」。
4. **確かめる**: F10 で `scores_destroy(&today);` を実行する。**Locals** で `today.data` は `0x0000000000000000`（`NULL`）になるが，`backup.data` は古いアドレスのまま。**Debug > Windows > Watch > Watch 1** に `backup.data[0]` と書くと，`free` の後の値（Debug 構成の MSVC では `-572662307` が多い）に変わっている。
5. **所有者を図にする**: `today` → [70 85 90] ← `backup` の図を描かせ，「この配列の所有者は何人？ 何回 `free` される？」と聞く（2 人のつもりで 2 回 → 二重解放）。

## ヒントの段階

1. 「`Scores backup = today;` の直後，`today.data` と `backup.data` のアドレスは？」
2. 「`scores_destroy(&today);` の後，`backup.data` が指す先はまだ使ってよい？」
3. 「この配列を `free` しているのは何回？」

## 原因

構造体の代入 `Scores backup = today;` は `count` と `data`（アドレス）をコピーするだけで，`data` が指す配列はコピーしない（講義 7.1）。`today` と `backup` が同じ配列を指したまま `scores_destroy(&today)` で配列を解放するので，`backup` の表示は**解放後の使用**，最後の `scores_destroy(&backup)` は同じ領域の**二重解放**になる。
`scores_destroy` は `today.data` を `NULL` にするが，コピーである `backup.data` は変わらない（講義 4 節，第13回の手引きの問い「`int *b = a; free(a); a = NULL;` の後，`b` も `NULL` になる？」と同じ）。
解放と読み取りが別のファイル（`scores.c`）の関数で起きるので，コンパイラの警告では見つからない。

## 直し方

`backup` に別の配列を確保し，中身をコピーする（独立したコピー）。

```diff
-    Scores backup = today;
+    Scores backup;
+    if (!scores_create(&backup, today.count)) {
+        fprintf(stderr, "allocation failed\n");
+        scores_destroy(&today);
+        return 1;
+    }
+    for (size_t i = 0; i < today.count; ++i) {
+        backup.data[i] = today.data[i];
+    }
     scores_destroy(&today);
```

確保に失敗したときも `today` を解放してから終わる。直した版は `backup: 70 85 90` と `mean=81.7` を表示する（テスト `variant_fixed`）。
控えを独立させる必要がなければ，`today` を解放せずに `backup` という別名で使う（所有者は 1 人のまま，解放も 1 回）設計もある。どちらにするかは「所有権の移動・借用・独立したコピーのどれか」を決めること（講義 7.1）。

## 学生への問い

- 問「Debug 構成の MSVC で `-572662307` が出たら，何を疑う？」→ 0xDDDDDDDD なので，解放した領域を読んでいる。0xCDCDCDCD（`-842150451`）なら `malloc` した後に初期化していない領域，0xCCCCCCCC（`-858993460`）なら初期化していない局所変数。
- 問「`scores_destroy(&backup);` を消せば直る？」→ 二重解放は消えるが，解放後の使用は残る（表示が壊れたまま）。原因は共有なので，コピーするか所有者を 1 人にする。
- 問「`backup = today;` の後で `today.data[0] = 0;` としたら，`backup.data[0]` は？」→ 0 になる。同じ配列を共有しているから。解放しなくても，控えとして役に立たない。

## 関連

- [第13回 README](../../week13/README.md) の「課題2　配列を逆順にする」（「追加：独立したコピー（`DynamicCopy`）」），「課題4　コードレビュー」（「所有者を図にする」）
- [第11回 README](../../week11/README.md) の「課題4　配列メンバとポインタメンバを比較する（`CopyMembers`）」
- [practice/README.md](../../practice/README.md) の「第13回　所有者と失敗経路」，「どの回でも使う型」の「AddressSanitizer」
