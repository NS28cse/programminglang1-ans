# BugMallocSize　動的配列（第13回）

ソース: [dynamic.c](dynamic.c)，既定の引数: [run.args](run.args)（`5`）

> [!IMPORTANT]
> この題材の誤りは**未定義動作**（確保した領域の外への書き込み）で，症状は環境・構成・引数で変わる。下の MSVC の症状は，Debug 構成の検査（デバッグヒープ）の仕様から通常見られるもの（授業の前に TA が手元で一度確かめる）。Linux の症状は GCC で実際に実行したもの。
> 「`n = 5` では正しく表示される」こと自体が，この題材で見せたい点の 1 つ。

## 対象の回と前提

- 第13回（メモリ管理）。講義 2 節「個数とバイト数」（「`malloc`の引数は要素数ではなく**バイト数**」）と，課題1 `Dynamic` の後。
- 学生が知っていること: `malloc`・`free`・`sizeof`，`strtol` による引数の検査（第10回），ブレークポイント（F9）・F5・F10・**Locals**，**Watch 1**（第13回 発展3。発展をしていない学生には未習）。
- 引数で個数を受け取る（**Command Arguments**）。

## プログラムがするはずのこと

引数の個数 `n`（1〜1000）だけ `int` を動的に確保し，1〜`n` を書き込んで，各要素と合計を表示してから解放する。引数 `5` なら:

```text
values: 1 2 3 4 5
sum=15
```

## 症状

**Startup Item** で `debugging BugMallocSize  [5]` を選び，Ctrl+F5 で実行する。

