# 第10回 演習 解答・解説（ファイル）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex10.html>（[ソース](https://github.com/t-yokoga/softprac1/blob/main/docs/ex10.md)）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec10.html>（例題: [`sample/10/`](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/10)）
- 今回の範囲: `fopen`/`fclose`（モード `r`・`w`・`a`・`rb`・`wb`・`wx`），`fgetc`・`fgets`・`fprintf`・`fscanf`・`fread`・`fwrite`，
  `ferror`・`perror`・`fflush`，`int main(int argc, char *argv[])`，`strtol` と `errno`/`ERANGE`，テキストとバイナリ，エンディアン，UTF-8。
  そのほかは第9回までの範囲（関数，`enum` の定数，ポインタ配列，`strcmp`，ビット演算）だけを使う。

## プロジェクト一覧

| 課題 | 内容 | プロジェクト | ソース | 既定の引数（`run.args`） | データファイル | テスト |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 1 文字ずつ読んで表示 | `ReadText` | [read_text.c](ReadText/read_text.c) | `input.txt` | [input.txt](ReadText/input.txt) | 9 |
| 1 | 行の長さ | `LineLengths` | [line_lengths.c](LineLengths/line_lengths.c) | `input.txt` | [input.txt](LineLengths/input.txt) | 13 |
| 2 | 数値引数の検査（講義の `parse_number.c`） | `ParseNumber` | [parse_number.c](ParseNumber/parse_number.c) | `42` | なし | 16 + 合計版 `sum` 13 |
| 2 | 引数を表示して文字列を探す | `Arguments` | [arguments.c](Arguments/arguments.c) | `nagano ishikawa` | なし | 12 |
| 3 | バイト列を保存（講義の `binary.c`） | `Binary` | [binary.c](Binary/binary.c) | なし | なし（`bytes.bin` は実行時に作る） | 2 + `utf8_a` 1 + `show_n` 1 |
| 3 | バイト順を調べる（「別の `main`」） | `ByteOrder` | [byte_order.c](ByteOrder/byte_order.c) | なし | なし | 1 + `value_0x1234` 1 |
| 4 | テキストを書く（モード `w`） | `WriteText` | [write_text.c](WriteText/write_text.c) | なし | なし（`scores.txt` は実行時に作る） | 3 + `mode_a` 3 + `mode_wx` 2 |
| 発展1 | 数値をテキスト・バイナリで往復 | `NumberFormats` | [number_formats.c](NumberFormats/number_formats.c) | なし | なし（`numbers.txt`・`numbers.bin` は実行時に作る） | 2 + `precision_0125` 1 |
| 発展2 | 二乗の一覧を書く | `WriteSquares` | [write_squares.c](WriteSquares/write_squares.c) | `4 squares.txt` | なし（`squares.txt` は実行時に作る） | 14 |
| 発展2 | 一覧を検査して値を探す | `CheckValue` | [check_value.c](CheckValue/check_value.c) | `squares.txt 9` | [squares.txt](CheckValue/squares.txt)（`WriteSquares 4` の出力のコピー） | 37 |

テストは合計 131 件（本体 109 件，variant 22 件）。すべて成功（GCC 13.3 + AddressSanitizer/UBSan，Clang 18.1，どちらも `-Wall -Wextra -Wpedantic -Werror` で警告 0）。

### この回の約束（TA 向け）

- **本体（フォルダのソース）は演習ページの期待する表示を出す版**（CONTRIBUTING.md §1）。この回は期待する表示がどれも配布コード・最初の版のものなので，本体はその版にし，その後の小問は variant にした。TA が IDE で本体を実行すると，演習ページ・講義の期待する表示がそのまま出る
  （`ParseNumber` は `42`，`Binary` は `41 00 42 0A`，`ByteOrder` は `01 00`，`WriteText` は何回実行しても 3 行，`NumberFormats` は `text=0.50 1.25 -2.00`）。
- 演習ページの「〜へ置き換えます」「値を変更すると」「モードだけを `a` へ変えます」などの小問は **variant** にした。
  各プロジェクトの `CMakeLists.txt` が全回共通の `softprac_add_variant`（[cmake/SoftpracVariant.cmake](../cmake/SoftpracVariant.cmake)）で本体の一部を置き換えた版を生成し，
  別の実行ファイル `<プロジェクト>_<版>` としてビルド・テストする（期待値は `<プロジェクト>/variants/tests/<版>.out` または `<版>--<ケース>.out`，
  テスト名は `week10/<プロジェクト>/variant_<版>[--<ケース>]`）。この README の variant のコードと実行結果は，その生成物を実際に実行したもの。

  | プロジェクト | variant | 演習ページの小問 |
  | --- | --- | --- |
  | `ParseNumber` | `sum` | 複数の数値を合計するなら（検査・変換部分を断片へ置き換え） |
  | `Binary` | `utf8_a` | UTF-8 をバイトとして観察する（`data` を `E3 81 82 0A` へ） |
  | `Binary` | `show_n` | `n` の値が 4 であることを `printf` で追加表示する |
  | `ByteOrder` | `value_0x1234` | 値を `0x1234` へ変更する |
  | `WriteText` | `mode_a`，`mode_wx` | モードだけを `a` へ変える，表の `wx` |
  | `NumberFormats` | `precision_0125` | `data[0]` を 0.125，最後の 2 行の表示を `%.3f` にする |

- `ByteOrder` は演習ページの「講義の `unsigned short` の観察用断片を別の `main` で実行します」に対応する。演習ページにプロジェクト名がないので，
  解答で名前を付けた（全回で重複しない名前）。学生のプロジェクト名は自由でよい。
- プログラムが書き出すファイル（`bytes.bin`・`scores.txt`・`numbers.txt`・`numbers.bin`・`squares.txt`）はリポジトリに置いていない。
  テストでは一時フォルダで実行し，書かれたファイルを `tests/<ケース>.files/` の期待値と比較している（`.bin` はバイト単位）。
- 実行結果は Linux x64（GCC 13.3）で実際にビルド・実行した出力。表示は ASCII だけで，Windows x64（MSVC）でも同じになる。
  環境で変わる点（改行コード，`long` のサイズなど）はそれぞれの節に「Windows x64 (MSVC) では…，Linux x64 では…」として書いた。
- 実行例の `$ ReadText input.txt` は「コマンド引数に `input.txt` を設定して実行した」という意味。`(終了コード 1)` はプログラムが返した値で，画面には出ない
  （Visual Studio の Ctrl+F5 のコンソールでは「…はコード 1 で終了しました」と表示される）。標準エラー出力も同じ画面に出る。

## 実行のしかた（コマンド引数と作業ディレクトリ）

この回のプログラムは，相対パスのファイル名（`input.txt` など）を**作業ディレクトリ**を基準に探す・作る。ソースの場所や実行ファイル（`.exe`）の場所ではない。

### Visual Studio（授業の手順：空のプロジェクト）

