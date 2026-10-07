# 第7回 演習 解答・解説（入出力）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex07/>（原稿: [`docs/ex07.md`](https://github.com/t-yokoga/softprac1/blob/main/docs/ex07.md)）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec07/>（例題: [`docs/sample/07/`](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/07)）

この回で使う文法・関数は第6回までの範囲（`if`・`while`・配列・関数・`const`・`size_t`・`strlen`）と，
第7回の `getchar`・`putchar`・`fgets`・`fflush`・`ferror`・`fprintf(stderr, ...)`・`printf` の書式に限っています。
`ctype.h`（`tolower`・`isalpha`），`scanf` は使っていません。

## プロジェクト一覧

| 課題 | プロジェクト | ソース | テスト数 | データファイル |
| --- | --- | --- | ---: | --- |
| 1 複写 | `Echo` | [`echo.c`](Echo/echo.c)（講義の例題にコメントだけ追加） | 5＋変更版 8 | [`input.txt`](Echo/input.txt) |
| 1 小文字化フィルタ | `LowerInput` | [`lower_input.c`](LowerInput/lower_input.c) | 9＋変更版 3 | [`input.txt`](LowerInput/input.txt)，[`ab.txt`](LowerInput/ab.txt)（課題4の入力ファイル） |
| 2 英字数 | `LetterCount` | [`letter_count.c`](LetterCount/letter_count.c) | 11＋変更版 2 | [`input.txt`](LetterCount/input.txt) |
| 2 バイト数 | `ByteCount` | [`byte_count.c`](ByteCount/byte_count.c)（演習ページのコードにコメントだけ追加） | 8 | [`input.txt`](ByteCount/input.txt) |
| 3 行の容量 | `LineInput` | [`line.c`](LineInput/line.c)（講義の例題にコメントだけ追加） | 11＋変更版 6 | [`input.txt`](LineInput/input.txt) |
| 4 書式 | `Formats` | [`formats.c`](Formats/formats.c)（演習ページのコードにコメントだけ追加） | 1＋変更版 3 | なし（入力を待たない） |
| 発展 タイピング | `Typing` | [`typing.c`](Typing/typing.c) | 14＋変更版 8 | [`input.txt`](Typing/input.txt) |
| | | | **89**（うち変更版 30） | |

- 演習ページはソース名を指定していないため，講義の例題（`echo.c`，`line.c`）はその名前を使い，ほかはプロジェクト名を小文字・`_` 区切りにしました。
- 演習ページの「一時的に置き換える」「`line[8]`へ変更する」「`n`を123456へ変更する」などの**実験用の変更**はフォルダのソース（本体）に入れません。
  本体は講義の例題・演習ページの配布コードのまま（演習ページの期待する表示を出す版）とし，変更した版は README にコードブロックで載せ，`softprac_add_variant` でテストしています。
  `Echo` の検証①〜③・`LineInput` の 31/32 個の `A`・`Formats` の期待する表示は，すべて変更前のコードに対する仕様だからです。
- 変更版（`Echo` の `character=`/`new line` 表示と `putchar('/')` の追加，`line[8]`，`n`・`base` の値，大文字・小文字を区別する比較）と，
  採点のポイントで挙げた**誤りの例**（`LetterCount` の 1 範囲判定，`LowerInput` の `>`/`<` 判定，`Typing` の「一致したときだけ位置を進める」），
  課題4のプログラム `A`（`LowerInput` に処理状況の `stderr` 出力・`Ready` の `stdout` 出力を加えた版）は，
  各フォルダの `CMakeLists.txt` の `softprac_add_variant` で README と同じ書き換えをした版をビルドしてテストしています。
  期待値とテスト名は，同じ版に複数の入力を与える `Echo`・`LowerInput`・`LetterCount`・`LineInput`・`Typing` では `variants/tests/<版>--<入力>.*`（テスト名 `variant_<版>--<入力>`），
  入力のない `Formats` では `variants/tests/<版>.out`（テスト名 `variant_<版>`）です。
- `Typing` は演習ページの「作成する最終版」（大文字・小文字を区別しない版）です。区別する版は README に載せ，`softprac_add_variant` でテストしています。

ビルドとテスト（警告 0・89 テスト成功を確認済み。GCC 13.3 + AddressSanitizer/UBSan，Clang 18.1（sanitizer なし）でも同じ）:

```sh
cmake -S . -B /tmp/build-week07 -G Ninja -DSOFTPRAC_WEEKS=week07 -DSOFTPRAC_WERROR=ON -DSOFTPRAC_SANITIZE=ON
cmake --build /tmp/build-week07
ctest --test-dir /tmp/build-week07 --output-on-failure
```

## 共通: 入力の与え方・入力終了・リダイレクト

### キーボードから入力して `EOF` を知らせる

| 環境 | 入力終了（`EOF`）の知らせ方 | 注意 |
| --- | --- | --- |
| Windows（Visual Studio の Ctrl+F5 のコンソール，cmd，PowerShell，VS Code のターミナル） | **新しい行の先頭で Ctrl+Z，続けて Enter** | 画面には `^Z` と映る。行の途中で押した Ctrl+Z は確実な入力終了にならないので，必ず行頭で押す |
| macOS / Linux の端末 | **新しい行の先頭で Ctrl+D**（Enter は不要） | 行の途中で Ctrl+D を押すと，それまでの文字が改行なしで渡されるだけ。もう一度 Ctrl+D で `EOF` |
| 強制停止（Ctrl+C，「デバッグの停止」） | 入力終了ではない | 実行そのものが中断され，`EOF` の後の集計（`ByteCount` の表示など）は実行されない |

Visual Studio では，入力するのはエディタではなく Ctrl+F5 で開いたコンソールです。

### リダイレクト・パイプ（任意。授業の範囲外の確認用）

演習ページは「シェル操作は行わない」としていますが，TA が動作確認する場合や，興味のある学生に聞かれた場合のために使い方をまとめます。
実行ファイルの場所は，学生の Visual Studio プロジェクトなら出力ウィンドウに表示される `...\x64\Debug\Echo.exe`，
このリポジトリを CMake で開いた場合は `out\build\msvc-debug\bin\week07\Echo.exe` です。
以下は実行ファイルのあるフォルダで実行する例です。このリポジトリでは，プロジェクトフォルダ（`week07\Echo` など。`input.txt` がある）で
`..\..\out\build\msvc-debug\bin\week07\Echo.exe < input.txt` のように実行ファイルを相対パスで指定すれば，入力ファイルをコピーする必要はありません。

**cmd（コマンドプロンプト）**: 記号の意味は講義の表どおりです。

```bat
rem input.txt を標準入力へ接続（キー入力も Ctrl+Z も不要）
Echo.exe < input.txt
rem 結果を out.txt へ（既存の内容は上書き）
LowerInput.exe < input.txt > out.txt
rem out.txt の末尾へ追記
LowerInput.exe < input.txt >> out.txt
rem LowerInput の stdout を ByteCount の stdin へ
LowerInput.exe < input.txt | ByteCount.exe
rem stderr だけを err.txt へ（stdout は画面のまま）
LineInput.exe < input.txt 2> err.txt
```

