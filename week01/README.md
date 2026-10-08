# 第1回 演習 解答・解説（プログラミングの基礎）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex01.html>（[ソース](https://github.com/t-yokoga/softprac1/blob/main/docs/ex01.md)）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec01.html>
- 今回の範囲: `#include <stdio.h>`，`int main(void)`，`printf`（文字列リテラルとエスケープシーケンス `\n` `\"` `\\`，書式の `%%`），`return 0;`，コメント。
  変数・繰り返し・`if` は使わない（演習ページ「今回は変数や繰り返しを使わず」）。

## プロジェクト一覧

| 課題 | 内容 | プロジェクト | ソース | テスト |
| --- | --- | --- | --- | --- |
| 1 | 最初のプログラム | `Welcome` | [welcome.c](Welcome/welcome.c)，[CMakeLists.txt](Welcome/CMakeLists.txt) | 3（[basic](Welcome/tests/basic.out)，[variant_one_printf](Welcome/variants/tests/one_printf.out)，[variant_missing_newline](Welcome/variants/tests/missing_newline.out)） |
| 2 | 改行と特殊な文字 | `Message` | [message.c](Message/message.c)，[CMakeLists.txt](Message/CMakeLists.txt) | 3（[basic](Message/tests/basic.out)，[variant_backslash_n_only](Message/variants/tests/backslash_n_only.out)，[variant_blank_line_in_first](Message/variants/tests/blank_line_in_first.out)） |
| 3 | エラーの修正（修正後） | `Broken` | [broken.c](Broken/broken.c) | 1（[basic](Broken/tests/basic.out)） |
| 3 | エラーの修正（修正前，ビルドしない） | `_Broken` | [broken.c](_Broken/broken.c) | なし（ビルドエラーを再現する用） |
| 4 | ソースと実行ファイルの区別（最終版 = Version B） | `Version` | [version.c](Version/version.c)，[CMakeLists.txt](Version/CMakeLists.txt) | 2（[basic](Version/tests/basic.out)，[variant_version_a](Version/variants/tests/version_a.out)） |
| 5 | 発展：文字で図を描く | `House` | [house.c](House/house.c)，[CMakeLists.txt](House/CMakeLists.txt) | 2（[basic](House/tests/basic.out)，[variant_single_backslash](House/variants/tests/single_backslash.out)） |

- どのプログラムも入力を取らず，表示が 1 通りに決まるので，本体のテスト（`basic`）は各 1 ケース（標準出力の完全一致と終了コード 0）。本体 5 件と下の書き換え版 6 件で，合計 11 件。
- README で取り上げた別の書き方・途中版・誤りの例は，本体を変えずに `softprac_add_variant`（各フォルダの `CMakeLists.txt`）でソースの一部を置き換えた版をビルドしてテストしている（期待値は `variants/tests/`）。
  - `Welcome/one_printf`: 2 つの `printf` を 1 つにまとめた版（出力は本体と同じ）
  - `Welcome/missing_newline`: 1 行目の末尾の `\n` を忘れた誤りの例（2 行が 1 行につながる）
  - `Message/backslash_n_only`: `Backslash: \\\n` を `\\n` と書いた誤りの例（`\` と `n` が表示され改行されない）
  - `Message/blank_line_in_first`: 空行を 1 行目の `printf("My first C program\n\n");` で作る版（出力は本体と同じ）
  - `Version/version_a`: 手順 1 の最初の版（`Version A`）
  - `House/single_backslash`: `\` を 1 つしか書かなかった誤りの例（1 行目と 3 行目）
- `_Broken/` は名前が `_` で始まるのでビルド対象外（CMake も `.vs/launch.vs.json` も無視する）。TA がエラーを再現するときは，このファイルを Visual Studio の空のプロジェクトに追加してビルドする。
  診断の行番号を演習ページのコード（1〜7 行目）と一致させるため，説明のコメントはファイルの末尾に置いている。
- 修正後の `Broken/broken.c` も同じ理由でコメントを末尾に置き，行番号を演習ページと一致させている（5 行目が `;` を追加した行）。
- 実行結果は Linux x64（GCC 13.3 / Clang 18.1，`-std=c17 -Wall -Wextra -Wpedantic -Werror`）で実際にビルド・実行した出力。表示は ASCII だけなので MSVC でも同じ表示になる。
  MSVC `/W4 /WX`（Debug・Release・sln）・MinGW・macOS の CI（GitHub Actions）で全プロジェクト（variants・versions を含む）のビルドとテストが成功している（コミット a76876f の時点）。
- MSVC の診断（エラー・警告の番号，文面，行番号）は，この README の作成環境（Linux）では実際に出していない。Microsoft のドキュメントなどに基づく**例**で，文面・行番号はバージョンや言語設定で異なる。GCC/Clang の診断は実際の出力。

### 実行ファイルの場所（このリポジトリと授業の違い）

| 環境 | ソース | 実行ファイル |
| --- | --- | --- |
| 授業の手順（Visual Studio の空のプロジェクト，「ソリューションとプロジェクトを同じディレクトリに配置する」に✓，x64 / Debug） | `...\PL1\week01\Welcome\welcome.c` | `...\PL1\week01\Welcome\x64\Debug\Welcome.exe` |
| 同上（プラットフォームが x86 / Win32 の場合） | 同上 | `...\PL1\week01\Welcome\Debug\Welcome.exe` |
| このリポジトリ（CMake。Visual Studio の「フォルダーを開く」や VS Code） | `week01\Welcome\welcome.c` | `out\build\<プリセット>\bin\week01\Welcome.exe`（Linux では拡張子なし） |

---

## 課題1　最初のプログラム（`Welcome` / `welcome.c`）

**要点**: 講義の `hello.c` と同じ形（`#include` → `main` → `printf` → `return 0;`）で，保存 → ビルド → 実行の流れを一通り行う。行の区切りは文字列中の `\n`。