1. ソリューションエクスプローラーで**プロジェクト**（例: `ReadText`）を右クリック →「プロパティ」。
2. 上の「構成」を実行に使う構成（通常は `Debug`，迷ったら「すべての構成」）と，「プラットフォーム」を `x64` にする。
3. 「構成プロパティ → デバッグ」の **コマンド引数** に `input.txt` と書く（`ReadText.exe` は書かない）。2 個なら `squares.txt 9` のように空白で区切る。
   空白を含む 1 個の名前は `"my input.txt"`，空文字列の引数は `""` と書く。この欄は C の文字列リテラルではないので `\` を二重にしない。
4. **作業ディレクトリ** を `$(ProjectDir)`（`.vcxproj` のあるフォルダ）にする。
5. `input.txt` を `.vcxproj` と同じフォルダに保存する（エクスプローラーで拡張子を表示し，`input.txt.txt` になっていないか確認）。
6. Ctrl+Shift+B でビルド，Ctrl+F5 で実行。引数を変えるたびにソースを直す必要はない。

複数のプロジェクトがあるソリューションでは，実行されるのは「スタートアップ プロジェクト」（太字）である。
別のプロジェクトのプロパティを変えても結果が変わらないときは，ここを確認させる（講義「パスが見つからない場合」の表）。

### このリポジトリを Visual Studio で開く場合（フォルダーを開く）

各プロジェクトは「作業ディレクトリ = プロジェクトフォルダ」「引数 = `run.args`（1 行 1 引数）」の起動構成になる（`tools/gen_launch_vs.py` が `.vs/launch.vs.json` を生成）。
ツールバーの起動項目で `week10 ReadText  [input.txt]` などを選んで Ctrl+F5。引数を変えたいときは `.vs/launch.vs.json` の `"args"` を書き換える。

### VS Code

1. 実行したい課題の `.c` を開き，「実行とデバッグ」で **「開いている課題を引数つきで実行」**（Windows は MSVC，macOS/Linux は gdb/lldb）を選ぶ。
2. `.vscode/launch.json` のその構成の `"args"` を課題に合わせて書き換える。**1 要素が 1 引数**で，引用符は要らない:
   - `ReadText`: `"args": [ "input.txt" ]`，空白を含む名前: `"args": [ "my input.txt" ]`
   - `CheckValue`: `"args": [ "squares.txt", "9" ]`，`WriteSquares`: `"args": [ "4", "squares.txt" ]`
3. `"cwd": "${fileDirname}"` なので，作業ディレクトリは開いている `.c` のフォルダ（= プロジェクトフォルダ）。F5 / Ctrl+F5 で実行。

### ターミナルから実行する

作業ディレクトリをプロジェクトフォルダにしてから，ビルドした実行ファイルを相対パスで起動する（ビルド先は `out/build/<プリセット>/bin/week10/`。
variant は `out/build/<プリセット>/variants/week10/<プロジェクト>_<版>`，例: `WriteText_mode_a.exe`）。

```bat
rem Windows の cmd（プリセット msvc-debug）
cd week10\ReadText
..\..\out\build\msvc-debug\bin\week10\ReadText.exe input.txt
..\..\out\build\msvc-debug\bin\week10\ReadText.exe "my input.txt"
..\..\out\build\msvc-debug\bin\week10\ReadText.exe ""
```

```sh
# macOS / Linux（プリセット gcc-debug）
cd week10/ReadText
../../out/build/gcc-debug/bin/week10/ReadText input.txt
../../out/build/gcc-debug/bin/week10/ReadText "my input.txt"
# variant の例（追記モードの WriteText）
cd ../WriteText
../../out/build/gcc-debug/variants/week10/WriteText_mode_a
```

- 空文字列の引数 `""` は cmd・bash・zsh では 1 個の空の引数として渡るが，**Windows PowerShell 5.1 は空の引数を落とす**（`argc` が 1 になる）。`""` の確認は cmd か Visual Studio の「コマンド引数」欄で行う。
- VS Code の gdb/lldb（cppdbg）は引数をデバッガ経由で渡すので，空白や空文字列を含む引数の扱いが環境で異なることがある。境界の確認はターミナルで行うのが確実。
- `ctest` で全部を確かめる場合: `ctest --preset msvc-debug -R week10`（macOS/Linux は `gcc-debug`）。

---

## 課題1　ファイルを読む（`ReadText`）

**要点**: `fopen` の戻り値（`NULL`）を検査し，`fgetc` の戻り値を `int` で受けて `EOF` までループし，`ferror` と `fclose` の結果まで確かめる。
`argc` を調べてから `argv[1]` を使う。相対パスは作業ディレクトリが基準。

解答: [ReadText/read_text.c](ReadText/read_text.c)（講義の `read_text.c` にコメントを加えたもの。処理は同一）。
データ: [ReadText/input.txt](ReadText/input.txt)（`Hello`・`File` の 2 行，ASCII・BOM なし・LF，11 バイト。Windows のメモ帳で作ると CRLF の 13 バイトになるが，テキストモードで読むので表示は同じ）。

### 実行結果

```text
$ ReadText input.txt
Hello
File
```

### 表「試す条件」（記入済み）

| 試す条件 | 期待する結果（実際の結果） | 理由 |
| --- | --- | --- |
| `Hello`と`File`の2行 | `Hello`，`File` の 2 行をそのまま表示し，正常終了（終了コード 0） | 1文字ずつ最後まで読む |
| 空ファイル | 何も表示せず正常終了（終了コード 0）。エラーメッセージは出ない | `EOF`は必ずしもエラーではない（最初の `fgetc` が `EOF`，`ferror` は 0） |
| 最後の`File`の後に改行なし | `Hello` と `File` を表示し，`File` の後に改行を出力しない（出力の最後のバイトが `e`）。ターミナルでは次のプロンプトが `File` と同じ行に続く。正常終了（終了コード 0） | 改行を前提にしていない（最後の文字も `EOF` の前に処理される） |
| `missing.txt` | 標準エラーに `fopen: No such file or directory`，終了コード 1。`missing.txt` は作られない | 存在しないファイルは`r`で作られない |
| 引数欄を空にする | 標準エラーに `usage: ReadText filename`，終了コード 1 | ファイル名を受け取れない（`argc` が 1） |
| 引数欄を`""`にする | 標準エラーに `usage: ReadText filename`，終了コード 1 | 空のファイル名を拒否する（`argc` は 2 だが `argv[1][0] == '\0'`） |

実際の出力（`(終了コード n)` は追記）:

```text
$ ReadText empty.txt              ← 0 バイトのファイル
(終了コード 0)
$ ReadText no_newline.txt         ← "Hello\nFile"（10 バイト）
Hello
File$                             ← 改行がないので次のプロンプトが同じ行に続く
$ ReadText missing.txt
fopen: No such file or directory
(終了コード 1)
$ ReadText
usage: ReadText filename
(終了コード 1)
$ ReadText ""
usage: ReadText filename
(終了コード 1)
```

`perror` の文言は Windows（UCRT）でも `fopen: No such file or directory` で同じ。

### 空白を含むファイル名

```text
$ ReadText "my input.txt"        ← 引数は 1 個（argv[1] = my input.txt。引用符は含まれない）
Hello
File
$ ReadText my input.txt          ← 引数は 2 個（argv[1] = my，argv[2] = input.txt）。argc が 3 なので拒否
usage: ReadText filename
(終了コード 1)
```

うまくいかないときは `input.txt` に戻し，「内容」「名前」「作業ディレクトリ」を 1 つずつ変えて原因を切り分けさせる。

### 採点のポイント・よくある誤り

- `input.txt` が `x64\Debug\` やソリューションのフォルダにある（作業ディレクトリが `$(ProjectDir)` でない）→ `fopen: No such file or directory`。
- `input.txt.txt`（拡張子非表示），BOM 付き UTF-8 で保存（先頭に `EF BB BF` の 3 バイトが増え，表示の先頭に余分な文字が出る）。
- 「コマンド引数」に `ReadText.exe input.txt` と書く → `argc` が 3 になり usage。
- `char ch = fgetc(fp);` で受ける（`EOF` と `0xFF` を区別できない），`while (!feof(fp))` で回して最後に `EOF` を 1 回余分に処理する。
- `fopen` の `NULL` を調べずに `fgetc` へ渡す，`fclose(NULL)` を呼ぶ。`ferror`・`fclose` の戻り値を見ていない。

## 課題1（続き）　行の長さを表示する（`LineLengths`）

**要点**: `fgets` は改行を配列に残す。改行を**実際に読んだときだけ**除く。容量（31 文字 + 終端）ちょうどで改行がないときは，次の 1 文字で「31 文字の行」か「長すぎる行」かを区別する。

解答: [LineLengths/line_lengths.c](LineLengths/line_lengths.c)（講義の `line_lengths.c` にコメントを加えたもの）。データ: [LineLengths/input.txt](LineLengths/input.txt)。

```text
$ LineLengths input.txt
5
4
```

### 表「入力の1行」（記入済み）

| 入力の1行 | 改行の有無 | 期待する長さ |
| --- | --- | ---: |
| `ABC` | あり | 3 |
| `ABC` | なし | 3 |
| 空行 | あり | 0 |
| `A`を31個 | あり・なし | どちらも 31 |
| `A`を32個 | あり・なし | どちらも長さは表示しない（`line too long`・`read or output error` を標準エラーに出し，終了コード 1） |

実際の出力（各ファイル 1 行だけ）:

```text
$ LineLengths abc.txt      ← "ABC\n"         → 3
$ LineLengths abc.txt      ← "ABC"           → 3
$ LineLengths empty_line.txt ← "\n"          → 0
$ LineLengths a31.txt      ← A×31 + "\n"     → 31
$ LineLengths a31.txt      ← A×31            → 31
$ LineLengths a32.txt      ← A×32 + "\n"（改行なしも同じ）
line too long
read or output error
(終了コード 1)
$ LineLengths empty.txt    ← 空ファイル: 何も表示しない（終了コード 0）
```

- 31 文字で改行あり: `fgets` は `A`×31 と終端で配列が一杯になり，改行は配列に入らない → 次の `fgetc` が `'\n'` なので 31 文字の行（改行はここで読み捨てられる）。
- 31 文字で改行なし: 次の `fgetc` が `EOF` → 31 文字の行。
- 32 文字: 次の `fgetc` が 32 文字目の `A` → 長すぎるので，残りを 2 行目として数えずに閉じて終了する（テスト `too_long_after_line`: `ABC` の後に 32 文字の行があると `3` だけ表示して終了し，3 行目は処理しない）。
- 環境差: Windows のテキストモードは CRLF を LF に変換するので，メモ帳で作った CRLF のファイルでも結果は同じ。Linux/macOS で CRLF のファイルを読むと `\r` が残り，`ABC` が 4 になる。

**説明すること**: `strlen(line)` から常に 1 を引くと，最後の行に改行がない `ABC` は `strlen` が 3 なので 2 になってしまう（最後の `C` を改行と誤って除く）。
`fgets` が改行を配列に入れるのは「改行まで読めたとき」だけで，ファイルの最後の行や容量で切れた行には改行がない。
そこで `line[length - 1] == '\n'` を確かめ，改行を実際に読み取ったときだけ 1 バイト除く（`length > 0` も先に調べて `line[-1]` を読まない）。

### 採点のポイント・よくある誤り

- `strlen(line) - 1` を無条件に使う（改行なしの `ABC` が 2，`length` が 0 のときは `size_t` の巨大な値になる）。
- 31 文字・改行なしを「長すぎる」と誤判定する，32 文字の行を 31 と 1 の 2 行として数える。
- 空ファイルで `0` を表示する（行がないので何も表示しないのが正しい）。

---

## 課題2　数値引数の検査（`ParseNumber`）

**要点**: `argv[1]` は数値ではなく文字列。`strtol` の `end`（変換が終わった位置）と `errno == ERANGE`，範囲 0〜100 を組み合わせて，
「数字がない」「余分な文字が残る」「`long` の範囲外」「課題の範囲外」をすべて拒否する。

### 本体（講義の `parse_number.c`）と検証表

解答: [ParseNumber/parse_number.c](ParseNumber/parse_number.c)（講義の `parse_number.c` に先頭のコメントだけを加えたもの）。既定の引数（`run.args`）は `42`。
次の実行例と表の値はすべて本体のテスト（[ParseNumber/tests](ParseNumber/tests)）にしている。

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: ParseNumber integer\n");
        return 1;
    }
    char *end;
    errno = 0;
    long value = strtol(argv[1], &end, 10);
    if (argv[1] == end || *end != '\0' || errno == ERANGE ||
        value < 0 || value > 100) {
        fprintf(stderr, "expected an integer from 0 to 100\n");
        return 1;
    }
    printf("%ld\n", value);
    return 0;
}
```