**PowerShell**（VS Code の既定のターミナル）: `<` は使えません（「`<` 演算子は将来使用するために予約されています」というエラーになる）。

```powershell
Get-Content input.txt | .\Echo.exe                      # 入力ファイルを標準入力へ（行ごとに送られる）
.\LowerInput.exe < input.txt                            # ← PowerShell ではエラー
cmd /c "LowerInput.exe < input.txt | ByteCount.exe"     # バイト数を正確に確かめたいときは cmd に任せる
```

PowerShell には次の違いがあるため，**バイト数を比べる実験は cmd で行う**よう案内してください。

- `Get-Content ... |` で外部プログラムへ渡すと，行単位の文字列に直してから送り直すため，最後に改行がないファイルにも改行が付きます（`ByteCount` の結果が 1 増える）。
- Windows PowerShell 5.1 の `>` は UTF-16LE（BOM 付き）でファイルを書きます。`out.txt` をメモ帳以外で見ると 1 文字おきに `NUL` が入って見えます。PowerShell 7 では BOM なし UTF-8 です。

macOS / Linux（zsh，bash）では `<`・`>`・`>>`・`|`・`2>` が cmd と同じ意味で使えます。

### 環境によって変わる点（テキストモード）

C の標準ストリームは**テキストモード**で開かれています。Windows（MSVC の C ランタイム）とmacOS/Linux では次が異なります。

| 項目 | Windows（MSVC） | macOS / Linux |
| --- | --- | --- |
| 入力中の `\r\n`（CR LF） | `\n` 1 バイトに変換されて `getchar` に届く | 変換されない。`\r` と `\n` の 2 バイトが届く |
| 出力する `\n` | `\r\n` に変換されて書かれる | `\n` のまま |
| Enter キー | コンソールは `\r\n` を渡すが，上の変換で `\n` 1 バイトになる | `\n` 1 バイト |
| 入力中の Ctrl+Z の文字（0x1A） | テキストモードでは入力終了として扱われる | ふつうの 1 バイト |

このため，`ByteCount` が数えるのは「プログラムが読み取ったバイト数」で，**ディスク上のファイルサイズと一致するとは限りません**。
実際に Linux で CR LF の入力を与えると，`\r` も数えます（Linux x64，GCC で実行）。

```console
$ printf 'abcd\r\n' | ./ByteCount
6
$ printf 'ab\r\nC\r\n' | ./ByteCount
7
```

同じ内容（メモ帳で保存した CR LF のファイル）を Windows で `ByteCount.exe < file.txt` とすると，`\r\n` が `\n` になるので 5 になります。
逆に，Windows で `LowerInput.exe < ab.txt > out.txt` として作った `out.txt` は `ab` と CR LF の 4 バイトになります（Linux では 3 バイト）。
本リポジトリのテストの入力（`tests/*.in`）は，下の `crlf` ケースを除いて LF なので，どちらの環境でも同じ結果になります。
CR LF の入力を与える `crlf` ケース（`LowerInput`・`LetterCount`・`Typing`）は，`\r` が結果に影響しない（英字でない・お手本の 14 文字目以降・
出力の `\r\n` はテストが改行コードを無視して比較する）ので，Windows でも Linux でも同じ期待値で成功します。
一方 `LineInput` に `Hello` と CR LF を与えると，Linux では `\r` が本文に残り `length=6 text=Hello\r` になります（Windows では `length=5`）。
`ByteCount` と `LineInput` に CR LF のテストを置いていないのはこのためです。

---

## 課題1　入力をそのまま出力する（`Echo`）

**要点**: `getchar` が返す値を `int` で受け，`EOF` でない間だけ `putchar` で書く**複写**。Enter（改行文字）と `EOF`（入力の状態）は別物で，Enter ではループは終わらない。

解答: [`Echo/echo.c`](Echo/echo.c)（講義の `echo.c` と同じ。コメントだけ追加）

```c
int ch; // EOF と 256 通りのバイト値を区別するため char ではなく int で受ける
while ((ch = getchar()) != EOF) {
    if (putchar(ch) == EOF) {
        fprintf(stderr, "output error\n");
        return 1;
    }
}
if (ferror(stdin)) {           // 入力終了と読み取りエラーはどちらも EOF で届く
    fprintf(stderr, "input error\n");
    return 1;
}
```

### 実行結果

コンソールでの実行例（Linux の端末で実行。Windows では最後に `^Z` の行が見え，その後 Enter を押す）。
**入力行（コンソールが映した文字）とプログラムの出力が交互に並ぶ**ことに注意します。

```text
abc        ← キーボードから入力した文字（コンソールが映したもの）
abc        ← putchar による出力
XYZ        ← 入力
XYZ        ← 出力
           ← ここで行頭から Ctrl+Z, Enter（Linux は Ctrl+D）→ 終了
```

指定の3つの試行（入力ファイルで与えて，出力をバイト単位で確認。テスト `empty`・`newline_only`・`two_lines` と同じ）:

| 試行 | 入力 | 予測 | 実行結果（標準出力） |
| --- | --- | --- | --- |
| ① 最初に入力終了 | なし（`EOF` だけ） | 出力なし | 出力なし（0 バイト），終了コード 0 |
| ② Enter だけ → 入力終了 | `\n` | 改行 1 個 | `\n`（1 バイト）。コンソールでは入力の空行と出力の空行で 2 行空く |
| ③ `abc` Enter，`XYZ` Enter → 入力終了 | `abc\nXYZ\n` | 2 行の複写 | `abc` `XYZ` の 2 行 |
| （追加）改行なしで終わる | `abc` | `abc`（改行は付かない） | `abc`（3 バイト。テスト `no_final_newline`） |
| （追加）空白・記号と，空白 2 個だけの行 | `Hello C17!\n  \n` | そのまま複写 | `Hello C17!` と空白 2 個の行（テスト `spaces_line`） |

「空の入力」（①: `getchar` の 1 回目から `EOF`）と「空行 1 個の入力」（②: 1 回目が `'\n'`，2 回目が `EOF`）は，ループ本体の実行回数が 0 回と 1 回で異なります。

### 読み取り順を紙上で追う（表）

| `getchar`で読む値 | `EOF`との比較 | プログラムの処理 |
| --- | --- | --- |
| `'a'` | 等しくない | `a`を出力 |
| `'b'` | 等しくない | `b`を出力 |
| `'c'` | 等しくない | `c`を出力 |
| `'\n'` | 等しくない | 改行を出力 |
| 次の入力 | 到着するまで待つ | 終了ではない（`XYZ` と Enter が届けば同様に 4 回出力） |
| `EOF` | 等しい | 本体へ入らず終了（`ferror` で読み取りエラーでないことを確認して `return 0`） |

### 改行を見える形で確認する（一時的な変更）

`putchar` とその失敗処理を置き換えた版:

