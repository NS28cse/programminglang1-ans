# BugFindMax　最大の要素の場所を返す（第9回）

ソース: [find_max.c](find_max.c)

## 対象の回と前提

- 第9回（ポインタ2）。講義 1 節「関数に渡す星の数を決める」と，課題1 `FindMax`（講義の `find_max(int a[], int n, int **out)`）の後。
- 学生が知っていること: ポインタの値渡し（第8回の `swap`），二重ポインタ，ブレークポイント（F9）・F5・F10・**Locals**。
  ステップイン（F11）・**Watch 1**・**Call Stack** は授業では未習（実務の手引きの第8回で先取りして見せる操作）。
- 入力も引数もない。

## プログラムがするはずのこと

`find_max` は配列の最大の要素の場所を呼び出し元のポインタ変数 `best` へ書き，成功なら 1 を返す。`main` は最大の点数とその添字を表示する。点数 `{72, 85, 60, 93, 80}` なら:

```text
max=93 index=3
```

## 症状

**Startup Item** で `debugging BugFindMax` を選び，Ctrl+F5 で実行する。

```text
max=72 index=0
```

先頭の要素のまま変わらない（テスト `debugging/BugFindMax/symptom`）。

## 学生への渡し方

- 渡すもの: `find_max.c` だけ。
- 最初に言うこと: 「最大の点数とその添字を表示するプログラムです。`max=93 index=3` と出るはずですが，Ctrl+F5 で実行すると `max=72 index=0` と出ます。原因をデバッガで探してください」
- 言わないこと: 星の数・`int **`。

## 探し方

1. **範囲を 2 つに分ける**: 「関数の中で探し間違えている」のか「関数の中では正しいが，結果が `main` に伝わらない」のかを分ける。
2. **関数の終わりで止める**: `find_max` の `return 1;` の行に F9，F5。**Locals** の `out` の値の欄に，指す先の値 `{93}` が出る（アドレスの後ろ）。関数の中では 93 の場所を指している。
3. **呼び出し元へ戻って比べる**: F10 を数回押して `main` へ戻る（または `printf` の行にもブレークポイントを置いて F5）。**Locals** の `best` は `{72}` で，`scores` の先頭のアドレスのまま。
4. **仮説**: 「`find_max` が書き換えたのは仮引数 `out`（`best` の値のコピー）で，`main` の `best` そのものではない」。
5. **確かめる**: `main` の `if (find_max(scores, COUNT, best)) {` の行で止め，**Debug > Windows > Watch > Watch 1**（授業では未習）に `&best` を書いて値（`best` のアドレス）をメモする。F11（**Debug > Step Into**。授業では未習）で `find_max` に入ったら，**Watch 1** に `&out` を書いてメモと比べる（違うアドレス = 別の変数。`find_max` の中では `best` は見えない）。`find_max` の中で **Debug > Windows > Call Stack** の `main` の行をダブルクリックすれば，`main` の `&best` を見ることもできる。第8回の `swap` の「`a = b` ではポインタのコピーを入れ替えるだけ」と同じ形であることを言わせる。

## ヒントの段階

1. 「`find_max` の中では正しく見つかっている？ `return 1;` の直前で `out` は何を指している？ 戻った後の `best` は？」
2. 「`out` と `best` は同じ変数？ `out` は何のコピー？」
3. 「`main` の `int` 変数を関数で書き換えるときは何を渡した？ では `main` の `int *` 変数を書き換えるには？」

## 原因

C の引数は値渡しなので，`find_max(scores, COUNT, best)` は `best` の値（アドレス）を仮引数 `out` にコピーして渡す。`out = &a[i];` は `out` というコピーを書き換えるだけで，`main` の `best` は先頭を指したまま。
呼び出し元のポインタ変数を書き換えるには，その変数の場所 `&best`（型 `int **`）を渡し，`*out = &a[i];` と書く（講義 1 節「関数に渡す星の数を決める」）。
型はどこも一致しているので，コンパイラは警告を出さない。`best` を `&scores[0]` で初期化していたので，誤りが異常終了ではなく「先頭のまま」として現れた（`NULL` で初期化していたら `*best` で止まる）。

## 直し方

```diff
-int find_max(int a[], int n, int *out)
+int find_max(int a[], int n, int **out)
 {
     if (n <= 0) {
         return 0;
     }
-    out = &a[0];
+    *out = &a[0];
     for (int i = 1; i < n; ++i) {
-        if (a[i] > *out) {
-            out = &a[i];
+        if (a[i] > **out) {
+            *out = &a[i];
         }
     }
     return 1;
 }
```

```diff
-    if (find_max(scores, COUNT, best)) {
+    if (find_max(scores, COUNT, &best)) {
```

直した版は `max=93 index=3` を表示する（テスト `variant_fixed`）。

## 学生への問い

- 問「誤りの版の `find_max` の先頭に `*out = 0;` と書いたら，何が 0 になる？」→ `out` が指す `scores[0]`。`int *` を受け取れば指す先の `int` は書き換えられるが，`main` のポインタ変数そのものは書き換えられない。
- 問「`best` を `NULL` で初期化していたら，誤りの版はどうなった？」→ `*best` で `NULL` をたどり，異常終了する（アクセス違反）。誤りは同じでも，初期値で症状が変わる。
- 問「最大値の場所ではなく値だけが欲しいなら？」→ 値を戻り値で返せばよく，二重ポインタは要らない（第9回 `ReturnMaximum`）。

## 関連

- [題材の一覧と渡し方の共通ルール](../README.md)
- [第9回 README](../../week09/README.md) の「課題1　見つからない場合（`FindMax`）」（「二重ポインタの代入を追う」，「値を返す版と，場所を返す版（`ReturnMaximum`）」）
- [第8回 README](../../week08/README.md) の「課題1　`swap`を追う」（「説明すること：`*a = *b` を `a = b` に変えても交換にならない理由」）
- [実務の手引き](../../ta-guide/README.md) の「第8回　Step Into とウォッチでポインタを見る」，「第9回　実験の前に commit，後で差分」