演習ページの順（42，0，100，101，-1，`12x`，非常に長い整数）の実行結果:

```text
$ ParseNumber 42
42
$ ParseNumber 0
0
$ ParseNumber 100
100
$ ParseNumber 101
expected an integer from 0 to 100
(終了コード 1)
$ ParseNumber -1
expected an integer from 0 to 100
(終了コード 1)
$ ParseNumber 12x
expected an integer from 0 to 100
(終了コード 1)
$ ParseNumber 999999999999999999999999999999
expected an integer from 0 to 100
(終了コード 1)
```

### 表「境界と文字列の形を確かめる」（記入済み）

| 引数欄 | 期待する結果（実際の結果） | 注目点 |
| --- | --- | --- |
| 0 | `0` を表示，終了コード 0 | 下限を含む |
| 100 | `100` を表示，終了コード 0 | 上限を含む |
| +42 | `42` を表示，終了コード 0 | 先頭の符号は許す |
| `" 42"` | `42` を表示，終了コード 0 | 先頭の空白は`strtol`が読み飛ばす |
| `"42 "` | `expected an integer from 0 to 100`，終了コード 1 | 末尾の空白はこのコードでは拒否（`*end` が `' '`） |
| `12x` | `expected an integer from 0 to 100`，終了コード 1 | 途中までの12だけで成功にしない（`*end` が `'x'`） |
| `abc` | `expected an integer from 0 to 100`，終了コード 1 | 数字を読めない（`end == argv[1]`） |
| 42 50 | `usage: ParseNumber integer`，終了コード 1 | 引数が多すぎる（`argc` が 3） |