**解答**: [Welcome/welcome.c](Welcome/welcome.c)（`printf` を 2 回使う方法）

```c
#include <stdio.h>

int main(void)
{
    printf("Welcome to Programming Languages 1.\n");
    printf("I can build and run a C program.\n");
    return 0;
}
```

`printf` 1 回で 2 行を表示する方法でもよい（テスト `Welcome/variant_one_printf` で同じ出力になることを確認）。

```c
    printf("Welcome to Programming Languages 1.\nI can build and run a C program.\n");
```

**実行結果**

```text
Welcome to Programming Languages 1.
I can build and run a C program.
```

**確認すること（`welcome.c` と `Welcome.exe` の保存場所）**

- `welcome.c`（ソースファイル）: プロジェクトフォルダ `...\PL1\week01\Welcome\welcome.c`。ソリューション エクスプローラーでファイルを右クリック →「エクスプローラーでフォルダーを開く」でも確かめられる。
- `Welcome.exe`（実行ファイル）: ビルドで新しく作られるファイルで，ソースと同じフォルダではなく構成ごとの出力フォルダにできる。
  上の設定（x64 / Debug）では `...\PL1\week01\Welcome\x64\Debug\Welcome.exe`。
  正確な場所は，ビルドの「出力」ウィンドウに出る次のような行で確認する（パスは各自の環境で異なる）。

  ```text
  1>Welcome.vcxproj -> C:\Users\<ユーザ名>\Documents\PL1\week01\Welcome\x64\Debug\Welcome.exe
  ```

  OneDrive を使っている場合は `C:\Users\<ユーザ名>\OneDrive\ドキュメント\PL1\...` のようになる。同じフォルダに `.obj` などの中間ファイルもできるが，実行するのは `.exe`。

**採点のポイント・よくある誤り**

- 2 行が演習ページと 1 文字も違わないか（`Languages` の綴り，`1.` のピリオド，`C program.` の末尾のピリオド）。
- 1 行目の末尾の `\n` を忘れると `Welcome to Programming Languages 1.I can build and run a C program.` と 1 行につながる（ビルドは成功し，GCC/Clang の `-Wall -Wextra -Wpedantic` でも警告は出ない。テスト `Welcome/variant_missing_newline` の実際の出力）。
- ファイル名が `welcome.cpp` や `welcome.c.txt` になっていないか。`.cpp` だと C++ としてコンパイルされる。
- `/TC`・C17・`/W4` の 3 つを「すべての構成」「すべてのプラットフォーム」で設定しているか（Debug だけ設定して Release は未設定，などが多い）。
- 「保存場所」の答えが「デスクトップ」「Visual Studio の中」のような曖昧なものでなく，ソースと `.exe` の**フルパス**を別々に書いているか。`.exe` がソースと同じフォルダにあると書いていたら誤り。
- `#include <stdio.h>;` のように前処理指令に `;` を付ける誤り（GCC/Clang では `extra tokens at end of #include directive` の警告，MSVC では例えば C4067 の警告）。

