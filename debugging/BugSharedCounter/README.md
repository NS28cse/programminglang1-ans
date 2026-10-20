# BugSharedCounter　呼び出し回数を数える（第12回）

ソース: [counter.h](counter.h)，[counter.c](counter.c)，[main.c](main.c)

## 対象の回と前提

- 第12回（コンパイル：分割コンパイルとライブラリ）。講義 6 節「`static`と`extern`」の後。課題3 のリンクエラー（LNK2005：同じ定義が 2 つ）を経験した後に向く。
- 学生が知っていること: ヘッダに宣言・`.c` に定義を置く分割，インクルードガード，翻訳単位，`static` と `extern`，ブレークポイント（F9）・F5・F10・**Locals**。
  ステップイン（F11）と **Watch 1** は授業では未習（第14回の講義・第13回の演習で扱う操作）。
- 入力も引数もない。

## プログラムがするはずのこと

`count_call` を呼ぶたびに呼び出し回数 `call_count` を 1 増やす。`main` は `count_call` を 3 回呼んでから回数を表示する。

```text
calls=3
```

## 症状

**Startup Item** で `debugging BugSharedCounter` を選び，Ctrl+F5 で実行する。

```text
calls=0
```

ビルドは警告もエラーもなく成功する（テスト `debugging/BugSharedCounter/symptom`）。

## 学生への渡し方

- 渡すもの: `counter.h`・`counter.c`・`main.c` の 3 ファイル（空のプロジェクトに 3 つとも追加する）。
- 最初に言うこと: 「`count_call` を 3 回呼んで `calls=3` と出るはずですが，Ctrl+F5 で実行すると `calls=0` と出ます。原因をデバッガで探してください」
- 言わないこと: `static` の意味，`extern`。

## 探し方

1. **範囲を 2 つに分ける**: 「`count_call` が呼ばれていない」「呼ばれて増えているが，`main` が別のものを読んでいる」のどちらか。
2. **関数の中で止める**: `counter.c` の `++call_count;` の行に F9，F5。3 回止まることで，呼ばれていることが分かる。3 回目に止まったら F10 を 1 回押し，コードの `call_count` にマウスポインターを重ねて（データヒント（DataTip）。授業では未習）値が 3 になることを見る。`call_count` は関数の外の変数なので **Locals** には出ない（**Debug > Windows > Autos** には出る）。
3. **呼び出し元で見る**: `main.c` の `printf` の行に F9 を置いて F5。ここで `call_count` にマウスポインターを重ねると 0。
4. **仮説**: 「`counter.c` の `call_count` と `main.c` の `call_count` は別の変数。ヘッダの `static int call_count = 0;` が，インクルードした `.c` ごとに 1 つずつ別の変数を作っている」。
5. **確かめる**: **Debug > Windows > Watch > Watch 1**（授業では未習）に `&call_count` を書き，`counter.c` で止まったときと `main.c` で止まったときのアドレスが違うことを見る。
   ウォッチを使わない場合は，「`#include` はヘッダの中身をその場に貼り付ける」ことから，`counter.c` と `main.c` にそれぞれ `static int call_count = 0;` が書かれたのと同じだと説明させる（講義 6 節：`static` は名前を他の翻訳単位から参照させない）。

## ヒントの段階

1. 「`count_call` の中で，`call_count` は 1，2，3 と増えている？」
2. 「`counter.c` の `call_count` と `main.c` の `call_count` は，同じ変数？」
3. 「`#include "counter.h"` は何をする？ `static` を付けたファイルスコープの変数は，ほかの `.c` から見える？」

## 原因

ヘッダの `static int call_count = 0;` は，`#include` した翻訳単位（`counter.c` と `main.c`）ごとに，その中だけで使える別々の変数を定義する。`count_call` が増やすのは `counter.c` の `call_count`，`main` が表示するのは `main.c` の `call_count`（0 のまま）。
`static` を外して `int call_count = 0;` にすると定義が 2 つになり，リンクエラー（MSVC では LNK2005：定義済み）になる。このリンクエラーを `static` を付けて消すのは学生がしがちな対処で，ビルドは通るが共有もされなくなる。共有変数は，ヘッダに `extern` の宣言，定義は 1 つの `.c` だけに置く（講義 6 節）。

## 直し方

```diff
 // counter.h
-static int call_count = 0;
+extern int call_count;
```

```diff
 // counter.c
 #include "counter.h"
 
+int call_count = 0;
+
 void count_call(void)
```

`main.c` は変えない。直した版は `calls=3` を表示する（テスト `variant_fixed`）。
共有する変数を減らすなら，`call_count` を `counter.c` の `static` 変数にして，回数を返す関数（`int call_count_get(void)` など）だけをヘッダで公開する設計もある（講義 6 節の最後）。

## 学生への問い

- 問「リンクエラーを `static` で消したことの何が問題だった？」→ エラーの原因（定義が 2 つ）を直さず，別々の変数にしてしまったこと。エラーが消えたことは，意図どおりに共有されたことを意味しない。
- 問「`extern int call_count;` だけで定義がないとどうなる？」→ リンクエラー（MSVC では LNK2019：未解決の外部シンボル）。
- 問「関数の中の `static int count;` とファイルスコープの `static int count;` は同じ意味？」→ 違う。関数の中は「呼び出しをまたいで値を保つ」，ファイルスコープは「他の翻訳単位から名前を見えなくする」（講義 6 節）。

## 関連

- [題材の一覧と渡し方の共通ルール](../README.md)
- 第12回 README の [課題3　リンクエラーを調べる](../../week12/README.md#課題3リンクエラーを調べるsplitcalc-と-builderrorssplit)（[エラーの比較（表の解答）](../../week12/README.md#エラーの比較表の解答)）
- 第13回 README の [発展2　`static`変数の寿命を確かめる](../../week13/README.md#発展2static変数の寿命を確かめるstoragecount--countcsharedcount--mainccounterccounterh) の [第12回との接続：共有変数の宣言（`SharedCount`）](../../week13/README.md#第12回との接続共有変数の宣言sharedcount)
- 実務の手引きの [第12回　コンパイルとリンクを分けて考える](../../ta-guide/README.md#第12回コンパイルとリンクを分けて考えるコンパイル)