そのほか: 引数なしは `usage: ParseNumber integer`（終了コード 1）。`""`（空文字列）は `end == argv[1]` なので `expected an integer from 0 to 100`（終了コード 1，テスト `empty_arg`）。

**極端に長い整数**: `999999999999999999999999999999` は `strtol` が `LONG_MAX` を返し `errno` を `ERANGE` にするので拒否される。
`long` は Windows x64 (MSVC) では 4 バイト（最大 2147483647），Linux x64 では 8 バイト（最大 9223372036854775807）。
例えば `3000000000` は Windows では `ERANGE`，Linux では `long` に収まって `value > 100` で拒否される（どちらも `expected an integer from 0 to 100`，テスト `ten_digits`）。理由は違っても両方で拒否されるのは，
「桁数」ではなく `errno` と範囲で判断しているから。「10 桁なら必ず範囲外」とは決められない。

### 複数の数値を合計するなら（variant `sum`）

本体の `main` の検査・変換部分（`if (argc != 2)` から `printf("%ld\n", value);` まで）を演習ページの断片へ置き換え，最後は元の `return 0;` で終わる版。
`ParseNumber/CMakeLists.txt` が `ParseNumber_sum` として生成してテストしている（[variants/tests/sum--*](ParseNumber/variants/tests)）。

```c
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 11) {
        fprintf(stderr, "expected 1 to 10 integers\n");
        return 1;
    }
    /* 各値は 0〜100，最大 10 個なので合計は 1000 以下で long の範囲内 */
    long total = 0;
    for (int i = 1; i < argc; ++i) {
        char *end;
        errno = 0;
        long value = strtol(argv[i], &end, 10);
        if (end == argv[i] || *end != '\0' || errno == ERANGE ||
            value < 0 || value > 100) {
            fprintf(stderr, "invalid integer\n");
            return 1;
        }
        total += value;
    }
    printf("%ld\n", total);
    return 0;
}
```

各値 0〜100・最大 10 個なので合計は最大 1000 で，配列を作らず `long total` へ順に加えられる（オーバーフローしない）。実行結果（`ParseNumber_sum`）:

```text
$ ParseNumber_sum 12 23 34
69
$ ParseNumber_sum 0 100
100
$ ParseNumber_sum 12 x 34
invalid integer
(終了コード 1)
$ ParseNumber_sum
expected 1 to 10 integers
(終了コード 1)
$ ParseNumber_sum 1 2 3 4 5 6 7 8 9 10 11      ← 11 個（テスト sum--eleven_values）
expected 1 to 10 integers
(終了コード 1)
$ ParseNumber_sum 42 50                          ← テスト sum--two_values
92
```

`12 x 34` では `12` を加えた後に `x` で失敗するが，合計は表示しない（途中までの合計を結果として扱わない）。テストでは 100 を 10 個（合計 1000），11 個（拒否），101・-1・`12x`・非常に長い整数も確かめている。

### 引数を表示して文字列を探す（`Arguments`）

解答: [Arguments/arguments.c](Arguments/arguments.c)。`argv[1]` から `argv[argc - 1]` を `arg番号=文字列` で表示し，北陸 3 県の名前と一致したら
フラグを立て，ループの後で `hokuriku!` を 1 回だけ表示する（一致のたびに表示すると `fukui ishikawa` で 2 回になる）。

```text
$ Arguments nagano ishikawa
arg1=nagano
arg2=ishikawa
hokuriku!
$ Arguments fukui ishikawa
arg1=fukui
arg2=ishikawa
hokuriku!
$ Arguments                       ← 何も表示しない
$ Arguments Toyama
arg1=Toyama
$ Arguments "toyama city" toyama        ← テスト space_and_toyama
arg1=toyama city
arg2=toyama
hokuriku!
```

`Toyama` は `strcmp` が大文字と小文字を区別するので `toyama` と一致しない。`"toyama city"` も 1 個の引数で，内容が `toyama` ではないので一致しない。

**文字列の比較で `==` を使わない理由**: `argv[i] == "toyama"` は 2 つの `char *`（文字列の先頭アドレス）を比べる式で，文字の並びは比べない。
`argv[i]` は起動時に用意された引数の領域を，`"toyama"` はプログラム中の文字列リテラルを指すので，内容が同じでもアドレスは別で，結果は常に偽になる
（同じ内容の文字列リテラル同士でも同じ場所に置かれる保証はない）。内容の比較は `strcmp(argv[i], "toyama") == 0` で行う（第6回・第9回）。

### 採点のポイント・よくある誤り

- `atoi` を使う（`12x` が 12，`abc` が 0 になり失敗を区別できない），`end` を調べない，`errno = 0;` を `strtol` の前に書かない。
- `strtol` の結果をいったん `int` に入れてから範囲を調べる（`long` が 8 バイトの Linux では，`int` に収まらない値が変換で別の値になり，範囲の検査をすり抜けることがある）。
- `argc` を調べずに `argv[1]` を使う（引数なしで `NULL` を `strtol` へ渡す）。
- 合計版で，失敗した後に途中までの合計を表示する，引数 11 個を受け付ける。
- `Arguments` で `hokuriku!` を一致のたびに表示する，`==` で比較する，`i = 0` から始めてプログラム名を表示する。

---

## 課題3　バイト列を保存する（`Binary`）

**要点**: `wb`/`rb` は改行変換をしない。`fread`/`fwrite` の戻り値は「処理した要素の個数」で，`size = 1` のときだけバイト数と一致する。
読んだ個数 `n` だけを使い，配列の残り（未初期化）や `%s` を使わない。

### 本体（講義の `binary.c`）

解答: [Binary/binary.c](Binary/binary.c)（講義の `binary.c` にコメントを加えたもの。`data` は `{0x41, 0x00, 0x42, 0x0A}`）。

```text
$ Binary
41 00 42 0A
```

`bytes.bin` は 4 バイト（`41 00 42 0A`）。途中の `00` も普通のデータとして読める（文字列ではないので `%s` で表示しない）。
繰り返し実行すると同じ名前のファイルを上書きし，常に 4 バイトになる（テスト `overwrite`: 20 バイトの古い `bytes.bin` があっても 4 バイトになる）。