- Debug 構成の MSVC: 期待どおりの 2 行が表示された後，`free` のところで **Microsoft Visual C++ Runtime Library** の **Debug Error!** のダイアログが出て（Debug 構成の既定の設定），**HEAP CORRUPTION DETECTED: after Normal block (#…) at 0x…** と **CRT detected that the application wrote to memory after end of heap buffer.** と表示される（F5 で実行した場合も同じ文面で止まる）。
- Linux の GCC（Debug，サニタイザーなし）: 引数 `5` では期待どおりに表示して正常に終わり，誤りが見えない。引数 `1000` では何も表示せずに異常終了する（終了コード 134）:

  ```text
  malloc(): corrupted top size
  ```

- AddressSanitizer 付き（`-DSOFTPRAC_SANITIZE=ON`）: 確保した 5 バイトの外へ初めて書く 2 回目の書き込み（`values[1]`。領域の先頭から 4 バイト進んだ位置（オフセット 4）から 4 バイト書き，5 バイトの領域を越える）で止まる（引数 `1` なら 1 回目の `values[0]`）。

  ```text
  ==...==ERROR: AddressSanitizer: heap-buffer-overflow on address ... 
  WRITE of size 4 at ... thread T0
      #0 ... in main .../dynamic.c:31
  ...
  ... is located 0 bytes after 5-byte region [...)
  ```

未定義動作なので，バグ入りの版は自動テストで実行しない（直した版だけをテストする）。

## 学生への渡し方

- 渡すもの: `dynamic.c` だけ。**Command Arguments** を `5` にし，Debug 構成で実行するように言う。
- 最初に言うこと: 「**Command Arguments** を `5` にして Debug 構成で Ctrl+F5 で実行すると，`values: 1 2 3 4 5` と `sum=15` が出て正常に終わるはずですが，表示の後でヒープが壊れたというダイアログが出ます。原因をデバッガで探してください」
- 言わないこと: `malloc(n)` の引数。

## 探し方

1. **ダイアログを読む**: 「ヒープの領域（`malloc` で確保した領域）の**終わりより後ろ**に書いた」と言っている。検出されたのは `free` のときだが，書いたのはその前（Debug の C ランタイムは，確保した領域の後ろの 4 バイトが書き換えられていないかを `free` のときに調べる）。範囲は「`values` へ書き込む行」に絞れる。
2. **境界の引数で比べる**: 引数を `1` にしても出ることを確かめる（1 要素でも足りない）。
3. **止めて値を見る**: `malloc` の次の行（`if (values == NULL)`）に F9，F5。**Locals** で `n` が 5 であることを見て，「`malloc(n)` は何バイト確保した？」と聞く（5 バイト）。**Debug > Windows > Watch > Watch 1**（第13回 発展3。発展をしていない学生には未習）に `n * sizeof *values` と書くと 20（`int` が 4 バイトの環境）。
4. **仮説**: 「`int` を 5 個入れるには 20 バイト必要なのに，5 バイトしか確保していない。`values[1]` 以降は確保した領域の外」。
5. **確かめる**: **Watch 1** に `values,5` と書き（「,要素数」で配列として表示する書式指定子。授業資料にはなく未習。[実務の手引きの第5回](../../ta-guide/README.md#第5回読みやすいコードと関数の契約配列と関数)の「デバッグの補足」），書き込みのループを F10 で進める。余裕があれば **Debug > Windows > Memory > Memory 1**（授業では未習）の **Address** に `values` と入れ，確保直後は 5 バイトの CD の後ろに FD が 4 バイト並び，ループの後はその FD が書き換えられていることを見せる。

## ヒントの段階

1. 「ダイアログの **after Normal block** は，どの領域の後ろ？ その領域に書き込んでいる行はどれ？」
2. 「`values` には全部で何バイト書き込む？（**Watch 1** に `n * sizeof *values`）」
3. 「`malloc(n)` は何バイト確保する？ `malloc` の引数は個数とバイト数のどちら？」

## 原因

`malloc` の引数はバイト数なので，`malloc(n)` は `n` バイトしか確保しない。`int` が 4 バイトの環境では，`n` 個の `int` に `n * sizeof *values` バイト必要で，`values[1]` 以降（`n` = 1 でも `values[0]` の 2 バイト目以降）は確保した領域の外になる（講義 2 節「個数とバイト数」）。
範囲外の書き込みは未定義動作で，すぐ後ろの領域がたまたま使われていなければ表示は正しく見える（glibc の `malloc` は小さい確保でも 24 バイトほど使える領域を返すので，`n = 5` では壊れたことが表に出ない）。`n` は実行時の引数で決まるので，コンパイラの警告では見つからない。

## 直し方

```diff
-    int *values = malloc(n);
+    int *values = malloc(n * sizeof *values);
```

`n` は 1〜1000 に検査済みなので，掛け算はあふれない（`n` に上限がない場合は，課題1 `Dynamic` のように `n > SIZE_MAX / sizeof *values` を先に調べる）。直した版は `5`・`1`・`1000`・`0`（エラー）を確かめている（テスト `variant_fixed--*`）。

## 学生への問い

- 問「Linux で `n = 5` を試したら正しく動いた。それでも誤り？」→ 誤り。範囲外の書き込みは未定義動作で，壊した場所がたまたま使われていないだけ。Linux の GCC（Debug）では引数 6 以下は正常に終わり，7 以上で glibc が壊れたことを検出して異常終了する。「`n = 5` で正しく見える」ことは「正しい」ことの根拠にならない。
- 問「`malloc(n * sizeof(int *))` と書いたら？」→ x64 ではポインタが 8 バイトなので確保しすぎになる（範囲外にはならないが誤り）。`sizeof *values` なら要素の型に追従する（講義 2 節）。
- 問「Debug 構成でダイアログが出るのはどの行？ 書き込んだ行で止まらないのはなぜ？」→ `free` の行。Debug の C ランタイムは書き込みのたびには調べず，解放のときに領域の後ろが書き換えられていないかを調べるから。

## 関連

- [題材の一覧と渡し方の共通ルール](../README.md)
- 第13回 README の [課題1　動的配列](../../week13/README.md#課題1動的配列dynamic--dynamicc)（[確保量を説明する](../../week13/README.md#確保量を説明する)）
- 実務の手引きの [第13回　所有者と失敗経路](../../ta-guide/README.md#第13回所有者と失敗経路メモリ管理)（「デバッグの補足」の 0xCD・0xFD），[どの回でも使う型](../../ta-guide/README.md#どの回でも使う型) の [AddressSanitizer](../../ta-guide/README.md#addresssanitizer範囲外アクセスと解放後の使用を実行時に見つける)