---

## 課題2　改行と特殊な文字（`Message` / `message.c`）

**要点**: エスケープシーケンス（`\n` 改行，`\"` 二重引用符，`\\` バックスラッシュ）と，`printf` の書式の規則 `%%`。空行は `\n` を 2 回続けて作る。

**解答**: [Message/message.c](Message/message.c)

```c
    printf("My first C program\n");
    printf("\n");                       // 2 行目の空行（\n だけを表示する）
    printf("She said, \"Hello!\"\n");
    printf("Backslash: \\\n");          // \\ で \ を 1 文字，続く \n で改行
    printf("Progress: 100%%\n");        // 最後の行の末尾にも改行を入れる
```

空行は `printf("My first C program\n\n");` のように 1 行目に `\n` を 2 つ続けてもよい（テスト `Message/variant_blank_line_in_first` で本体と同じ出力になることを確認）。

**実行結果**

```text
My first C program

She said, "Hello!"
Backslash: \
Progress: 100%
```

出力をバイト単位で見ると（Linux の `od -An -c`。`-An` はオフセットを表示しない指定），空行は `\n` が 2 つ続いたもの，`\\` は `\` 1 文字，`%%` は `%` 1 文字になっている。合計 67 バイト。

```text
   M   y       f   i   r   s   t       C       p   r   o   g   r
   a   m  \n  \n   S   h   e       s   a   i   d   ,       "   H
   e   l   l   o   !   "  \n   B   a   c   k   s   l   a   s   h
   :       \  \n   P   r   o   g   r   e   s   s   :       1   0
   0   %  \n
```

（`od` はバイトを読みやすく表示するため，改行文字 1 バイトを `\n` と書いている。）

**説明すること（ソースに書いた `\n` は，画面に `\` と `n` の 2 文字として表示されるか）**

**表示されない。** 改行として表示される。
文字列リテラルの中の `\n` は，ソースコード上は 2 文字だが，コンパイラが「改行文字」という**1 文字**に置き換えて実行ファイルに入れるエスケープシーケンスである。
`printf` が受け取るのは既に改行文字なので，画面では次の行へ移るだけで `\` と `n` は出ない（上の `od` の出力でも改行は 1 バイト）。
なお Windows では，C ランタイムがテキストモードの標準出力（`stdout`）に書き出すときに改行文字（LF）を CR+LF に変換する。変換するのはコンソールではなく C ランタイムなので，出力をファイルへリダイレクトした場合も CR+LF になる。どちらにしても `\` と `n` の 2 文字にはならない。

`\` と `n` の 2 文字を表示したいときは `\\n` と書く（`\\` が `\` 1 文字，`n` はそのまま）。実際に `message.c` の `Backslash` の行を `printf("Backslash: \\n");` に置き換えて実行すると（テスト `Message/variant_backslash_n_only` の実際の出力），次のように `\n` が文字として表示され，改行されない。

```text
My first C program