**読み取った個数だけを使う**（variant `show_n`）: `buffer` は 16 要素だが，`fread` が返す `n` は 4。表示するのは `buffer[0]`〜`buffer[3]` だけで，残り 12 個は値が決まっていない（読んではいけない）。
`n` を確かめるために，表示のループの直前へ 1 行足した版:

```c
    printf("n=%zu\n", n);   /* size=1 なので n は読めたバイト数 */
    for (size_t i = 0; i < n; ++i) {
```

```text
$ Binary_show_n
n=4
41 00 42 0A
```

`size = 1` なので `n` はバイト数と一致する。ファイルが 16 バイトより大きいと 1 回の `fread` では全部読めない。「`fread` を呼んだ = ファイル全体を読んだ」ではない。

### UTF-8 をバイトとして観察する（variant `utf8_a`）

`data` を次の 4 バイトに置き換えた版（`Binary_utf8_a`）:

```c
    /* ソースに日本語を直接書かずに，UTF-8 の「あ」（E3 81 82）と LF をバイト列で指定する（BOM は付けない） */
    const unsigned char data[] = {0xE3, 0x81, 0x82, 0x0A};
```

```text
$ Binary_utf8_a
E3 81 82 0A
```

`bytes.bin` は 4 バイト（`E3 81 82 0A`）。`E3 81 82` が UTF-8 の「あ」（U+3042），`0A` が LF。BOM（`EF BB BF`）は付けていないので 7 バイトにはならない。
`wb` で書いているので，Windows でも `0A` は CRLF（`0D 0A`）に変換されず 4 バイトのまま（テキストモード `w` で書くと Windows では 5 バイトになる）。
画面に「あ」が出るかどうか（コンソールのコードページ）ではなく，書いたバイトと読み返したバイトが一致することを確認する課題。

### バイト順を調べる（`ByteOrder`）

解答: [ByteOrder/byte_order.c](ByteOrder/byte_order.c)。講義の観察用断片を別の `main` にし，`sizeof value` を `%zu` で表示してから 1 バイトずつ 16 進数で表示する。
最後に演習ページの 2 進数表示の断片を加えた。

本体（`unsigned short value = 1;`）:

```text
$ ByteOrder
sizeof value = 2
01 00
00000001
```

値を `0x1234` へ変更した版（variant `value_0x1234`，`unsigned short value = 0x1234;`）:

```text
$ ByteOrder_value_0x1234
sizeof value = 2
34 12
00000001
```

- Windows x64（MSVC）・Linux x64・macOS（Apple Silicon）はいずれもリトルエンディアンで，`unsigned short` は 2 バイト。どれも同じ表示になる。
  ビッグエンディアンの処理系なら `00 01`・`12 34` になる（テストはリトルエンディアンを前提にしている）。
- 先に `0x34` があっても，数値が `0x3412` に変わったわけではない。値は `0x1234` のままで，**メモリに置く複数バイトの順序**が下位バイトからなだけ。
- 1 バイトの中のビットは反転しない。2 進数表示は上位ビット（bit 7）から並べるので，`1` は `00000001`。

### 採点のポイント・よくある誤り

- `fopen("bytes.bin", "w")`（`b` なし）で書き，Windows で `0A` が `0D 0A` になって 5 バイトになる。
- `buffer` の 16 個すべてを表示する，`printf("%s", buffer)` で表示する（`00` で止まる・終端がない）。
- `fwrite`/`fread` の戻り値をバイト数と思い込む（`size` が 1 でないときは要素数）。`fclose` の戻り値を見ていない。
- エンディアンを「ビットの並びが逆」と説明する。`sizeof` を使わず 2 と決め打ちする。

---

## 課題4　テキストを書き出す（`WriteText`）

**要点**: `w` は開いた時点で以前の内容を消す，`a` は末尾へ追記する，`wx` は既存ファイルがあれば開くのに失敗する。
`fprintf` が成功しても，バッファに残った出力は `fclose` のときに書かれるので `fclose` の戻り値も調べる。

### 本体（モード `w`）

解答: [WriteText/write_text.c](WriteText/write_text.c)（`fopen("scores.txt", "w")`）。画面には何も表示しない（結果はファイル）。
IDE で何回実行しても `scores.txt` は 3 行のままなので，本体はこの版にしている。

```text
$ WriteText            ← 1 回目
$ ReadText scores.txt  ← 課題1のプログラムで読み返す
72
85
60
$ WriteText            ← 2 回目（同じ条件）: 再び 3 行。6 行にはならない
```

`scores.txt` のバイト数: Windows（テキストモードで `\n` が CRLF になる）では 3 行 ×（2 文字 + CR LF）= **12 バイト**，Linux/macOS では **9 バイト**。
`"wb"` で書けば Windows でも 9 バイトになる（「バイナリで保存した場合とバイト数が異なることがある」の答え）。`ReadText` で読み返した表示はどちらも同じ。

### モードを `a` に変えた版（variant `mode_a`）

```c
    /* a: ファイルがなければ作り，あれば以前の内容を残して末尾へ追記する */
    FILE *fp = fopen("scores.txt", "a");
```

```text
（scores.txt が 3 行ある状態で）
$ WriteText_mode_a     → 6 行（72 85 60 72 85 60）
$ WriteText_mode_a     → 9 行
（scores.txt を削除してから）
$ WriteText_mode_a     → 3 行（a はファイルがなければ新しく作る）
```

（行数は実行後に `scores.txt` を数えたもの。テスト `mode_a--new_file`・`mode_a--append_to_3_lines`・`mode_a--append_to_6_lines` で内容まで比較している。）

### 表「上書きと追記を比較する」（実際の結果）

| モード | 実行前に3行ある場合 | 注意 | 確かめたこと（テスト） |
| --- | --- | --- | --- |
| `w` | 今回の3行だけになる | 以前の内容を消す | 3 行 → 3 行，`old data` などの別の内容 → 3 行（本体の `overwrite_*`） |
| `a` | 以前の3行と今回の3行で6行 | 繰り返すたびに増える | 3 → 6 → 9 行，なければ 3 行で作成（`mode_a--*`） |
| `wx` | 開くのに失敗 | 既存ファイルを保護する | `fopen: File exists`，終了コード 1，元の内容のまま（`mode_wx--existing_file`）。なければ 3 行で作成 |

`wx` の版（variant `mode_wx`，`fopen("scores.txt", "wx")`）の実行結果:

```text
（scores.txt がある状態で）
$ WriteText_mode_wx
fopen: File exists
(終了コード 1)
```

`wx`（`x` は C11 から標準）は MSVC（UCRT）でも使える。失敗しても自動で `w` に切り替えず，別の未使用の名前を指定する。

**説明すること**（`fclose` の戻り値を調べる理由）: `fprintf` はデータをメモリ上のバッファへ書いた時点で成功を返すことがあり，
実際にディスクへ書くのはバッファが一杯になったときや `fclose` のときになる。ディスクの容量不足・書き込み権限・ネットワークドライブの切断などの失敗は，
その最後の書き込み（`fclose` の中）で初めて分かる。`fclose` が `EOF` を返したら，ファイルは不完全かもしれないので失敗として報告する（解答は `write error: scores.txt may be incomplete` を出して終了コード 1）。
終了時の自動処理（`return` 後のクローズ）に任せると，この失敗を検出できない。

