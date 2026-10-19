# BugUpper　大文字にして写す（第7回）

ソース: [upper.c](upper.c)

## 対象の回と前提

- 第7回（入出力）。講義 2 節「1文字ずつ読む」（`getchar`・`putchar`・`EOF`）と，課題1 `Echo`・`LowerInput`（小文字化フィルタ）の後。
- 学生が知っていること: `getchar` は呼ぶたびに次の 1 文字を読むこと，`EOF` と入力終了（Windows は行頭で Ctrl+Z → Enter），ブレークポイント（F9）・F5・F10・**Locals**。
- 標準入力を使う（引数・ファイルはない）。

## プログラムがするはずのこと

標準入力を `EOF` まで 1 文字ずつ読み，英小文字は大文字に，それ以外はそのまま表示する。`hello` と入力して Enter を押したら `HELLO` と表示されるはず。

## 症状

**Startup Item** で `debugging BugUpper` を選び，Ctrl+F5 で実行する。コンソールに `hello` と入力して Enter，続けて行頭で Ctrl+Z → Enter（入力の終わり）を押す。

```text
hello
EL
^Z
```

1 行目と 3 行目はコンソールが映した入力，2 行目がプログラムの出力。期待は `HELLO`。`abc` と入力すると `B` だけが出る（テスト `debugging/BugUpper/hello`・`abc`）。
入力の文字数（改行を含む）が奇数だと，`while` の条件で最後の文字を読んだ後に本体の `getchar` がもう一度入力を待つ。Windows ではそのために行頭の Ctrl+Z → Enter がもう一度要ることがあり，最後に `EOF` の値を `putchar` するので，意味のない 1 バイト（0xFF）が余分に出る。

## 学生への渡し方

- 渡すもの: `upper.c` だけ。
- 最初に言うこと: 「入力を大文字にして写すプログラムです。Ctrl+F5 で実行し，`hello` と入力して Enter を押すと `HELLO` と出るはずですが，`EL` と出ます（終えるときは行頭で Ctrl+Z → Enter）。原因をデバッガで探してください」
- 言わないこと: `getchar` を 2 回呼んでいること。

## 探し方

1. **症状を並べる**: 入力 `h e l l o ⏎` と出力 `E L ⏎` を縦に並べて書かせる。出力に残ったのは 2・4・6 文字目（`e`・`l`・改行）で，1 つおきに消えていることに気付かせる。
2. **1 回目で止める**: `if (ch >= 'a' && ch <= 'z') {` の行に F9，F5。コンソールに `hello` と入力して Enter を押すと止まる。**Locals** の `ch` は `101`（`'e'` の文字コード）で，`h`（104）ではない。`int` は数だけが表示されるので，**Debug > Windows > Watch > Watch 1**（授業では未習）に `(char)ch` と書くと `101 'e'` のように文字も見られる。
3. **仮説**: 「1 回の繰り返しの中で，`ch` に入る前に 1 文字読まれて捨てられている」。
4. **確かめる**: `while` の行にもブレークポイントを置き，F5 で最初から実行し直す。`while (getchar() != EOF)` の行から F10 で 1 文ずつ進め，「この行で 1 文字，次の `ch = getchar();` でもう 1 文字読む」ことを確かめる。条件の `getchar()` の戻り値はどの変数にも入らないので，**Locals** には現れない（捨てられている）ことを言わせる。
   F10 で `getchar` を呼ぶ行を通った直後は，**Debug > Windows > Autos**（授業では未習）に `getchar` の戻り値が表示される（`getchar returned` のような形。Microsoft Learn「Inspect variables and return values in the Visual Studio debugger」の **View return values in the Autos window**）。`while` の行で 104（`h`）が読まれ，どこにも残らないことが分かる。
5. 入力待ちのときに F10 を押すと進まないのは正常（入力待ち）。コンソールへ切り替えて入力する。

## ヒントの段階

1. 「入力と出力を 1 文字ずつ並べて書こう。どの文字が消えた？」
2. 「`while` の行を F10 で 1 回進めたとき，入力の何文字目が読まれた？（**Autos** に `getchar` の戻り値が出る）」 **Autos** を使わない場合は「`while` の行を通った後，`hello` のうち読まれずに残っているのは何文字？ 次の `ch = getchar();` で `ch` に入るのはどの文字？」
3. 「1 回の繰り返しの中で，`getchar` は何回呼ばれている？ `while` の条件で読んだ文字は，どの変数に入っている？」

## 原因

`getchar` は呼ぶたびに次の 1 文字を読む。`while (getchar() != EOF)` で読んだ文字は比べた後に捨てられ，本体の `ch = getchar();` が次の文字を読むので，1 文字おきにしか処理されない。
読む・比べる・使うを 1 回の `getchar` で行うには，読んだ値を変数に代入してから比べる（講義 2 節の `while ((ch = getchar()) != EOF)`）。

## 直し方

```diff
-    while (getchar() != EOF) {
-        ch = getchar();
+    while ((ch = getchar()) != EOF) {
         if (ch >= 'a' && ch <= 'z') {
```

直した版は `hello` → `HELLO`，空の入力 → 何も表示しない，などを確かめている（テスト `variant_fixed--*`）。

## 学生への問い

- 問「`while ((ch = getchar()) != EOF)` の括弧を外して `ch = getchar() != EOF` にするとどうなる？」→ `!=` が先に計算され，`ch` には比較の結果（1 か 0）が入る（講義 2 節の注意）。
- 問「`a` 1 文字だけで試したら，どう見えた？」→ `a` と改行の 2 文字なので，改行だけが出て `a` が消える。1 文字の入力でも誤りが見える。
- 問「この誤りのバグ報告を書くと？」→ 再現手順「Ctrl+F5 で起動し `hello` と入力して Enter，行頭で Ctrl+Z → Enter」，期待「`HELLO`」，実際「`EL`」。

## 関連

- [題材の一覧と渡し方の共通ルール](../README.md)
- 第7回 README の [共通: 入力の与え方・入力終了・リダイレクト](../../week07/README.md#共通-入力の与え方入力終了リダイレクト)，[課題1　入力をそのまま出力する](../../week07/README.md#課題1入力をそのまま出力するecho--echoc)（[読み取り順を紙上で追う（表）](../../week07/README.md#読み取り順を紙上で追う表)，[小文字化フィルタ（`LowerInput`）](../../week07/README.md#小文字化フィルタlowerinput)）
- 実務の手引きの [第7回　再現できる質問・バグ報告](../../ta-guide/README.md#第7回再現できる質問バグ報告入出力)，[どの回でも使う型](../../ta-guide/README.md#どの回でも使う型) の [質問・バグ報告のテンプレート](../../ta-guide/README.md#質問バグ報告のテンプレート)