She said, "Hello!"
Backslash: \nProgress: 100%
```

（次の `printf("Progress: 100%%\n");` の出力が同じ行に続いている。）

`%%` はエスケープシーケンスではなく `printf` の書式の規則（`%` は変換指定の始まりなので，`%` そのものは `%%` と書く）。`printf` を使わない文字列では `%` は 1 つでよい。

**採点のポイント・よくある誤り**

- 2 行目が本当に空行か（空白だけの行や，空行なしは誤り）。最後の `Progress: 100%` の後にも改行があるか（演習ページに明記）。
- `"Hello!"` の `"` を `\"` にしていない → 文字列がそこで終わるのでコンパイルエラー。GCC: `error: expected ')' before 'Hello'`，Clang: `error: expected ')'`，MSVC の例: `error C2146: 構文エラー: ')' が識別子 'Hello' の前にありません。`（続けて別の診断が出ることもあり，番号・文面はバージョンで異なる）。
- `"Backslash: \"` のように `\` を 1 つしか書かない → `\"` が引用符のエスケープになり，文字列が閉じない。MSVC の例: `C2001`（定数が 2 行目に続いています / newline in constant），GCC: `error: missing terminating " character`。
- `"Backslash: \\n"` と書いて `\` と改行の両方のつもりになっている → `\` と `n` が表示され改行されない（警告なし。上の実行例）。正しくは `\\\n`（`\\` + `\n`）。
- `100%\n` と書く → 書式として不正（`%` の後に変換指定がない）で，動作は未定義。MSVC は例えば `/W4` で C4476（`'printf' : unknown type field character '\n' in format specifier`，表示は環境で異なる），GCC は `warning: unknown conversion type character '\x0a' in format [-Wformat=]`，Clang は `warning: invalid conversion specifier '\x0a'` を出す。警告なので**ビルドは成功してしまう**点を指摘する。
- 円記号（全角の `￥`）を入力している。日本語キーボードでは半角のバックスラッシュが `¥` に見えることがある（講義の注意）。

---

## 課題3　エラーメッセージを読んで修正する（`Broken` / `broken.c`）

**要点**: 構文エラーの診断（ファイル名・行番号・説明）を読む。コンパイラが誤りに気付く場所（6 行目）と，直すべき場所（5 行目）が一致しないことを体験する。

**修正前**（[_Broken/broken.c](_Broken/broken.c)，演習ページのとおり。5 行目の末尾に `;` がない）

```c
#include <stdio.h>

int main(void)
{
    printf("I fixed the error!\n")
    return 0;
}
```

**修正後**（[Broken/broken.c](Broken/broken.c)）: 5 行目の末尾に `;` を追加する。

```c
    printf("I fixed the error!\n");     // 文の終わりに ; を追加した
```

**実行結果（修正後）**

```text
I fixed the error!
```

**記録すること（修正前の診断と，修正した箇所）**

| 項目 | MSVC（例。文面・行番号は環境で異なる） | GCC 13（実際の出力） | Clang 18（実際の出力） |
| --- | --- | --- | --- |
| 診断の番号・種類 | エラー `C2143` | `error` | `error` |
| ファイル | `broken.c` | `broken.c` | `broken.c` |
| 行 | **6**（`return` の行） | 5 行 35 列（5 行目の末尾）。6 行目の `return` も併せて示される | 5 行 35 列 |
| 説明 | 構文エラー: `';'` が `'return'` の前にありません。（英語版: `syntax error: missing ';' before 'return'`） | `expected ';' before 'return'` | `expected ';' after expression` |
| 修正した箇所 | 5 行目 `printf("I fixed the error!\n")` の末尾に `;` を追加 | 同左 | 同左 |

MSVC の「出力」ウィンドウ（ビルド）に出る診断の例（パス・列の有無・言語は環境で異なる）。

```text
1>broken.c
1>C:\Users\<ユーザ名>\Documents\PL1\week01\Broken\broken.c(6,5): error C2143: 構文エラー: ';' が 'return' の前にありません。
1>プロジェクト "Broken.vcxproj" のビルドが終了しました -- 失敗。
========== ビルド: 0 正常終了、1 失敗、0 更新不要、0 スキップ ==========
```

「エラー一覧」には「コード C2143，説明，プロジェクト Broken，ファイル broken.c，行 6」と表示される例。
エラー一覧の表示を「ビルド + IntelliSense」にしていると，IntelliSense の診断（`E0065`，`';' が必要です`）が 5 行目に出ることもある。どちらも原因は同じ 1 か所。

GCC の実際の出力（`gcc -std=c17 -Wall -Wextra -Wpedantic -c broken.c`）:

```text
broken.c: In function 'main':
broken.c:5:35: error: expected ';' before 'return'
    5 |     printf("I fixed the error!\n")
      |                                   ^
      |                                   ;
    6 |     return 0;
      |     ~~~~~~