### 採点のポイント・よくある誤り

- 練習用フォルダ以外（大事なファイル）を出力先にする。`scores.txt` 以外で `a` の実験をする。
- 「2 回実行したら 6 行になるはず」と予測して `w` の意味を取り違える／`a` の結果が前回の残りか今回の結果か確かめない（更新日時と内容を見る）。
- `fprintf` の戻り値（負ならエラー）や `fclose` の戻り値を見ない。`fopen` 失敗時に `perror` せず `NULL` へ書く。

---

## 発展1　数値をテキスト・バイナリで往復する（`NumberFormats`）

**要点**: 同じ 3 つの `double` を，テキスト（個数の行 + 値を `%.2f` で 3 行）とバイナリ（個数 1 バイト + `double` 3 個のメモリ表現）で保存し，読み戻して比べる。
テキストは書式で桁が失われることがあり，バイナリは同じ処理系なら値をそのまま戻せる。ヘッダの個数は配列の要素数と一致するか確かめてから値を読む。

解答: [NumberFormats/number_formats.c](NumberFormats/number_formats.c)。`write_text`・`write_binary`・`read_text`・`read_binary` の 4 関数に分け，
それぞれが開いたファイルを必ず閉じ，失敗なら 0 を返す。`main` はどれかが失敗したら値を表示せずに終了コード 1 で終わる。

### 本体（`data` が `{0.5, 1.25, -2.0}`，表示が `%.2f`）

```c
    const double data[COUNT] = {0.5, 1.25, -2.0};
    ...
    printf("text=%.2f %.2f %.2f\n", text_values[0], text_values[1], text_values[2]);
    printf("binary=%.2f %.2f %.2f\n", binary_values[0], binary_values[1], binary_values[2]);
```

```text
$ NumberFormats
text=0.50 1.25 -2.00
binary=0.50 1.25 -2.00
```

演習ページの期待する表示と一致する。作られたファイル:

```text
numbers.txt（Linux: 18 バイト，Windows: 22 バイト）
3
0.50
1.25
-2.00

numbers.bin（25 バイト = 1 + 3 * sizeof(double)。16 進数）
03 | 00 00 00 00 00 00 E0 3F | 00 00 00 00 00 00 F4 3F | 00 00 00 00 00 00 00 C0
     0.5                       1.25                      -2.0
```

### サイズの見方

- `numbers.bin` は `1 + 3 * sizeof(double)` = 1 + 3 × 8 = **25 バイト**（Windows x64・Linux x64 とも `double` は 8 バイトの IEEE 754 倍精度，リトルエンディアンなので上と同じバイト列）。
- `numbers.txt` は 4 行・文字数 14（`3`・`0.50`・`1.25`・`-2.00`）+ 改行 4 個。改行が LF なら 18 バイト，Windows のテキストモード（CRLF）なら **22 バイト**。
  この小さな例ではテキストの方が小さい。テキスト・バイナリのどちらが常に小さい・速いということはない。
- `numbers.bin` は「同じ処理系で読み戻す専用」。`double` のサイズ・表現・バイト順が違う処理系とは交換できない。

### `data[0]` を 0.125，表示を `%.3f` にした版（variant `precision_0125`）

保存の書式は `%.2f` のまま，`data[0]` を 0.125 にし，最後の 2 行の表示書式だけ `%.3f` に変えた版:

```c
    const double data[COUNT] = {0.125, 1.25, -2.0};
    ...
    printf("text=%.3f %.3f %.3f\n", text_values[0], text_values[1], text_values[2]);
    printf("binary=%.3f %.3f %.3f\n", binary_values[0], binary_values[1], binary_values[2]);
```

```text
$ NumberFormats_precision_0125
text=0.120 1.250 -2.000
binary=0.125 1.250 -2.000
```

`numbers.txt` は `3`・`0.12`・`1.25`・`-2.00`（保存した時点で 0.125 の 3 桁目が失われた），`numbers.bin` の 1 個目は `00 00 00 00 00 00 C0 3F`（0.125 そのもの）。
バイナリ側は文字列への変換を通らないので 0.125 を保つ。テキスト側が 0.12 と 0.13 のどちらになるか（丸めの境界）は本質ではない：0.125 は 2 進数で正確に表せるちょうど中間の値で，
glibc（Linux）と現在の Windows の UCRT はどちらも偶数側へ丸めて `0.12` を保存するので `text=0.120` になる。
ただし古い UCRT や，旧来の丸めに戻す `legacy_stdio_float_rounding.obj` をリンクした場合は `0.13` を保存して `text=0.130` になる（学生の結果が 0.130 でも誤りではない）。
注目するのは「`%.2f` で保存した時点で桁が失われ，0.125 とは一致しない」こと。

### 補足

- `fscanf` は自分がこの実行で書いた小さなファイルを読むためのもの。外部ファイルの厳密な検査器ではない（`%d` の範囲外，余分なデータなどは調べていない）。外部テキストの検査は発展2の `CheckValue` の形で行う。
- 時間を測って速度を比べる場合は，画面出力・ディスクのキャッシュ・測定回数の影響が大きく，この小さな例から一般的な結論は出せない。

### 採点のポイント・よくある誤り

- バイナリを `"w"`/`"r"`（`b` なし）で開く（Windows で `0A` を含むバイト列が変換され，値が壊れる・サイズが 25 にならない）。
- `fwrite(data, sizeof data, ...)` と `fwrite(data, sizeof(double), 3, ...)` の要素数・サイズの取り違え，戻り値をバイト数と比べる。
- 読んだヘッダの個数をそのまま配列の長さとして使う（3 を超える値で配列の外へ読む）。
- テキストの丸めを「`double` が不正確だから」と説明する（原因は保存書式 `%.2f` で桁を落としたこと）。

---

## 発展2　二乗の一覧を書き出して検索する

保存形式（講義「保存形式を先に決める」）: 1 行目が個数 `N`（0〜100），続く `N` 行が 0〜`N`−1 の二乗（0〜9801）。ASCII・1 行 1 整数。

### 書く側：`WriteSquares`

**要点**: 引数 `N` を `strtol` で 0〜100 に検査し，`wx` で新しいファイルだけを作る（既存のファイルを上書きしない）。`i` は 99 以下なので `i * i` は 9801 以下でオーバーフローしない。

解答: [WriteSquares/write_squares.c](WriteSquares/write_squares.c)。成功時は何も表示しない（結果はファイル）。

