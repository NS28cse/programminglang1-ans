---
theme: default
title: エラーメッセージを読む
info: |
  関係する回: 第1回〜（リンクのエラーは第12回で詳しく扱う）
  ビルドに失敗したときに，1 件目の診断のファイル名・行番号・説明を読み，指された行とその前の行を見て直す。番号の頭（C か LNK か）で直す場所の見当を付ける。
fonts:
  sans: Noto Sans JP
  mono: Fira Code
lineNumbers: true
routerMode: hash
drawings:
  persist: false
transition: none
mdc: true
---

# エラーメッセージを読む

ビルドに失敗したら，あちこち変える前に 1 件目を読む

<div class="opacity-70 mt-8">

関係する回: 第1回〜（リンクのエラーは第12回で詳しく扱う）

</div>

<!--
- 使う場面: ビルドに失敗して，エラー一覧を見ずにソースのあちこちを変えている学生。エラーが何十件も並んで手が止まっている学生。
- 全部を見せなくてよい。「1 件目」「前の行」「C と LNK」「古い exe」のうち，その学生の場面に合う 1 枚だけを見せる。
- 問「今出ているエラーの 1 件目は，どのファイルの何行目？」→ 学生の画面の Error List で答えさせる。
- 反応「エラーが多すぎてどこから見ればいいか分からない」→ 上から 1 件だけ。後ろは 1 件目の続きのことが多い。
- 画面の表記は Visual Studio 2026（英語版）。日本語版の名前を括弧で添えている。詳しくは ta ブランチの実務の手引きの第1回・第12回の節。
-->

---

# 1 件目だけ読む

**View > Error List**（エラー一覧）の**いちばん上**の行で，3 つを声に出して読む。行をダブルクリックすると，その行へ移る

| 列 | 読むこと | 例 |
| --- | --- | --- |
| **File**（ファイル） | どのファイルか | `hello.c` |
| **Line**（行） | 何行目か | `7` |
| **Description**（説明） | 何が足りない・合わないか | `'mesage': undeclared identifier`（宣言されていない名前） |

- 1 か所の誤りが，後ろに関係のないエラーを何件も出すことがある
- 1 件直したら，**Build > Build Solution**（ビルド > ソリューションのビルド，Ctrl+Shift+B）でビルドし直してから次を読む
- 同じ内容は **View > Output**（出力）の **Show output from: Build**（出力元: ビルド）にも出る

<!--
- 使う場面: Error List を開かずに，ソースの赤い波線だけを見て直している学生。
- 問「エラーが 10 件出たら，どれから直す？」→ 1 件目。1 件直したらビルドし直す（後ろのエラーが消えることが多い）。
- 反応「説明が英語で読めない」→ 全部訳さなくてよい。expected（〜があるはず），undeclared（宣言されていない），missing（足りない）など，数語で見当が付く。
- Error List の上の **Build + IntelliSense** を **Build Only** にすると，ビルドの診断だけになる（入力中の推測の表示が混ざらない）。
-->

---

# 指された行に誤りがなければ，前の行を見る

<div class="code-large">

```c {3-4|all}
#include <stdio.h>

int main(void);
{
    printf("Hello\n");
    return 0;
}
```

</div>

- 3 行目の最後の `;` が**余計**。コンパイラは 4 行目の `{` を読んで初めて「おかしい」と分かるので，4 行目を指す
- 指された行に誤りが見当たらないときは，1 つ前の行の終わりを見る
- 2 件目以降が出ても，1 件目の続きのことが多い。1 件目を直してビルドし直すと消える

<!--
- 使う場面: 「指された行は合っているのに，エラーが消えない」と言う学生。
- GCC 13 の表示は `4:1: error: expected identifier or '(' before '{' token`，Clang 18 は `4:1: error: expected identifier or '('`（どちらも 4 行目を指す。確かめた）。Visual Studio（MSVC）の番号と行番号はこの環境では確かめていない。学生の画面で Line の列を一緒に読む。
- 問「4 行目の `{` は正しいのに，なぜ 4 行目が指される？」→ 3 行目が `;` で終わると，そこで宣言が終わったと読まれる。4 行目の `{` は何にも続かない `{` になる。
- 反応「4 行目の `{` を消したら別のエラーになった」→ 指された行を変える前に，1 つ前の行を見る。
-->

---

# 番号の頭で，直す場所の見当を付ける