```

Clang の実際の出力（`clang -std=c17 -Wall -Wextra -Wpedantic -c broken.c`）:

```text
broken.c:5:35: error: expected ';' after expression
    5 |     printf("I fixed the error!\n")
      |                                   ^
      |                                   ;
1 error generated.
```

**なぜ MSVC は 6 行目を指すのか**（上の例のように `return` の行を指す場合）: C では改行は単なる空白で，`printf("...")` の後に改行があっても文は終わらない。
コンパイラは 5 行目の終わりではまだ「式が続くかもしれない」と考えて読み進め，6 行目の `return` が来た時点で初めて「`;` がない」と分かる。
そのため，診断の行（6 行目）の**前の行**（5 行目）を直す必要がある（講義「示された行の前の行も確認」）。
GCC/Clang は「直前のトークンの直後」に位置を戻して 5 行目を指すので，コンパイラによって行番号が異なる。

**手順 3〜4**: 修正して保存し，再ビルドすると「1 正常終了、0 失敗」となり，Ctrl+F5 で `I fixed the error!` が表示される。
ビルドに失敗した状態で Ctrl+F5 を押すと「ビルド エラーが発生しました。続行して、最後に成功したビルドを実行しますか?」と聞かれるが，「いいえ」を選ぶ（今回は初回ビルドが失敗しているので，成功した `exe` はそもそもない）。

**採点のポイント・よくある誤り**

- 記録に「ファイル名・行番号・原因の説明」の 3 つがそろっているか。番号（C2143）があればなおよい。文面は他の人と同じでなくてよい（演習ページ）。
- 「6 行目が間違っていた」として `return 0;` の行をいじっている（例: `;return 0;` と書く）→ ビルドは通るが，直す場所の理解としては不十分。直すべきは 5 行目の末尾であることを説明できているか。
- 修正した箇所として「`;` を付けた」だけでなく，**どの行のどこに**付けたかを書いているか。
- `#include <stdio.h>` や `int main(void)` の行，`{` の行にまで `;` を付けてしまう過剰修正（講義「すべての行末に `;` を付けるわけではない」）。`int main(void);` とすると関数定義にならずエラーになる。
- 修正後のビルドが成功したことを確認せずに実行していないか（手順 4）。

---

## 課題4　ソースファイルと実行ファイル（`Version` / `version.c`）

**要点**: 保存はソースファイルを書き換える操作，ビルドはソースから実行ファイルを作り直す操作であり，保存しただけでは `Version.exe` は変わらないことを確かめる。

**解答**: フォルダのソースは手順 3 で書き換えた最終版（[Version/version.c](Version/version.c)，`Version B` を表示）。手順 1 の最初の版は次のとおり（テスト `Version/variant_version_a` で `Version A` と表示されることを確認）。

```c
#include <stdio.h>

int main(void)
{
    printf("Version A\n");
    return 0;
}
```

手順 3 で変更するのは `printf` の文字列だけ。

```c
    printf("Version B\n");
```

**実行結果**: 手順を Linux（GCC 13.3）で再現した実際の記録（打ったコマンドをそのまま載せている。最初の `version.c` は上の `Version A` の版）。
`sed` によるソースの書き換えが「Visual Studio で編集して保存」に相当する。`sha256sum` は実行ファイルの内容が変わったかを見るためのハッシュ値。

```text
$ gcc -std=c17 -Wall -Wextra -Wpedantic -o Version version.c && ./Version
Version A
$ sha256sum Version
e400107a68495bc16ef5b13d1740473205af3407cc244fb7c813250f95fdf4a8  Version
$ sed -i "s/Version A/Version B/" version.c   # 保存に相当
$ stat -c '%y %n' Version version.c
2026-10-08 07:02:57.505615291 +0000 Version
2026-10-08 07:02:57.520196956 +0000 version.c
$ ./Version
Version A
$ sha256sum Version
e400107a68495bc16ef5b13d1740473205af3407cc244fb7c813250f95fdf4a8  Version
$ gcc -std=c17 -Wall -Wextra -Wpedantic -o Version version.c && ./Version
Version B
$ sha256sum Version
eadd5aea45dd00af3b40772bee154bb2d55a8f621582cec57efc817e4981dd23  Version
```