```text
$ WriteSquares 4 squares.txt
（squares.txt の内容）
4
0
1
4
9
$ WriteSquares 4 squares.txt        ← 2 回目: 既にあるので失敗し，元のファイルはそのまま
fopen: File exists
(終了コード 1)
$ WriteSquares 4 squares2.txt       ← 未使用の名前なら成功
$ WriteSquares 0 sq0.txt            ← 内容は「0」の 1 行だけ
$ WriteSquares 100 sq100.txt        ← 101 行，最後の行は 9801
$ WriteSquares 101 x.txt
expected a count from 0 to 100
(終了コード 1)
$ WriteSquares 4
usage: WriteSquares count filename
(終了コード 1)
```

テストでは `N` = 4・0・100 の内容，既存ファイルの保護，未使用の名前，空白を含む名前（`"my squares.txt"`），`N` = 101・-1・`12x`・非常に長い整数，引数の個数の誤り，空のファイル名を確かめている。
書き込み途中で失敗した場合は `write error: <名前> may be incomplete` を出して終了コード 1（途中までのファイルが残るので，完成品として使わない）。

### 読む側：`CheckValue`

**要点**: ヘッダの個数を信用せず，その個数の行が本当にあるか，各行が範囲内の整数 1 個か，余分な行がないかを最後まで確かめてから結果を表示する。
1 行は `fgets` で文字列として読み（容量を決める），`strtol` で検査する（`%d` では範囲外を安全に扱えない）。

解答: [CheckValue/check_value.c](CheckValue/check_value.c)。
- `read_value`: 1 行（30 バイト + 改行 + 終端の配列）を読み，改行と末尾の空白（スペース・タブ・CR）を除いて，0〜上限の整数 1 個なら 1，行がなければ 0，形式の誤りなら -1，
  31 バイト以上の行なら -2 を返す。失敗したときは値を書き込まないので，呼び出し側は得られなかった値を使わない。先頭の空白は `strtol` が読み飛ばす。
- `report_line_error`: 失敗の種類ごとに `line N: missing count/value`・`line N: line too long`・`line N: expected a ...`・`line N: read error` を標準エラーへ出す。
- `check_file`: 1 行目を個数（0〜100）として読み，続く `N` 行を値（0〜9801）として読む。見つけても `return` せずフラグを立てるだけにし，
  `N` 行の後に 1 文字でも残っていれば（空行も）`extra data` で拒否する。最後の行の改行はなくてもよい。
- `main`: 引数の個数と検索値（0〜9801）を先に検査し，ファイルを開いて `check_file` を呼び，必ず `fclose` する。形式が正しいときだけ `found`/`not found` を表示する。

作業ディレクトリは `CheckValue` のフォルダ。`WriteSquares` で作った `squares.txt` をここへコピーしたものが [CheckValue/squares.txt](CheckValue/squares.txt)（同じ相対パス `squares.txt` でも，プロジェクトが違えば別のフォルダを探す）。

```text
$ CheckValue squares.txt 9
found
$ CheckValue squares.txt 12
not found
$ CheckValue squares.txt 9802
expected a value from 0 to 9801
(終了コード 1)
```

形式は正しいが二乗ではないファイル（`2`・`5`・`6`）も受け付ける（`CheckValue bad.txt 6` → `found`）。このプログラムは「ファイル形式の検査」をしているだけで，
値が 0，1，4，9 という特定の計算結果になっているかは検査しない。また，1 行目の個数そのものは検索対象ではない（`2`・`0`・`1` のファイルで 2 を探すと `not found`）。

**前提として検査しないこと**: 形式の約束（ASCII・`NUL` なし）は前提とし，`NUL` や非 ASCII のバイトは検査しない。
例えば `9`，`NUL`，`x` の行は `fgets` の後の文字列が `"9"` で終わるので 9 として読む（テスト `nul_not_checked` → `found`）。
BOM 付き UTF-8 で保存した `squares.txt` は，先頭の `EF BB BF` が数字ではないので `line 1: expected a count from 0 to 100` で拒否される（テスト `bad_bom`）。

### 表「異常なデータも別ファイルで確認する」（記入済み・実際の結果）

正常な `squares.txt`（`4`・`0`・`1`・`4`・`9`）のコピーを `bad.txt` として変更し，`CheckValue bad.txt 9` で実行した。

| 変更 | 期待する結果（実際の結果） |
| --- | --- |
| ヘッダを4のまま最後の9を削除 | `line 5: missing value`，終了コード 1（個数不足） |
| 値の1行を`abc`へ変更 | `line 3: expected a value from 0 to 9801`，終了コード 1（3 行目の値 `1` を `abc` にした場合） |
| 値の1行を99999へ変更 | `line 4: expected a value from 0 to 9801`，終了コード 1（範囲外。4 行目の値 `4` を 99999 にした場合） |
| 最後に余分な数値や空行を追加 | `line 6: extra data`，終了コード 1（`16` を追加しても，空行を追加しても同じ） |
| ヘッダを101へ変更 | `line 1: expected a count from 0 to 100`，終了コード 1 |
| 正常な最終行の改行だけ削除 | `found`，終了コード 0（最後の行の改行はなくてよい） |
| ファイル全体を空にする | `line 1: missing count`，終了コード 1 |

（行番号はファイルの何行目かで，表示はすべて標準エラー。どの異常でも `found`/`not found` は表示しない。）

そのほかテストで確かめていること: 値の前後の空白・タブ（受け付ける），CRLF のファイル（受け付ける），途中の空行・空白だけの行（拒否），
30 バイトの行（受け付ける）と 31 バイトの行（`line 5: line too long` で拒否。31 バイト以上のヘッダも `line 1: line too long`），`N` = 0 のファイル，`N` = 100 のファイルで 9801（`found`）と 9800（`not found`），
**見つけた後の行が壊れている場合**（`4`・`0`・`1`・`abc`・`9` で 1 を探すと，1 は 3 行目で見つかるが 4 行目の `abc` で `line 4: …` となり `found` は出ない），
検索値 9802・-1・`12x`，存在しないファイル，空白を含むファイル名，引数の個数の誤り，空のファイル名。

```text
$ CheckValue long.txt 9      ← 5 行目が空白 30 個 + "9"（31 バイト）
line 5: line too long
(終了コード 1)
```

環境差: Windows のテキストモードは CRLF を LF に変換するので，CRLF のファイルでも「30 バイト + 改行」の行は受け付ける。
Linux/macOS で CRLF のファイルを読むと CR が行に残るため，30 バイトの値の行は CR 込みで 31 バイトとなり `line too long` で拒否される（29 バイト以下の行は CR を末尾の空白として除くので受け付ける）。

`read_value` が失敗したときは，その呼び出しで得られなかった値を読まない（`*value` は書き換えず，呼び出し側もすぐ失敗として終わる）。
検索だけなら 1 個ずつ比較すれば足りるので，値全体を配列に保存していない。

### 採点のポイント・よくある誤り