```c
#include <stdio.h>
int main(void)
{
    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            printf("new line\n");
        } else {
            printf("character=%c\n", ch);
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    return 0;
}
```

入力 `ab` と Enter（標準出力だけ。テスト `variant_visible--ab`）:

```text
character=a
character=b
new line
```

ほかに `abc` Enter `XYZ` Enter（`character=` 6 行と `new line` 2 行。`variant_visible--two_lines`），Enter だけ（`new line` 1 行。`variant_visible--newline_only`），空の入力（出力なし。`variant_visible--empty`）もテストしています。

`getchar` は 3 回呼ばれ，`'a'`・`'b'`・`'\n'` を 1 バイトずつ返しています。キーボードで `a`，`b` を押した時点ではコンソールが入力文字を映すだけで，プログラムの出力（`character=...`）はまだ出ず，Enter を押したときにまとめて 3 行が出ます。
これは**コンソールが 1 行分をためてから渡す**ためで，`getchar` が 1 行ずつ読むわけではありません（「Enter でまとめて届く」と「`getchar` を 3 回呼ぶ」は別のこと）。

### `putchar('/')` を加える（予測の練習）

元に戻した `echo.c` の `putchar(ch)` の前に，`putchar('/')` とその戻り値の確認を加えた版（ループ部分）:

```c
while ((ch = getchar()) != EOF) {
    if (putchar('/') == EOF) {
        fprintf(stderr, "output error\n");
        return 1;
    }
    if (putchar(ch) == EOF) {
        fprintf(stderr, "output error\n");
        return 1;
    }
}
```

| 入力 | 予測 | 実行結果 | テスト |
| --- | --- | --- | --- |
| `ab` Enter | `/a/b/` と改行 | `/a/b/` と改行 | `variant_slash--ab` |
| `abc` Enter，`XYZ` Enter | `/a/b/c/` 改行 `/X/Y/Z/` 改行 | `/a/b/c/` 改行 `/X/Y/Z/` 改行 | `variant_slash--two_lines` |
| Enter だけ | `/` と改行 | `/` と改行 | `variant_slash--newline_only` |
| 空の入力 | 出力なし | 出力なし | `variant_slash--empty` |

改行も 1 文字として読まれ本体を通るので，**改行の前にも `/` が付き**，行末が `/` になります。`EOF` では本体に入らないので，最後に余分な `/` は付きません。

### 小文字化フィルタ（`LowerInput`）

解答: [`LowerInput/lower_input.c`](LowerInput/lower_input.c)

```c
while ((ch = getchar()) != EOF) {
    // EOF を除いた後なので ch は実際に読んだ 1 バイト。範囲内だけを変換する
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch - 'A' + 'a';
    }
    if (putchar(ch) == EOF) { ... }
}
```

