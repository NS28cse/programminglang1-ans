# BugStudentNames　名簿を読む（第11回）

ソース: [students.c](students.c)，入力: [input.txt](input.txt)

## 対象の回と前提

- 第11回（構造体）。講義 3 節「配列の文字列とポインタの文字列」と，課題4 `CopyMembers`（配列メンバとポインタメンバ）の後。ファイルを 1 行ずつ読むのは第10回の `fgets`。
- 学生が知っていること: `typedef` した構造体と構造体の配列，`char *` のメンバと `char` 配列のメンバの違い，`fgets` と改行の除去，`strcpy`，ブレークポイント（F9）・F5・F10・**Locals**。
- 作業ディレクトリの `input.txt` を読む（引数はない）。

## プログラムがするはずのこと

`input.txt` の名前（1 行 1 人）を `Student` の配列へ読み込み，読み終えてから番号と名前を表示する。`input.txt` が `Alice`・`Bob`・`Carol` なら:

```text
1 Alice
2 Bob
3 Carol
```

## 症状

**Startup Item** で `debugging BugStudentNames` を選び（作業ディレクトリは題材のフォルダ），Ctrl+F5 で実行する。

```text
1 Carol
2 Carol
3 Carol
```

番号は正しく，名前がすべて最後の人になる（テスト `debugging/BugStudentNames/symptom`）。

## 学生への渡し方

- 渡すもの: `students.c` と `input.txt`（プロジェクトフォルダに置く）。
- 最初に言うこと: 「`input.txt` の名簿を読んで表示するプログラムです。`input.txt` をプロジェクトフォルダに置いて Ctrl+F5 で実行すると，`1 Alice`，`2 Bob`，`3 Carol` と出るはずですが，3 人とも `Carol` と出ます。原因をデバッガで探してください」
- 言わないこと: ポインタメンバ・`line` を共有していること。

## 探し方

1. **いつ変わったかを絞る**: 「読み込んだ直後から誤っている」のか「後で変わった」のかを分ける。`++count;` の行に F9，F5。
2. 1 回目に止まったとき，**Locals** で `students` を展開し，`[0]` の `name` が `"Alice"` であることを確かめる。F5（**Debug > Continue**）で 2 回目に止まると，`[0]` の `name` が `"Bob"` に変わっている（`[1]` も `"Bob"`）。
3. **仮説**: 「`students[0].name` と `students[1].name` は同じ場所を指している。2 人目を読んだときに 1 人目の名前も変わった」。
4. **確かめる**: **Locals** の `students[0].name`・`students[1].name`・`line` の値の欄のアドレスが同じであることを見る（どれも `line` の先頭）。`students[i].name = line;` は文字列をコピーせず，`line` の場所を入れるだけだと言わせる。
5. 最後に `Carol` が 3 つ並ぶのは，ループの後の `line` の内容が `Carol` だから（ファイルの終わりで `fgets` が `NULL` を返すときは配列を変えない）。

## ヒントの段階

1. 「1 人目を読み込んだ直後の `students[0].name` は？ 2 人目を読み込んだ後は？」
2. 「`students[0].name` と `students[1].name` が指しているアドレスを比べよう」
3. 「`students[count].name = line;` で，`name` には何が入る？ 文字がコピーされる？」

## 原因

`name` は `char *` のメンバなので，`students[count].name = line;` は `line` の先頭のアドレスを入れるだけで，文字列はコピーされない。全員の `name` が同じ配列 `line` を指し，`line` は次の行を読むたびに上書きされるので，表示するときには最後の名前だけが残っている（講義 3 節「配列の文字列とポインタの文字列」）。
型は一致しているのでコンパイラは警告を出さない。`line` は `main` の終わりまで有効なので，この版では未定義動作にもならない（`line` が別の関数の局所変数だったら，寿命の切れた配列を指すことになる）。

## 直し方

名前を各要素の配列メンバへコピーする。

```diff
 typedef struct {
     int number;
-    char *name;
+    char name[MAX_NAME + 1];
 } Student;
```

```diff
         students[count].number = count + 1;
-        students[count].name = line;
+        strcpy(students[count].name, line);
```

`strcpy` の前に `length > MAX_NAME` を調べているので，配列メンバに収まる。直した版は 3 人・6 人（5 人まで読む）・20 文字の名前・21 文字の名前（エラー）を確かめている（テスト `variant_fixed--*`）。

## 学生への問い

- 問「1 人だけの名簿で試したら気付けた？」→ 気付けない。共有していても 1 人なら正しく見える。2 人以上で，名前がすべて違う入力を使う。
- 問「`char *name` のまま直すには？」→ 人ごとに別の領域を用意してコピーする（第13回の `malloc` で確保し，使い終わったら解放する）。この回の範囲では配列メンバにする。
- 問「`Student b = students[0];` で構造体をコピーすると，`name` の中身もコピーされる？」→ 配列メンバならコピーされる。`char *` メンバならアドレスだけがコピーされ，同じ文字列を共有する（課題4 `CopyMembers`）。

## 関連

- [題材の一覧と渡し方の共通ルール](../README.md)
- 第11回 README の [課題4　配列メンバとポインタメンバを比較する](../../week11/README.md#課題4配列メンバとポインタメンバを比較するcopymembers--copy_membersc)（図，[変更を分類する（表）](../../week11/README.md#変更を分類する表)）
- 第10回 README の [課題1（続き）　行の長さを表示する](../../week10/README.md#課題1続き行の長さを表示するlinelengths--line_lengthsc)（`fgets` と改行の除去）
- 実務の手引きの [第11回　コードレビュー：説明しながら読んで見つける](../../ta-guide/README.md#第11回コードレビュー説明しながら読んで見つける構造体)，[どの回でも使う型](../../ta-guide/README.md#どの回でも使う型) の [コードレビューの観点チェックリスト](../../ta-guide/README.md#コードレビューの観点チェックリスト) の「コピーと共有」