- `WriteSquares` で `w` を使う（既存の `squares.txt` を上書きする），`wx` が失敗したら `w` で開き直す。
- `CheckValue` を `fscanf(fp, "%d", ...)` だけで書く（`12x`・行の区切り・空行・余分な行・範囲外を区別できない）。
- ヘッダの個数をそのまま信用してループし，行が足りなくても成功にする。見つけた直後に `return` して残りを検査しない。
- 30 バイトを超える行を 2 行として読んでしまう（`fgets` の容量で切れた残りを次の値として扱う）。
- `CheckValue` の作業ディレクトリに `squares.txt` をコピーしていない（`WriteSquares` のフォルダにしかない）。
- メモ帳などで `squares.txt` を **BOM 付き UTF-8** で保存し直すと，先頭の `EF BB BF` のため `line 1: expected a count from 0 to 100` で拒否される。
  学生が「正しいファイルなのに拒否される」と言ったら，まず BOM（エンコードの「UTF-8 (BOM 付き)」）を疑う。これは仕様どおりの拒否で，プログラムの誤りではない。

---

## 確認問題

1. **よくない。** `fopen` が `NULL` を返したときはストリームが開いていないので，閉じるものがない。`fclose` には `fopen` が成功して返したポインタだけを渡す。
   `fclose(NULL)` は標準 C では未定義の動作で，MSVC では無効なパラメーターとして実行時エラー（デバッグ版ではアサーションのダイアログ）になる。開くのに失敗したら `perror` で診断して終了すればよい。
2. **よくない。** 改行がない最後の行では最後の文字を削ってしまう（`ABC` が 2）。容量で切れた行にも改行はない。`line[length - 1] == '\n'` を確かめ，実際に改行を読んだときだけ除く（`LineLengths`）。
3. `argc` は**個数**しか表さないから。内容は空文字列（`""`），数字でない文字列（`abc`），途中までしか数値でない文字列（`12x`），範囲外（`101`，非常に長い整数），存在しないファイル名などがあり得る。
   個数を確かめた後に，`strtol` の `end`・`errno`・範囲や，`argv[1][0] != '\0'`，`fopen` の結果で内容を検査する（`ParseNumber`・`ReadText`・`WriteSquares`・`CheckValue`）。
4. **そうとは限らない。** `fread` の戻り値は完全に読めた**要素の個数**。`size` が 1 のときだけバイト数と一致する。`fread(buf, 4, 4, fp)` が 3 を返したら 4 バイトの要素が 3 個（12 バイト分）で，
   一部だけ読めた 4 個目は数えられない。また要求より少ないこともあるので，`ferror` と終端を確かめる（`Binary`・`NumberFormats`）。
5. **変換されない。** 拡張子はファイル名の一部で，名前を変えても中のバイトは同じ。テキストとして扱うかバイナリとして扱うかは，`fopen` のモード（`b` の有無）と，読み書きするプログラムが決めた保存形式で決まる。
6. **同じではない。** 「あ」は見た目 1 文字（コードポイント U+3042 の 1 個）だが，UTF-8 では `E3 81 82` の 3 バイト（`Binary` の variant `utf8_a` で確認）。`strlen` はバイト数を数えるので 3 になる。
   見た目の 1 文字が複数のコードポイントからできている場合もあり，バイト数・コードポイント数・見た目の文字数はそれぞれ別。
7. **よくない。** ファイルの個数（ヘッダ）は壊れていたり，わざと大きくされていたりするかもしれない。配列の容量以内か（`NumberFormats` は 3 と一致するか，`CheckValue` は 0〜100 か）を確かめ，
   さらにその個数のデータが本当にあるか（`fread` の戻り値，`CheckValue` の `missing value`）を確かめてから使う。
8. ファイル**全体**が正しい形式であることを確かめてから結果を出すため。途中で見つけた直後に終わると，後ろに `abc`・範囲外の値・余分な行・個数不足があっても `found` と報告してしまい，
   壊れたファイルを正しいデータとして扱うことになる（テスト `bad_after_found`）。検索結果は「形式が正しいファイルの中にあったか」として報告する。

### 講義ページの確認問題（参考）

1. `fopen` の結果を確認する前に `fgetc` を呼んではいけない（`NULL` を渡すと未定義の動作）。
2. `argc = 1` のとき `argv[1]` は `NULL` なので，文字列として使ってはいけない（`%s` や `strtol` に渡さない）。
3. UTF-8 で保存した日本語の `strlen` はバイト数で，見た目の文字数ではない（「あ」は 3）。

## チェックリスト

| 項目 | 確認できる課題と内容 |
| --- | --- |
| 正常な値だけでなく，課題に示された境界の値でも確認した | `ParseNumber`: 0・100（受け付ける），101・-1（拒否），`+42`・`" 42"`・`"42 "`・`12x`・`abc`・非常に長い整数・引数の過不足。合計版の 10 個・11 個。<br>`LineLengths`: 31 文字（改行あり・なし）と 32 文字，空行，空ファイル。<br>`ReadText`: 空ファイル，最後の改行なし，`missing.txt`，引数なし，`""`，空白を含む名前。<br>`WriteText`: `w`・`a`・`wx` を既存ファイルあり・なしで比較。<br>`WriteSquares`: `N` = 0・100・101，既存ファイル。<br>`CheckValue`: 表の 7 種類の異常，0 と 9801，30・31 バイトの行。すべて自動テストにしている |
| 警告を確認し，原因を説明・修正した | すべてのプロジェクトが GCC/Clang の `-Wall -Wextra -Wpedantic -Werror` で警告 0（MSVC `/W4` で問題になる C4996 は `fopen` を使うファイルの先頭の `#define _CRT_SECURE_NO_WARNINGS` で抑止。`%zu` は MSVC 2015 以降で使え，現在の UCRT の `fopen` はモードの `x` に対応している）。<br>学生の提出物でよく出る警告: C4996（`fopen`，`_CRT_SECURE_NO_WARNINGS` がない／`#include` の後に書いた），C4244（`char ch = fgetc(fp);` の `int` → `char`。`/W4` で出る。`long` → `int` は MSVC では同じ 4 バイトなので警告にならないが，Linux では値が変わり得る），C4018/C4389（`size_t` と `int` の比較），C4100（使わない `argc`） |
| 自分の言葉で，処理の流れと使った型を説明できる | `FILE *`（ストリームでありファイルの中身ではない），`fgetc` の戻り値が `int` である理由（課題1），`char *argv[]` と `argc`（課題2），`size_t` と `fread` の戻り値（課題3），`unsigned char *` でオブジェクトの表現を見る（`ByteOrder`），`long` と `strtol`・`errno`（課題2・発展2），`double` のテキスト/バイナリ表現（発展1） |

注: 空文字列の引数は `.args` の空行で表す（空行 1 行だけなら空文字列の引数 1 つ）。`ReadText ""`（`empty_arg`），`ParseNumber ""`（本体 `empty_arg`・合計版 `sum--empty_arg`），`Arguments ""`（`empty_arg`），`WriteSquares 4 ""`，`CheckValue "" 9` を自動テストにしている。