- ソースを `Version B` に変えて保存した後も，実行ファイルの更新時刻（07:02:57.505，ソースの 07:02:57.520 より古い）とハッシュ値は最初のビルドのときのまま。ビルドせずに古い実行ファイルを直接起動すると `Version A` と表示された（手順 4 の予測の裏付け。授業の手順 4 では実行しない）。
- ビルドし直すと実行ファイルが作り直され（ハッシュ値が変わった），`Version B` と表示された。

| 時点 | ソース `version.c` の内容 | `Version.exe` の内容 | 表示 |
| --- | --- | --- | --- |
| 手順 2（最初のビルド・実行） | `Version A` | `Version A` を表示する版 | `Version A` |
| 手順 3〜4（保存しただけ） | `Version B` | **変わらない**（`Version A` を表示する版のまま） | （実行しない） |
| 手順 5（再ビルド・実行） | `Version B` | `Version B` を表示する版に作り直された | `Version B` |

**手順 4 の予測と理由**: `Version.exe` の内容は**変わっていない**。
`Version.exe` は手順 2 のビルドのときに，その時点のソース（`Version A`）を翻訳して作ったファイルであり，ソースファイルとは別のファイルである。
保存はエディタの内容を `version.c` に書き込むだけで，`Version.exe` には何もしない。
エクスプローラーで `Version.exe` の更新日時を見ると，保存の前後で変わっていないことでも確かめられる。

**保存とビルドの役割の違い**

- **保存**: エディタで編集した内容をソースファイル（`version.c`）に書き込む。実行ファイルは変わらない。
- **ビルド**: ディスク上のソースファイルをコンパイル・リンクして，実行ファイル（`Version.exe`）を新しく作り直す（Visual Studio は既定で，その前に未保存のファイルを自動保存する）。
- **実行**: その時点の実行ファイルを動かす。表示されるのは，最後にビルドしたときのソースの内容。

**Visual Studio での注意**: Ctrl+F5 は，プロジェクトが古くなっている（ソースが `exe` より新しい）と，実行の前に自動でビルドする（またはビルドするかを確認するダイアログを出す）ことがある（演習ページの注意）。
そのため手順 4 では実行操作をしない。
また，ビルドが読むのはディスク上のソースファイルだが，Visual Studio は既定でビルドの前に未保存のファイルを自動保存する（ビルド操作の中で保存も行われる）。
保存だけでは実行ファイルは変わらない。これらの自動処理のせいで「保存しただけで `exe` が変わった」と誤解しやすいので，「Ctrl+F5 の中でビルド（と保存）が行われた」ことを区別させる。

**採点のポイント・よくある誤り**

- 手順 4 で「変わる（保存したから）」と予測していたら，その理由づけが誤り。予測が外れたこと自体は減点ではなく，手順 5 の結果と比べて考察できているかを見る。
- 最初の表示 `Version A` と再ビルド後の表示 `Version B` の**両方**を記録しているか。
- 保存とビルドの違いを「ソースファイルへの書き込み」と「実行ファイルの作成」という**対象のファイルの違い**で説明しているか。「保存は保存，ビルドはビルド」のような同語反復は不可。
- 手順 4 で Ctrl+F5 を押してしまい，自動ビルドで `Version B` が表示された → 「保存しただけで変わった」と結論していないか。
- 提出された `version.c` が最終版（`Version B`）になっているか。

---

## 課題5　発展：文字で図を描く（`House` / `house.c`）

**要点**: 表示する `\` 1 文字はソースで `\\` と書く。行頭の空白も文字列の一部として書く。変数・繰り返しは不要。

**解答**: [House/house.c](House/house.c)

```c
    printf("  /\\\n");
    printf(" /  \\\n");
    printf("/____\\\n");
    printf("| [] |\n");
    printf("|____|\n");
```

行末の `\\\n` は `\\`（`\` 1 文字）と `\n`（改行）が続いたもの。

**実行結果**

```text
  /\
 /  \
