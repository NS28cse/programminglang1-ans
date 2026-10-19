# BugAnswerCheck　答え合わせ（第6回）

ソース: [answer_check.c](answer_check.c)

## 対象の回と前提

- 第6回（文字列）。講義 3 節「`strcmp`は最初に違う文字で決まる」と，課題4 `CompareJoin`（比較してから連結する）の後。
- 学生が知っていること: 文字列を関数へ渡すこと，`strcmp` の戻り値（等しければ 0，前なら負，後なら正），`if` の条件は 0 なら偽・0 以外なら真（第4回 講義 2 節「真は1だけではない」），ブレークポイント（F9）・F5・F10・**Locals**。
- 入力も引数もない。

## プログラムがするはずのこと

`check(answer, guess)` は答えと解答を比べ，同じ文字列なら `guess: correct`，違えば `guess: wrong` と表示する。答え `"apple"` に 3 つの解答を比べるので，期待する表示は:

```text
apple: correct
apply: wrong
Apple: wrong
```

## 症状

**Startup Item** で `debugging BugAnswerCheck` を選び，Ctrl+F5 で実行する。

```text
apple: wrong
apply: correct
Apple: correct
```

3 つとも逆になる（テスト `debugging/BugAnswerCheck/symptom`）。

## 学生への渡し方

- 渡すもの: `answer_check.c` だけ。
- 最初に言うこと: 「答え合わせのプログラムです。`apple: correct`，`apply: wrong`，`Apple: wrong` と出るはずですが，Ctrl+F5 で実行すると correct と wrong がすべて逆に出ます。原因をデバッガで探してください」
- 言わないこと: `strcmp` の戻り値の意味，`== 0`。

## 探し方

1. **症状を分類する**: 3 つとも逆。「一部の解答だけ」ではなく「判定のしかたが反対」と範囲を絞る。判定しているのは `check` の `if` だけ。
2. **止めて経路を見る**: `check` の `if (strcmp(answer, guess)) {` の行に F9，F5。1 回目（**Locals** の `guess` が `"apple"`）で F10 を押すと，`correct` ではなく `wrong` の `printf` の行へ進む。
3. **条件の値を見る**: `strcmp(answer, guess)` の値を確かめる。F10 で `if` の行を通った直後の **Debug > Windows > Autos**（授業では未習）に `strcmp` の戻り値が出る。`"apple"` 同士では 0。評価できる環境なら，**Debug > Windows > Watch > Watch 1**（授業では未習）に `strcmp(answer, guess)` と書いても見られる（ウォッチで関数呼び出しを評価するには，その関数のシンボルが要る）。
   ウォッチを使わない場合は，講義 3 節の表（「等しければ0」）を読み，`if (0)` がどちらへ進むかを言わせる。
4. **仮説**: 「`strcmp` は等しいときに 0 を返す。`if` は 0 を偽として扱うので，等しいときに `else`（wrong）へ進む」。
5. **確かめる**: `"apply"` のときの値（`'e'` と `'y'` の違いで負の値）と，`if` が真になることを確かめる。「`strcmp` は『違うかどうか』を返す関数のように振る舞っている」と言葉にさせる。

## ヒントの段階

1. 「`"apple"` と `"apple"` を比べたとき，`if` の後でどちらの `printf` へ進んだ？」
2. 「`strcmp("apple", "apple")` はいくつを返す？ 講義の表で確かめよう」
3. 「`if` の条件が 0 のとき，真？ 偽？」

## 原因

`strcmp` は等しいときに **0** を返し，違えば 0 以外（負か正）を返す（講義 3 節）。`if (strcmp(answer, guess))` は「0 以外なら真」なので，「違うとき」に `correct` を表示してしまう。
`strcmp` の名前や「比較して真なら等しい」という思い込みから，`if (strcmp(a, b))` を「等しければ」と読む誤りはよく起きる。文法上は正しいので，コンパイラは警告を出さない。

## 直し方

```diff
-    if (strcmp(answer, guess)) {
+    if (strcmp(answer, guess) == 0) {
```

直した版は `correct`・`wrong`・`wrong` を表示する（テスト `variant_fixed`）。「等しい」は `== 0`，順序は `< 0`・`> 0` と，比べる相手を必ず書く（`== -1` や `== 1` とは比べない。講義 3 節）。

## 学生への問い

- 問「`if (!strcmp(answer, guess))` でも直る。`== 0` と書く方がよいのはなぜ？」→ 結果は同じだが，`!` は「否定」と読めて「等しい」という意図が伝わりにくい。`== 0` なら戻り値の約束（等しければ 0）をそのまま書ける。
- 問「`answer == guess` と書いたら？」→ 文字列の中身ではなく配列の場所（アドレス）を比べるので，同じ文字でも等しいとは限らない（講義 6 節「よくある間違い」の表）。
- 問「`Apple` が wrong になるのは正しい？」→ 正しい。`strcmp` は大文字と小文字を別の文字（別の文字コード）として比べる。区別したくないなら，比べる前に小文字へそろえる（課題2 `Lower`）。

## 関連

- [題材の一覧と渡し方の共通ルール](../README.md)
- [第6回 README](../../week06/README.md) の「課題4　比較してから連結する」（「比較の条件を変える（容量 10）」）
- [実務の手引き](../../ta-guide/README.md) の「第6回　容量と範囲外書き込み」の「よくある反応」（`strcmp(...) == -1`）