| 入力 | 予測 | 実行結果 | テスト |
| --- | --- | --- | --- |
| `Hello C17!` | `hello c17!` | `hello c17!` | `hello` |
| `AZaz09` | `azaz09` | `azaz09` | `azaz09` |
| ``@AZ[`az{``（`A`・`Z`・`a`・`z` の前後の文字） | ``@az[`az{`` | ``@az[`az{`` | `boundary` |
| `Hello C17!`，`AZaz09`，`A B` の 3 行 | 3 行とも小文字化，空白・改行はそのまま | `hello c17!` / `azaz09` / `a b` | `multi_lines` |
| 空の入力 / Enter だけ / 改行なしの `ABC` | 出力なし / 改行 / `abc` | 同左 | `empty` / `newline_only` / `no_final_newline` |
| （課題4 の入力ファイル）`AB` | `ab` | `ab` | `ab` |
| CR LF で終わる 2 行（`Hello C17!`，`AZaz09`） | 2 行とも小文字化 | `hello c17!` / `azaz09`（Linux では `\r` もそのまま複写） | `crlf` |

コンソールでの実行例（Linux の端末）:

```text
Hello C17!
hello c17!
AZaz09
azaz09
```

**説明すること（変換を `EOF` 判定の後に行う理由）**:
`EOF` は文字ではなく「これ以上読めない」という状態を表す負の `int` の値なので，文字として変換・出力してはいけません。
条件式で先に `EOF` を除いておけば，本体の `ch` は必ず実際に読んだ 1 バイト（0〜255）であり，その値だけを範囲判定・変換・`putchar` できます。
（判定の前に変換して `putchar` に渡すような書き方をすると，`EOF` が `unsigned char` に変換された値のバイトとして書き出されてしまいます。MSVC・glibc では `EOF` は −1 なので，0xFF（255）のバイトになります。）

**説明すること（配列へ全入力を保存しなくてよい理由）**:
各文字の出力は**その 1 文字だけで決まり**，前後の文字を参照しないからです。読んだらすぐ変換して書き出し，次の文字へ進めばよいので，必要な記憶は変数 `ch` の 1 つだけです。
入力の長さを事前に知る必要がなく，配列の容量を超える心配もありません。このように少しずつ読んで処理し次へ渡すプログラムが**フィルタ**です。

### 採点のポイント・よくある誤り（課題1）

- `ch` を `char` で宣言している → 誤り（確認問題1）。MSVC `/W4` では `C4244`（`int` から `char` への変換）の警告が出る。
- `while (ch = getchar() != EOF)` と括弧を省く → `ch` には比較結果 1 が入り，`ab` Enter で `\x01` が 3 バイト出力される（実際に試した結果。GCC は `-Wparentheses`，MSVC は `C4706` を出す）。
- `putchar(ch + 32)` のように範囲判定なしで変換 → 数字・記号・改行まで変わる。`'a' - 'A'` または `- 'A' + 'a'` を使い，32 を直接書かない方が意図が明確。
- 範囲を `ch > 'A'` / `ch < 'Z'` とする境界の誤り → `AZaz09` で `A`・`Z` が変わらず `AZaz09` のまま出力される（この誤りの版のテスト `variant_strict--azaz09`）。
- Enter を押しても終わらないのを「止まった」と誤解し，強制停止している → `EOF` の知らせ方（行頭で Ctrl+Z, Enter）を確認させる。
- 記録で，コンソールが映した入力行と `putchar` の出力行を区別していない（`abc` が 2 回見えるのは正常）。

---

## 課題2　英字の数を数える（`LetterCount`，`ByteCount`）

**要点**: 継続条件に `ch != '\n'` を加えると「1 行」で止まる。`&&` の短絡評価で，`EOF` のときは右側の比較を評価しない。英字は 2 つの範囲を `||` でつなぐ。

解答: [`LetterCount/letter_count.c`](LetterCount/letter_count.c)

```c
while ((ch = getchar()) != EOF && ch != '\n') {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        ++count;
    }
}
if (ferror(stdin)) { ... }
printf("%d\n", count);
```

表示は個数だけ（`3` と改行）にしました（演習ページは表示形式を指定していないため，`ByteCount` と同じ形式）。

### 英字の範囲と停止条件を確かめる（表）

| 1行の入力 | 期待する数 | 注目点 | 実行結果 | テスト |
| --- | ---: | --- | ---: | --- |
| `abc 12!` | **3** | 数字・空白・記号は除く | 3 | `abc_12` |
| 空行 | **0** | 本体を実行せず改行で終了 | 0 | `empty_line` |
| `AZaz` | **4** | 大文字・小文字の両方を数える | 4 | `azaz` |
| `@AZ[` | **2** | `A`の前，`Z`の後は英字ではない | 2 | `outside_az` |
| `123!?` | **0** | 英字なし | 0 | `no_letters` |
| （追加）`` `az{ `` | 2 | `a` の前（`` ` ``）と `z` の後（`{`）も英字ではない | 2 | `lower_boundary` |
| （追加）`EOF` だけ | 0 | 改行がなくても `EOF` で止まる | 0 | `eof_only` |
| （追加）改行なしの `abc 12!` | 3 | 最後の行に改行がなくても集計する | 3 | `no_final_newline` |
| （追加）英字 999 個と Enter（上限 1000 バイト） | 999 | 上限いっぱいの行でも数え漏れがない | 999 | `max_1000` |
| （追加）`ab` Enter `cdef` Enter | 2 | 最初の改行で止まり，2 行目は読まない | 2 | `first_line_only` |
| （追加）`abc 12!` と CR LF | 3 | `\r` は英字ではないので数えない（Windows では `\n` に変換済み） | 3 | `crlf` |

コンソールでの実行例（Linux の端末）。`EOF` を知らせなくても，Enter を押した時点で集計が表示されて終了します。

```text
abc 12!
3
```

**短絡評価**: `(ch = getchar()) != EOF && ch != '\n'` で左側が偽（`EOF`）なら，右側の `ch != '\n'` は評価されず，条件全体が偽になります。
`getchar` は左側で 1 回だけ呼ばれ，右側は読み取った値を調べるだけです（右側にもう一度 `getchar()` を書くと 1 文字読み飛ばす誤りになる）。

### 改行も含めた全入力のバイト数（`ByteCount`）

解答: [`ByteCount/byte_count.c`](ByteCount/byte_count.c)（演習ページのコードにコメントだけ追加）

| 入力してから`EOF` | 期待する数 | 実行結果 | テスト |
| --- | ---: | ---: | --- |
| 何も入力しない | **0** | 0 | `empty` |
| Enterだけ | **1** | 1 | `newline_only` |
| `abcd`とEnter | **5** | 5 | `abcd` |
| `ab`とEnter，CとEnter | **5** | 5 | `two_lines` |
| （追加）改行なしの `abcd` | 4 | 4 | `no_final_newline` |
| （追加）`A` 999 個と Enter（上限 1000 バイト） | 1000 | 1000 | `max_1000` |
| （課題4 問4）`ab` と Enter（`A` の出力） | 3 | 3 | `pipe_ab` |
| （課題4 問5）`Ready` と Enter，`ab` と Enter | 9 | 9 | `pipe_ready` |

コンソールでの実行例（Linux の端末。最後の行で Ctrl+D。Windows では行頭で Ctrl+Z, Enter）。Enter を押しても（入力文字が映るだけで）プログラムは何も出力せず，`EOF` を知らせて初めて `5` が出ます。

```text
ab
C
5
```

Windows の対話入力でも Enter は `\n` 1 バイトとして読まれるので，表の値は Windows・macOS・Linux で同じです。
CR LF のファイルをリダイレクトした場合だけ，Windows は改行 1 バイト，Linux は 2 バイトと数えます（[共通](#環境によって変わる点テキストモード)を参照）。

**説明すること（何を数えるか・いつ表示するか）**:

| | `LetterCount` | `ByteCount` |
| --- | --- | --- |
| 何を数えるか | **最初の 1 行**に含まれる ASCII 英字（`A`〜`Z`，`a`〜`z`）の個数。数字・空白・記号・改行は数えない | **`EOF` までに読み取ったすべてのバイト**の個数。改行も空白も 1 として数える（単語数・見た目の文字数・ファイルサイズではない） |
| いつ表示するか | 改行を読んだとき，または改行の前に `EOF` になったとき（Enter で表示される） | `EOF` になったときだけ（Enter では表示されない。強制停止すると表示されない） |
| 停止条件 | `ch == '\n' \|\| ch == EOF` | `getchar() == EOF` |

### 採点のポイント・よくある誤り（課題2）

- 英字判定を `ch >= 'A' && ch <= 'z'` の 1 範囲にしている → `[` `\` `]` `^` `_` `` ` `` も数える。`@AZ[` が 3，`` `az{ `` が 3 になれば誤り（この誤りの版のテスト `variant_one_range--outside_az`・`variant_one_range--lower_boundary` で 3 になることを確認）。
- `ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z'` と括弧を省いても，`&&` が `||` より先に結合するので結果は同じ。ただし GCC は `-Wparentheses`（Clang は `-Wlogical-op-parentheses`）の警告を出すので，意図を明示するため `(... && ...) || (... && ...)` と括弧を付ける（`-Werror` の環境ではビルドが止まる）。
- `while (getchar() != '\n')` だけで `EOF` を見ていない → 改行なしで入力が終わると無限ループ。
- 右側にも `getchar()` を書いて 1 文字おきに読む。
- `ByteCount` の表で改行を数え忘れる（Enter だけを 0，`abcd` Enter を 4 とする）。
- 「`ab` と Enter，`C` と Enter」を 3 とする（改行 2 個を忘れる）。

---

## 課題3　行の容量（`LineInput`）

**要点**: `fgets(line, sizeof line, stdin)` は最大で容量−1 バイトを読み終端を付ける。改行が配列に入ったかどうかで「容量内に収まった」かを判断し，入らなかったときは残りを読んで「ちょうど 31 バイト」と「超過」を区別する。

解答: [`LineInput/line.c`](LineInput/line.c)（講義の `line.c` と同じ。コメントだけ追加）

### 実行結果

標準出力の `Text: ` は入力案内です。入力をファイルから与えると入力行は映らないので，案内と結果が同じ行に並びます。

| 入力 | 標準出力 | 標準エラー出力 | 終了コード | テスト |
| --- | --- | --- | ---: | --- |
| 空行（Enter だけ） | `Text: length=0 text=` | | 0 | `empty_line` |
| `Hello` | `Text: length=5 text=Hello` | | 0 | `hello` |
| `A` 30 個 | `Text: length=30 text=AAA…A`（`A` 30 個） | | 0 | `a30` |
| `A` 31 個 | `Text: length=31 text=AAA…A`（`A` 31 個） | | 0 | `a31` |
| `A` 32 個 | `Text: ` | `Line too long.` | 1 | `a32_too_long` |
| 何も入力せず `EOF` | `Text: ` | `No line read.` | 1 | `eof_only` |
| （追加）改行なしの `Hello` で終了 | `Text: length=5 text=Hello` | | 0 | `hello_no_newline` |
| （追加）改行なしの `A` 31 個で終了 | `Text: length=31 text=AAA…A` | | 0 | `a31_no_newline` |
| （追加）改行なしの `A` 32 個で終了 | `Text: ` | `Line too long.` | 1 | `a32_no_newline` |
| （追加）`Hello` Enter `World` Enter | `Text: length=5 text=Hello` | | 0 | `first_line_only` |
| （追加）`Hello C17!` | `Text: length=10 text=Hello C17!` | | 0 | `spaces` |

コンソールでの実行例（Linux の端末）:

```text
Text: Hello
length=5 text=Hello
```

```text
Text: No line read.        ← Text: の後に行頭で Ctrl+D（Windows では Ctrl+Z, Enter。画面に ^Z が映り，改行してから No line read.）
```

### 3つの長さを区別する（表）

`Hello` と Enter では，入力として読むのは本文 5 文字と改行の 6 文字，`fgets` が保存するのは終端を加えた 7 要素，例題が表示する本文の長さは 5 です。

| 本文 | 最初の`fgets`の保存内容 | 例題の最終結果（実行結果） |
| --- | --- | --- |
| 空行 | 改行＋終端（2 要素） | `length=0 text=` |
| `Hello` | `Hello`＋改行＋終端（7 要素） | `length=5 text=Hello` |
| `A`が30個 | `A`30個＋改行＋終端（32 要素すべて） | `length=30 text=` と `A` 30 個 |
| `A`が31個 | `A`31個＋終端（改行は入らない） | 後から改行を消費し，`length=31 text=` と `A` 31 個 |
| `A`が32個 | `A`31個＋終端 | 残った `A` を検出して `stderr` に `Line too long.`，終了コード 1 |

`A` 31 個の場合，`fgets` の後に `getchar` が読むのは改行 1 つだけ（`extra` は 0 のまま）なので正常な行です。
`A` 32 個の場合は 32 個目の `A` を読んだ時点で `extra = 1` になり，さらに改行まで読み捨ててから診断します。

### 入力終了だけを知らせた場合

起動後，何も入力せず行頭で入力終了を知らせると，`fgets` は 1 文字も読めないまま入力が終わったので `NULL` を返し，`No line read.` を `stderr` に出して終了コード 1 で終わります。
Enter だけの空行は `'\n'` と `'\0'` を読めているので `fgets` は成功し，`length=0` の正常な行になります。
「長さ 0 の文字列を読み取れた」（空行）と「行を読み取れなかった」（`EOF` だけ）は別の結果です。

### 容量を小さくして仕組みを見る（`line[8]` に変更した版）

変更は宣言 1 か所だけです（`fgets(line, sizeof line, stdin)` が容量を `sizeof` で受け取っているので，読み込み上限が自動で 8 に追従します）。

```c
    char line[8];
```

| 入力 | 予測 | 実行結果（標準出力 / 標準エラー出力） | テスト |
| --- | --- | --- | --- |
| `ABCDEF`（6文字） | 長さ6 | `Text: length=6 text=ABCDEF` | `variant_line8--abcdef` |
| `ABCDEFG`（7文字） | 長さ7 | `Text: length=7 text=ABCDEFG` | `variant_line8--abcdefg` |
| `ABCDEFGH`（8文字） | Line too long. | `Text: ` / `Line too long.`（終了コード 1） | `variant_line8--abcdefgh` |
| 空行 | 長さ0 | `Text: length=0 text=` | `variant_line8--empty_line` |
| `EOF` だけ | No line read. | `Text: ` / `No line read.`（終了コード 1） | `variant_line8--eof_only` |
| 改行なしの `ABCDEFG` で終了 | 長さ7 | `Text: length=7 text=ABCDEFG` | `variant_line8--abcdefg_no_newline` |

`ABCDEF` は 6 文字＋改行＋終端 = 8 要素でちょうど収まり，`ABCDEFG` は 7 文字＋終端で改行が入らず，追加の `getchar` が改行だけを読みます。
`sizeof line` は配列そのものに使っているので 8 になりますが，**関数の配列引数**（`char s[]`）に `sizeof` を使っても配列全体の大きさは得られない（第5回）ので，関数に分けるときは容量を別の引数で渡します。

### 説明すること（追加の `getchar`・`extra`・読み捨てのループ）

- **追加の `getchar` で調べていること**: 配列の末尾に改行がないとき，入力にまだ残っている文字が「改行だけ（本文がちょうど 31 バイト）」「何もない（改行なしで入力が終了した）」「本文の続き（31 バイトを超えた）」のどれかです。
  `fgets` の結果だけでは区別できないので，残りを 1 文字ずつ読んで，改行と `EOF` 以外の文字があるかを調べています。
- **`extra` の意味**: 「最初の `fgets` で読み切れなかった本文の文字が 1 つ以上あった」ことを表すフラグです。超過がなければ（残りが改行だけ，または `EOF` だけ）**初期値の 0 のまま**です。
- **終了条件まで読み捨てるループが必要な理由**: 超過した本文が 2 文字以上残っていることもあるので，1 回の `getchar` では行の終わりまで届きません。
  改行まで（改行がなければ `EOF` まで）消費しておかないと，読み残した文字が次の入力処理に持ち越され，次の行の先頭として読まれてしまいます。
  また，条件に `ch != EOF` がないと，改行のない入力で `EOF` を読み続けて止まらなくなります。

### 採点のポイント・よくある誤り（課題3）

- `fgets` の戻り値を確認する前に `strlen(line)` を呼ぶ（確認問題5）。
- 改行を除くとき `line[strlen(line) - 1]` を無条件に書き換える → 改行がない場合に本文の最後の文字を消す。`n > 0` の確認がないと `size_t` の 0 から 1 を引いて巨大な添字になる。
- 「改行がない＝長すぎる」と判断する → `A` 31 個や改行なしで終わる入力を誤って超過と診断する。
- 表で「保存内容」と「本文の長さ」を混同する（`Hello` の保存は 7 要素，`strlen` は改行込みで 6，表示は 5）。
- `fflush(stdin)` で読み残しを捨てようとする（標準 C では未定義。講義どおり `getchar` で読み捨てる）。
- `line[8]` の実験で `fgets(line, 32, stdin)` のように容量を数値で書いている → 配列の外へ書き込む。`sizeof line` を使う利点を説明できるか。

---

## 課題4　接続関係を説明する（`Formats` ほか）

**要点**: データ（結果）は `stdout`，診断・状況は `stderr` に分ける。パイプやリダイレクトが付け替えるのは通常 `stdout`（と `stdin`）だけ。`printf` の幅・精度・長さ修飾子は型と目的に合わせる。

### `A` の処理状況は `B` に数えられるか・入力案内を `stdout` に出すと

- `A` の `stdout` を `B` の `stdin` へ接続しても，`A` が `stderr` へ書いた処理状況は**パイプを通らず画面へ出る**ので，`B` は処理状況を数えません。
- `A` が入力案内を `stdout` へ出すと，案内も**データと同じストリーム**に流れるので，`B` は案内の文字（と改行）まで数えてしまい，集計が狂います。ファイルへリダイレクトした場合も案内がファイルに混ざります。
  データ処理用のフィルタでは，案内を出さないか，`stderr` に出すべきです。

### リダイレクトの結果を予測する（接続図と答え）

入力ファイルの内容は `AB` と改行，`A` は小文字化フィルタ（処理状況を `stderr` へ出す），`B` は改行を含めて数えるプログラム（`ByteCount`）です。

```text
1.  入力ファイル(AB\n) ─stdin→ [A] ─stdout→ 画面        「ab」と改行
                                   └stderr→ 画面        処理状況
2.  入力ファイル(AB\n) ─stdin→ [A] ─stdout→ 出力ファイル 「ab」と改行が記録される
                                   └stderr→ 画面        処理状況は画面に残る
4.  入力ファイル(AB\n) ─stdin→ [A] ─stdout→(パイプ)─stdin→ [B] ─stdout→ 画面「3」
                                   └stderr→ 画面             └stderr→ 画面
```

| 問 | 答え | 理由 |
| --- | --- | --- |
| 1 | 画面に `ab` と改行が表示される（処理状況も画面に出る） | `A` の `stdout` も `stderr` も画面につながっている。大文字だけが小文字になり，改行はそのまま |
| 2 | ファイルには `ab` と改行だけが記録される。処理状況はファイルに入らず画面に出る | `>` が付け替えるのは `stdout` だけ。Windows ではファイルの改行は CR LF になり 4 バイト，macOS/Linux では 3 バイト |
| 3 | 上書き 2 回: `ab` と改行が **1 回分**だけ残る。上書き→追記: `ab` 改行 `ab` 改行の **2 回分**になる | `>` は実行のたびに前の内容を消してから書く。`>>` は末尾へ追加する |
| 4 | `B` は **3** と表示する | `B` が読むのは `a`・`b`・改行の 3 バイト。処理状況は `stderr` なので数えない |
| 5 | `B` の集計は **9**（6 増える） | `Ready` の 5 バイトと改行 1 バイトが `stdout` のデータに混ざり，`B` はそれも数える |

答えの根拠はテストで確認しています（`A` は `LowerInput` に `fprintf(stderr, "A: start\n")` と `fprintf(stderr, "A: done\n")` を加えた版 `status`，`A_ready` はさらに先頭で `printf("Ready\n")` する版 `ready`。`LowerInput/CMakeLists.txt`）。

| 問 | 確かめること | テスト | 入力 → 期待する結果 |
| --- | --- | --- | --- |
| 1・2 | 小文字化フィルタの `stdout` は `ab` と改行だけ | `LowerInput` の `ab` | `AB\n` → `ab\n` |
| 1・2・4 | 処理状況は `stdout` に混ざらず `stderr` に出る | `LowerInput` の `variant_status--ab` | `AB\n` → `stdout` は `ab\n` だけ，`stderr` は `A: start\nA: done\n` |
| 5 | `Ready` を出すと `stdout` のデータが `Ready\nab\n` になる | `LowerInput` の `variant_ready--ab` | `AB\n` → `stdout` は `Ready\nab\n` |
| 4 | `B` は `A` の `stdout`（`ab\n`）を 3 と数える | `ByteCount` の `pipe_ab` | `ab\n` → `3` |
| 5 | `B` は `Ready\nab\n` を 9 と数える | `ByteCount` の `pipe_ready` | `Ready\nab\n` → `9` |

テストはパイプそのものではなく，`A` の `stdout` の内容と，それを `B` の `stdin` に与えた結果を別々に固定しています。参考として，Linux で実際にリダイレクト・パイプでつないだ結果:

```console
$ ./A < ab.txt > out.txt
A: start
A: done
$ od -c out.txt
0000000   a   b  \n
0000003
$ ./A < ab.txt > out.txt 2>/dev/null; ./A < ab.txt >> out.txt 2>/dev/null; od -c out.txt
0000000   a   b  \n   a   b  \n
0000006
$ ./A < ab.txt | ./ByteCount
A: start
A: done
3
$ ./A_ready < ab.txt | ./ByteCount
A: start
A: done
9
```

Windows でパイプを使っても `B` の表示は同じ 3 と 9 です（`A` のテキストモード出力で `\n` が `\r\n` になり，`B` のテキストモード入力で `\n` に戻るため）。
なお，`stdout` と `stderr` は別々にバッファされるので，画面上で処理状況と結果が見える順番は環境によって前後します（`stdout` がパイプやファイルのときは，まとめて最後に書かれることが多い）。画面の並び順を処理順の証拠にしないよう注意します。

### `printf` の幅と書式を確かめる（`Formats`）

解答: [`Formats/formats.c`](Formats/formats.c)（演習ページのコードにコメントだけ追加。テスト `basic`）

実行結果（期待する表示と 1 文字ずつ一致）:

```text
|3|    3|
|154.423000|154.42|  154.42|
|1.300000e+10|1.3e+10|
500 764 1f4
5000000000
```

MSVC（Visual Studio 2015 以降）でも同じ表示です（古い MSVC は `%e` の指数を 3 桁 `e+010` で出していたが，現在は C 標準どおり 2 桁以上）。

#### 値を変えて確かめる

| 変更 | 予測 | 実行結果（変わった行） |
| --- | --- | --- |
| `int n = 123456;` | `%5d` でも 6 桁すべて表示（切り詰めない） | `\|123456\|123456\|`（テスト `variant_n_123456`） |
| `unsigned int base = 0764u;` | 八進 764 = 十進 500 なので出力は変わらない | `500 764 1f4`（5 行とも元と同じ。テスト `variant_base_octal`） |
| `unsigned int base = 0x1f4u;` | 十六進 1f4 = 十進 500 なので出力は変わらない | `500 764 1f4`（5 行とも元と同じ。テスト `variant_base_hex`） |

`n = 123456` の全出力:

```text
|123456|123456|
|154.423000|154.42|  154.42|
|1.300000e+10|1.3e+10|
500 764 1f4
5000000000
```

`big` の書式を `%d` に変える実験は，演習ページの指示どおり行いません（型が合わない書式は未定義動作）。

#### 説明すること

- **`%.2f` と `%8.2f` の違い**: どちらも小数点以下を 2 桁に丸めて表示します（`154.42`）。`%8.2f` はさらに**最小の表示幅** 8 を指定しているので，`154.42`（小数点を含めて 6 文字）の左に空白 2 個を補って `  154.42` になります。
  `%.2f` は幅の指定がないので必要な文字数だけです。幅は最小値で上限ではなく，桁が多ければはみ出して全部表示します。表示を丸めても変数 `value` の値は変わりません。
- **`%f` と `%g` の精度の意味の違い**: `%f` の精度（`%.2f` の 2，省略時 6）は**小数点以下の桁数**です。`%g` の精度（省略時 6）は**有効桁数**で，値の大きさに応じて通常形式か指数形式を選び，末尾の 0 を省きます。
  1.3e10 は指数 10 が精度 6 以上なので指数形式 `1.3e+10` になり，154.423 は 6 桁に収まるので `154.423` です。`%e` は常に指数形式で，精度は仮数の小数点以下の桁数（省略時 6，`1.300000e+10`）です。
- **長い整数に正しい長さ修飾子が必要な理由**: `printf` は可変個の引数を受け取る関数で，引数の型を自分では知らず，**書式の指定どおりの型として引数を取り出します**。
  `long long`（8 バイト）の値を `%d`（`int`，4 バイト）で表示すると，取り出す型と大きさが実際と食い違い未定義動作になります（5000000000 は `int` の範囲を超えるので，正しく表示される保証はまったくありません）。
  型に合う長さ修飾子 `ll`（`%lld`）を付けて，`long long` として取り出させる必要があります。
  `long` は Windows（MSVC，x64）では 4 バイト，Linux x64 では 8 バイトと環境で大きさが違うため，5000000000 を確実に保存・表示するには `long long` と `%lld` を使います。

### 採点のポイント・よくある誤り（課題4）

- 問4 で「`B` は処理状況も数える」と答える → `|` は `stdout` だけをつなぐ（`stderr` は画面のまま）。
- 問5 で増える数を 5 とする（`Ready` の後の改行を忘れる）。
- 問3 で「上書き 2 回なら 2 回分残る」と答える。
- 問2 で処理状況もファイルに入ると答える。
- `%8.2f` の 8 を「小数点以下 8 桁」や「整数部 8 桁」と説明する（幅は全体の文字数で，小数点も含む）。
- `%g` の精度を `%f` と同じ「小数点以下の桁数」と説明する。
- `0764` を「764」と読む（先頭の 0 で八進数になる）。

---

## 発展　タイピングの採点（`Typing`）

**要点**: 入力位置 `position` と得点 `score` を分けて管理し，**範囲内かを先に調べてから**お手本を読む（短絡評価で配列外を読まない）。小文字化関数は `EOF` を除いた `int` の値に使う。

解答: [`Typing/typing.c`](Typing/typing.c)（最終版: 大文字・小文字を区別しない）

```c
// ASCII の英大文字だけを小文字にする。EOF を除いた後の値を渡す
int lower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

int main(void)
{
    const char target[] = "This is a pen";
    size_t length = strlen(target); // 13
    size_t position = 0;            // 次に読む文字の位置（入力するたびに進む）
    int score = 0;                  // 一致した場合だけ増える
    ...
    while ((ch = getchar()) != EOF && ch != '\n') {
        // 範囲内かを先に調べてから target を読む（14 文字目以降は加点しない）
        if (position < length && lower(ch) == lower(target[position])) {
            ++score;
        }
        ++position;
    }
    ...
    printf("score=%d\n", score);
```

表示形式は演習ページで指定されていないため，`stdout` に入力案内 `Model: This is a pen` と `Input: ` を出し，最後に `score=得点` を出すことにしました。
対話実行の例（Linux の端末）:

```text
Model: This is a pen
Input: thiS is a Pen
score=13
```

### 段階ごとの確認

| 段階 | 確認すること | 入力 | 期待する得点 | 実行結果 | テスト |
| --- | --- | --- | ---: | ---: | --- |
| A | 空行と完全一致 | 空行 | 0 | 0 | `a_empty_line` |
| A | | `This is a pen` | 13 | 13 | `a_exact` |
| B | 途中まで入力 | `This` | 4 | 4 | `b_partial` |
| C | 同じ位置だけを採点 | `Txxxxxxxxxp` | 2 | 2 | `c_same_position` |
| D | 大文字・小文字を区別しない | `thiS is a Pen` | 13 | 13 | `d_ignore_case` |
| 追加 | 1 文字抜けると後ろがずれる | `Thi is a pen` | 3 | 3 | `missing_char` |
| 追加 | 14 文字目以降は加点しない | `This is a pen!` | 13 | 13 | `extra_char` |
| 追加 | すべて不一致 | `xxxxxxxxxxxxx`（13 個） | 0 | 0 | `all_wrong` |
| 追加 | すべて大文字 | `THIS IS A PEN` | 13 | 13 | `upper_all` |
| 追加 | 2 回分入力しても上限 13 | `This is a penThis is a pen` | 13 | 13 | `twice` |
| 追加 | `EOF` だけ / 改行なしの `This` | （なし）/ `This` | 0 / 4 | 0 / 4 | `eof_only` / `no_final_newline` |
| 追加 | 最初の改行で採点を終える | `This` Enter `This is a pen` | 4 | 4 | `first_line_only` |
| 追加 | CR LF で終わる行 | `This is a pen` と CR LF | 13 | 13 | `crlf` |

`Txxxxxxxxxp` は 11 文字で，位置 0 の `T` と位置 10 の `p` だけがお手本（`This is a pen` の位置 0 が `T`，位置 10 が `p`）と一致するので 2 点です。
`Thi is a pen` は位置 3 以降がお手本より 1 つ前にずれるため，`Thi` の 3 点だけです（位置を合わせ直す処理はしない仕様）。

### 大文字・小文字を区別する版

比較を `ch == target[position]` に変えた版（`if` の行だけが異なる）:

```c
        if (position < length && ch == target[position]) {
```

| 入力 | 区別しない版（最終版） | 区別する版（実行結果） | テスト（区別する版） |
| --- | ---: | ---: | --- |
| `This is a pen` | 13 | 13 | `variant_case_sensitive--exact` |
| `thiS is a Pen` | 13 | 10（`t`・`S`・`P` の 3 文字が不一致） | `variant_case_sensitive--mixed` |
| `This` | 4 | 4 | `variant_case_sensitive--partial` |
| `Txxxxxxxxxp` | 2 | 2 | `variant_case_sensitive--same_position` |
| `THIS IS A PEN` | 13 | 4（`T` と空白 3 個だけが一致） | `variant_case_sensitive--upper_all` |

### 入力案内を `stdout` に出していることと課題4の関係

このプログラムは対話用なので `Model: ...` と `Input: ` を `stdout` に出しています。得点だけを別のプログラムへパイプで渡すと，`B` には案内の文字列も届いてしまいます（課題4の問5 と同じ）。
得点だけを渡したいなら，案内を `fprintf(stderr, ...)` に変える，案内を出さないモードを設ける，などで**データ（得点）と案内の出力先を分ける**必要があります。

### 採点のポイント・よくある誤り（発展）

- `target[position]` を範囲の確認より前に読む（`target[position] == ch && position < length` の順）→ 14 文字目以降で配列の外を読む。`&&` の左側に範囲確認を置く。
- 一致しなかったときに `position` を進めない（`++position;` を `if` の中に入れる）→ 一致した文字だけで位置が進む別の仕様になり，`Txxxxxxxxxp` が 1，`Thi is a pen` が 5 になる（この誤りの版のテスト `variant_advance_on_match--same_position`・`variant_advance_on_match--missing_char`。完全一致の `This is a pen` は 13 のままなので，完全一致だけでは誤りに気付けない）。
- `score` と `position` を 1 つの変数で兼用する。
- 小文字化を `getchar` の直後（`EOF` の判定前）に行う，または `char` で受けた値に行う。
- 改行も 1 文字として比較・加点している（`This is a pen` Enter が 13 を超える，または 14 文字目扱いになる）。
- お手本の長さ 13 を数値で直接書き，お手本を変えたときに追従しない（`strlen` か `sizeof target - 1` を使う）。

---

## 確認問題

1. **`getchar` の戻り値を `char` へ先に保存しないのはなぜか**
   → `char` では `EOF` と文字を正しく区別できないからです。`getchar` は 256 通りのバイト値（0〜255）と，それらと異なる負の値 `EOF` の合わせて 257 通りを `int` で返しますが，`char` には 256 通りしか入りません。
   `char` が符号付きの環境（MSVC，x86 の GCC）ではバイト 0xFF が −1 になり `EOF` と等しくなって途中で止まります（Linux で `char ch` 版に `ab` 0xFF `cd` を与えると `ab` だけ出力して終了しました）。
   `char` が符号なしの環境では `EOF` が 255 になり，`EOF` と一度も等しくならず止まりません。MSVC `/W4` では `C4244` の警告が出ます。

2. **`'0'`，`'\0'`，`'\n'`，`EOF` の役割**
   → `'0'` は数字の文字ゼロ（ASCII で 48）で，`getchar` で読める普通の文字です。`'\0'` は値 0 の文字で，**配列の中で文字列の終わりを示す終端**です（入力の末尾に自動で流れてくるものではない）。
   `'\n'` は改行の文字（ASCII で 10）で，Enter で届き，行の区切りとして読まれます。`EOF` は文字ではなく，`getchar` などが**入力の終了または読み取りエラー**を知らせるために返す負の `int` の値（`stdio.h` で定義。−1 と決め打ちしない）です。

3. **`abcd` と Enter は，`getchar` で何回の読み取りに対応するか**
   → **5 回**です（`'a'`，`'b'`，`'c'`，`'d'`，`'\n'`）。Windows のコンソールでも Enter はテキストモードで `'\n'` 1 つになるので 5 回です。その後に入力終了を知らせれば 6 回目の呼び出しが `EOF` を返します（`ByteCount` の表の `abcd` と Enter が 5 になるのと同じ）。

4. **`getchar` を 1 回呼ぶと，入力した 112 は整数 112 になるか**
   → **ならない**。1 回目が返すのは文字 `'1'` の値（ASCII で 49）で，続けて呼ぶと `'1'`，`'2'`，`'\n'` を順に返します。整数 112 を得るには，各文字を `ch - '0'` で数字の値に直して 10 倍しながら足すなどの変換が必要です（数値文字列の検査と変換は第10回）。

5. **`fgets` の戻り値を確認する前に `strlen` を使ってはいけないのはなぜか**
   → `fgets` が `NULL` を返したとき（1 文字も読めずに入力が終了した，または読み取りエラー），配列に終端が書かれた保証がないからです。
   初期化していない局所配列なら中身は不定で，`strlen` は終端を探して配列の外まで読む未定義動作になります。成功（`NULL` でない）を確認してから，終端のある文字列として `strlen` や `%s` に渡します。

6. **`char line[32]` に保存できる本文の最大長は，この例題では何バイトか**
   → **31 バイト**です。容量 32 のうち 1 要素は終端に必要です。本文 31 バイトのときは改行が配列に入りませんが，例題は追加の `getchar` で改行だけが残っていることを確かめて正常な行として扱います（`A` 31 個 → `length=31`，32 個 → `Line too long.`）。
   改行まで配列に入る本文は 30 バイトまでです。

7. **`printf` で `double` を表示するときと，`scanf` で `double` へ読み込むときの書式**
   → `printf` は **`%f`**（`%e`・`%g` も可），`scanf` は **`%lf`** です。`printf` では `float` も `double` に変換されて渡されるので `%f` が `double` 用ですが，`scanf` は変数のアドレスを受け取り書き込む型を区別する必要があるので，`%f` が `float`，`%lf` が `double` です。

8. **パイプへ接続されるのは通常どの出力か．`stderr` はどう扱われるか**
   → パイプに接続されるのは**標準出力 `stdout`** です。`stderr` は接続されず，通常は画面（端末）に出たままです（`2>` などで別に指定しない限り，パイプの先のプログラムには届かない）。
   このため，結果を `stdout`，エラーや処理状況を `stderr` に分けておけば，次のプログラムへ渡すデータに診断が混ざりません。

### 参考: 講義ページの確認問題

1. `getchar` の戻り値を `int` で受けるのは，すべてのバイト値と `EOF` を区別するため（上の 1 と同じ）。
2. `fgets` で配列に改行が残るのは，改行までの行全体（本文＋改行）が容量−1 バイト以内に収まった場合（`line[32]` なら本文 30 バイト以下）。
3. 標準出力と標準エラー出力を分けると，リダイレクトやパイプで結果だけを次の処理やファイルへ渡せ，エラーメッセージは画面で確認できる。

---

## チェックリスト

| 項目 | 確認できる課題と内容 |
| --- | --- |
| 正常な値だけでなく，課題に示された境界の値でも確認した | 課題1 ``@AZ[`az{``（`A`/`Z`/`a`/`z` の前後），課題2 `@AZ[`・空行・`EOF` だけ，課題3 `A` 30/31/32 個と `line[8]` の 6/7/8 文字，発展 14 文字目以降（`This is a pen!`）。すべて `tests/` または `variants/tests/` にテストケースがある |
| 警告を確認し，原因を説明・修正した | 全プログラム（変更版を含む）が GCC 13・Clang 18 の `-Wall -Wextra -Wpedantic -Werror` で警告 0（`-DSOFTPRAC_WERROR=ON` でビルドして確認）。MSVC `/W4` で出る警告（C4244・C4706・C4996 など）の原因になる書き方（`getchar` の結果の `char` への代入，条件式全体が代入になる書き方，`scanf` 等）も使っていない（MSVC での実ビルドは未確認）。`char ch`（C4244）や括弧なしの代入（C4706，`-Wparentheses`）の警告の原因を課題1の採点ポイントで説明 |
| 自分の言葉で，処理の流れと使った型を説明できる | 課題1の読み取り順の表，`getchar` を `int` で受ける理由（確認問題1），`strlen` の `size_t`（課題3），`long long` と `%lld`（課題4） |
| Enter による改行，`EOF` による終了，強制停止を区別できる | 課題1 ①②③（空の入力と空行），課題2（`LetterCount` は Enter で表示，`ByteCount` は `EOF` で表示，強制停止では表示されない），共通の「入力終了」の表 |
| 入力文字の表示と，プログラム自身の出力を区別して記録した | 課題1・課題3・発展のコンソールでの実行例（入力行と出力行に注記），`character=` 版の確認 |
| 本文の長さ，改行，終端のための容量を別々に数えた | 課題3「3つの長さを区別する」の表（`Hello` は本文 5・改行込み 6・保存 7 要素），確認問題6 |