| **Code**（コード）の頭 | 起きた段階 | 直す場所 |
| --- | --- | --- |
| `C`（例: C2065） | コンパイル | そのファイルの文法・名前・型 |
| `LNK`（例: LNK2019） | リンク | 関数の名前のつづり，必要な `.c` がプロジェクトに入っているか |

`printf` を `prinft` と打つと，どちらも出る

```text {*}{lines:false}
warning C4013: 'prinft' undefined; assuming extern returning int
error LNK2019: unresolved external symbol prinft referenced in function main
fatal error LNK1120: 1 unresolved externals
```

- **warning**（警告）も読む。C4013 が誤りのある行（`prinft` の行）を指している
- LNK1120 は件数のまとめ。原因はその前の LNK2019

<!--
- 使う場面: LNK で始まるエラーをダブルクリックしてもソースに飛ばず，困っている学生。
- MSVC の番号の意味は ta の各回の README と同じ（C4013: 宣言のない関数を int を返す外部関数と仮定，LNK2019: 未解決の外部シンボル，LNK1120: その件数）。LNK のエラーには行番号がない（Line が空）ので，名前を手がかりにする。
- C1083（インクルード ファイルを開けない）のように，前処理の診断も C で始まる（第12回の手引きの表）。
- GCC 13 は `warning: implicit declaration of function 'prinft'; did you mean 'printf'?` の後にリンクで `undefined reference to 'prinft'`。Clang 18 は最初からエラー（`call to undeclared function 'prinft'`）にする（どちらも確かめた）。
- 複数のファイルに分けるのは第12回から。第11回までは「LNK ならつづりを見る」で足りる。
- 問「LNK2019 の行をダブルクリックしてもソースに飛ばない。どこを見る？」→ メッセージの名前（`prinft`）をソースで探す。
- 反応「警告だから無視した」→ この C4013 がいちばん大事な手がかり。警告も 1 件目から読む。
-->

---

# 失敗したら，古い exe を実行しない

ビルドに失敗したまま Ctrl+F5 を押すと，次のダイアログが出る

```text {*}{lines:false}
There were build errors. Would you like to continue and run the last successful build?
```

- **No**（いいえ）を押す。**Yes**（はい）だと，前に成功したときの古いプログラムが動く（直したつもりの変更が入っていない）
- 日本語版では「最後に成功したビルドを実行しますか」という確認になる。同じく **いいえ** を押す
- 成功は **Output** の `========== Build:` で始まる行で確かめる（`1 succeeded, 0 failed`）

```text {*}{lines:false}
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
```

<!--
- 使う場面: 「直したのに表示が変わらない」と言う学生。
- 問「このダイアログで Yes を押すと，どのプログラムが動く？」→ 前に成功したときの古い exe。
- 反応「exe が動いたので直った」→ 失敗したビルドの後に動いたのは古い exe。Output の `succeeded` と `failed` の数を読ませる。
- この行の後に `Build completed at ... and took ... seconds` の行も出る。
- このダイアログで「次から表示しない」を選んでしまった学生には，**Tools > Options > Projects and Solutions > Build and Run** の **On Run, when build or deployment errors occur** を **Do not launch** にする（画面の表記は要確認）。それまでは Ctrl+F5 の前に必ず **Output** の `failed` の数を見させる。
-->

---

# まとめ: 読む順番

1. **Error List** のいちばん上を読む（**File**・**Line**・**Description**）
2. 指された行を見る。誤りがなければ前の行の終わりを見る
3. 番号の頭を見る（`C` ならそのファイル，`LNK` なら関数の名前のつづりと，必要な `.c` がプロジェクトに入っているか）
4. 1 か所だけ直して，ビルドし直す（**No** を押して古い exe を動かさない）
5. **Output** で `1 succeeded` を確かめてから実行する

<!--
- 使う場面: 一度説明した学生が，次のエラーで同じように止まったとき。手順を自分で追わせる。
- 学生に 1〜5 を言わせるより，次のエラーのときに 1 だけを自分でやってもらう方が身につく。
- 問「ファイル名・行番号・説明の 3 つを言ってみて」→ 学生の Error List の 1 件目で答えさせる（第1回の課題3 の記録と同じ 3 つ）。
- 反応「全部いっぺんに直した方が早い」→ 1 件目を直すと後ろが消えることが多い。1 か所ずつの方が結局早い。
-->