/____\
| [] |
|____|
```

各行の文字数は 4・5・6・6・6 文字（1 行目は空白 2 つ，2 行目は空白 1 つで始まる。行末に空白はない）。

**採点のポイント・よくある誤り**

- 行頭の空白の数（1 行目 2 つ，2 行目 1 つ，3〜5 行目 0）と，屋根の内側の空白（2 行目は 2 つ）。
- `\` を 1 つしか書かない誤りは，後ろの文字によって症状が変わる。
  - `/\` と改行のつもりで `printf("  /\\n");` と書く → `\\` + `n` になり，改行されず `  /\n /  \` のように 1 行目と 2 行目がつながる（警告なし）。
  - `printf("/____\n");` → `\` が消えて `/____` と表示される（警告なし。ビルドは成功する）。
  - `printf(" /  \ \n");` のように `\` の後に空白 → 未定義のエスケープシーケンス。MSVC の例: C4129（`' ': unrecognized character escape sequence`，`\` を無視して空白を表示），GCC は `warning: unknown escape sequence: '\040'`，Clang は `warning: unknown escape sequence '\ '`。
  - `printf("/____\");` → `\"` で文字列が閉じず，コンパイルエラー（MSVC の例: C2001，GCC: `missing terminating " character`）。
- `/` はエスケープ不要。`\/` と書くと MSVC は C4129 の警告を出す（Microsoft のドキュメントの C4129 の例による）。
- 実際に間違えた版を実行すると次のようになる（テスト `House/variant_single_backslash` の実際の出力。1 行目を `"  /\\n"`，3 行目を `"/____\n"` とした場合）。ビルドが成功しても表示が正しいとは限らない例（確認問題 6）。

  ```text
    /\n /  \
  /____
  | [] |
  |____|
  ```

---

## 確認問題

**1. Visual Studio の C++ プロジェクトで C 言語を使うには，ファイル名や設定のどこに注意するか。**

結論: ソースファイルの**拡張子を `.c`** にし，プロジェクトのプロパティで**コンパイル言語を「C コードとしてコンパイル（`/TC`）」**，**C 言語標準を「ISO C17（`/std:c17`）」**にする（警告レベルは 4 `/W4`）。
理由・注意点:
- 「新しい項目」で C++ ファイル（`.cpp`）を選んだまま追加すると，C++ としてコンパイルされる。名前を `hello.c` に変える。`hello.c.txt` や `hello.cpp` になっていないか，ソリューション エクスプローラーで確認する。
- `/TC` はプロジェクト全体を C としてコンパイルする設定で，拡張子の付け間違いがあっても C として扱われる。
- プロパティは**プロジェクト**を右クリックして開き，「構成: すべての構成」「プラットフォーム: すべてのプラットフォーム」で設定する（ソリューションのプロパティではない）。新しいプロジェクトごとに設定し直す。
- テンプレートは「空のプロジェクト」を選ぶ（他のテンプレートだと `pch.h` などが必要になる）。1 プロジェクトに `main` を持つファイルは 1 つだけ。

**2. ソースファイルを保存する操作と，プロジェクトをビルドする操作は，何が違うか。**

結論: 保存は**ソースファイル（`.c`）**にエディタの内容を書き込む操作，ビルドはソースファイルを翻訳（コンパイル・リンク）して**実行ファイル（`.exe`）**を作る操作で，対象のファイルが違う。
理由: 課題4で，`Version B` に変えて保存しても `Version.exe` は変わらず，ビルドし直して初めて `Version B` と表示された。保存だけでは実行ファイルは変わらない。ビルドが読むのはディスク上のソースファイルで，Visual Studio は既定でビルド前に未保存のファイルを自動保存するため，ビルド操作の中で保存も行われる（保存の後にビルドが続く）。

**3. `printf` の文末の `;` と，文字列中の `\n` は何が違うか。**

結論: `;` は**ソースコードの文法上の記号**で，式の後に付けて 1 つの文にする（文の終わりを示す）。`\n` は**文字列リテラルの中のエスケープシーケンス**で，表示するデータとしての改行文字 1 文字を表す。
理由: `;` はコンパイラが文の区切りを知るためのもので画面には何も出ず，忘れるとビルドエラー（課題3の C2143）。`\n` は実行時に出力される文字で，忘れてもビルドは成功し，表示が 1 行につながるだけ（課題1）。ソースの行末で改行しても `\n` の代わりにはならない。

**4. `return 0;` は，画面に `0` を表示する文か。**

結論: **表示しない。**
理由: `return` は関数の処理を終えて値を返す文で，`main` から `0` を返すと「正常に終了した」ことを実行環境（OS や Visual Studio）へ伝える（終了コード）。課題1〜5の実行結果にも `0` は表示されていない。
Ctrl+F5 で実行すると，コンソールの最後に例えば次のように表示されるが，これは Visual Studio が終了コードを知らせる案内で，プログラムの `printf` の出力ではない（パスとプロセス番号は環境で異なる）。

```text
C:\Users\<ユーザ名>\Documents\PL1\week01\Welcome\x64\Debug\Welcome.exe (プロセス 12345) は、コード 0 で終了しました。
```

Visual Studio のバージョンによっては `コード 0 (0x0) で終了しました。` のように 16 進数も付く。

**5. 編集・保存した後にビルドが失敗した。以前からある `exe` が動けば，修正したプログラムが正しいといえるか。**

結論: **いえない。**
理由: 以前からある `exe` は，最後に**成功したビルド**のときのソースから作られたもので，ビルドに失敗した今のソースは反映されていない（課題4で，ソースを変えても再ビルドするまで `Version A` のままだったことと同じ）。
Visual Studio が「最後に成功したビルドを実行しますか?」と聞いてきても実行せず，エラーを直してビルドを成功させてから確かめる。

**6. ビルドが成功すれば，必ず課題で指定された表示になるか。**

結論: **ならない。**
理由: ビルドの成功は，コードが C の文法などの規則に合っていて実行ファイルを作れたことを示すだけで，表示する内容が正しいかは調べない。
例えば `\n` の書き忘れ（課題1で 2 行が 1 行につながる。テスト `Welcome/variant_missing_newline`），`\\` を `\` と書いた（課題5で `/____` になる。テスト `House/variant_single_backslash`），綴りの誤り，空白の数の誤りは，どれも警告すら出ずにビルドが成功する。`100%\n` は警告は出るがビルドは成功する。実行して，期待する表示と 1 文字ずつ比べる必要がある。

---

## チェックリスト

| 項目 | どこで確認できるか |
| --- | --- |
| Visual Studio でプロジェクトを作成し，C のソースファイルを追加できる | 課題1〜5 の各プロジェクト（空のプロジェクト，拡張子 `.c`，`/TC`・C17・`/W4`）。確認問題1 |
| 課題ごとのプロジェクトと，`welcome.c`，`message.c`，修正済みの `broken.c`，`version.c` を保存した | プロジェクト一覧の表（`Welcome`・`Message`・`Broken`・`Version`。`House` は発展）。`broken.c` は修正後（5 行目に `;`），`version.c` は `Version B` の最終版 |
| 警告やエラーを確認したうえで，それぞれのプログラムをビルド・実行できる | 全プログラムが GCC/Clang（`-Wall -Wextra -Wpedantic -Werror`）で警告 0 でビルドでき，テスト 11 件が成功。MSVC `/W4 /WX`（Debug・Release・sln）・MinGW・macOS の CI（GitHub Actions）でも全プロジェクトのビルドとテストが成功している（コミット a76876f の時点）。課題3でエラーを確認 |
| 課題2 の空行・引用符・バックスラッシュ・パーセントを正しく表示できる | 課題2 の実行結果と `od -An -c` の出力（`\n\n`，`\"`，`\\`，`%%`），テスト `Message/basic` |
| 課題3 の診断と修正箇所，課題4 の結果の違いを説明できる | 課題3「記録すること」の表（MSVC の例では C2143・6 行目，修正は 5 行目末尾に `;`），課題4 の表（保存だけでは `Version A` のまま，再ビルドで `Version B`） |

---

## ビルドとテスト（このリポジトリ）

```sh
B=/tmp/build-week01
cmake -S . -B $B -G Ninja -DSOFTPRAC_WEEKS=week01 -DSOFTPRAC_WERROR=ON -DSOFTPRAC_SANITIZE=ON
cmake --build $B
ctest --test-dir $B --output-on-failure    # 11 件すべて成功
```
