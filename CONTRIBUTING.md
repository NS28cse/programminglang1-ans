# このリポジトリへの追加・修正のガイド

解答（`weekNN/`）・実務の手引き（`ta-guide/`）・デバッグの題材（`debugging/`）を追加・修正するときの規約。人が書くときも，Claude のサブエージェントが書くときも，これに従う。
リポジトリの入口と使い方はルートの [README.md](README.md) にある。

- 評価: 解答（`weekNN/`）は [softprac-grader](.claude/agents/softprac-grader.md) が回ごとに採点する。
  実務の手引き（`ta-guide/`）とデバッグの題材（`debugging/`）は [ta-material-reviewer](.claude/agents/ta-material-reviewer.md) が評価する（題材に固有の確認はその手順 5）。
- 授業サイト: <https://t-yokoga.github.io/softprac1/>
- 授業資料のリポジトリ: <https://github.com/t-yokoga/softprac1>（`docs/exNN.md` が演習，`docs/lecNN.md` が講義，`docs/sample/` が例題）

## フォルダ構成

```
weekNN/
├── README.md            ← その回の解答・解説（TA 用）
├── <プロジェクト名>/     ← Visual Studio の 1 プロジェクト = 1 実行ファイル
│   ├── <ソース名>.c      ← 演習ページの表のファイル名どおり
│   ├── *.h              ← 分割コンパイルの回など
│   ├── input.txt など   ← 実行に使うデータファイル（作業ディレクトリに置くもの）
│   ├── run.args         ← （任意）IDE から実行するときの既定のコマンドライン引数（1 行 1 引数）
│   ├── CMakeLists.txt   ← （任意）ライブラリや書き換えた版（softprac_add_variant）を使うときだけ
│   ├── tests/           ← 自動テスト（後述）
│   ├── variants/tests/  ← （任意）書き換えた版の期待値
│   └── versions/        ← （任意）README に載せた確認用・比較用のプログラム
└── _<名前>/             ← ビルドしないフォルダ（意図的にエラーを含むコードなど）
```

- プロジェクト名（フォルダ名）とソースファイル名は，演習ページの表・本文の指定に**完全に**合わせる（大文字小文字も含む）。
  プロジェクト名は全回で重複できない（実行ファイル名になるため）。重複したら CMake が止まるので，`Hello2` のように名前を変えて README に理由を書く。
- フォルダ直下の `*.c` はすべて 1 つの実行ファイルにリンクされる（`versions/` などのサブフォルダは含まない）。`main` を持つ `.c` は 1 フォルダに 1 つだけにする。
- フォルダのソース（本体）は，**演習ページの「期待する表示」を出す版**にする。
  - 期待する表示がすべての指示を反映した後の形なら（「関数を追加して表示する」など），その形を本体にする。
  - 期待する表示が配布コード・最初の版のもので，その後の変更が「値を変えて確かめる」「〜に変えて比べる」実験なら，本体は配布コード・最初の版のままにし，変更した版は `softprac_add_variant` でテストする。
  - 迷ったら「TA が IDE で本体を実行すると，演習ページの期待する表示がそのまま出る」ことを優先する。途中版のコードは README にも載せる。
  - 演習ページがプロジェクト名を付けている派生版は，別フォルダにする。
- ライブラリを作る回（第12回の `CalcLib`/`CalcApp` など）は，フォルダに `CMakeLists.txt` を置き，`softprac_add_program(<名前> <ソース>...)` と `add_library` を使う。
- フォルダや `.c` を足すと，次のビルドのときに CMake が自動で再構成する（`CONFIGURE_DEPENDS`）。
- `debugging/` と `ta-guide/` の規則は，後の「[デバッグの題材](#デバッグの題材debugging)」「[実務の手引き](#実務の手引きta-guide)」にある。

## ソースコードの規約

- C17 の標準 C だけを使う（`scanf_s` などの MSVC 専用関数，POSIX 専用関数は使わない）。
- **その回までに講義で扱った文法・関数だけを使う**（例: 第2回は `if`・繰り返し・`scanf` を使わない）。演習ページの「使わない」指定は必ず守る。
- **本体は演習ページ（配布コード）どおりに保つ**: 本体の出力は「期待する表示」だけにし，検証表の値・境界・途中版・誤りの例は本体に足さず
  `softprac_add_variant` でテストする（本体と variant で同じ確認を重複させない）。演習ページが「`main` の値を書き換えて試す」課題に，
  テストのためだけにコマンドライン引数を追加しない（演習ページ自体が引数を使う課題は除く）。
- 表示は演習ページの「期待する表示」と**1 文字も違わない**ようにする（空白・改行・小数の桁・末尾の改行を含む）。
- 表示する文字列は原則 ASCII にする（Windows のコンソールで文字化けしないように）。演習ページが日本語の表示を指定した場合だけ日本語にする。
- 書き方は授業の例題（`docs/sample/`）に合わせる: インデント 4 空白，関数の `{` は次の行，`if`/`for` などの `{` は同じ行，`int main(void)`。
- `fopen`・`strcpy`・`scanf` など MSVC が C4996 を出す関数を使うファイルは，講義と同様に**先頭（`#include` より前）**に `#define _CRT_SECURE_NO_WARNINGS` を書く。
- MSVC `/W4` と GCC/Clang `-Wall -Wextra -Wpedantic` で**警告 0**。AddressSanitizer/UBSan でエラーが出ないこと（未定義動作をしない）。
- 入力・引数・`fopen`・`malloc` の戻り値は検査し，失敗時は `stderr` へメッセージを出して `EXIT_FAILURE`（または 1）で終わる。確保したメモリと開いたファイルは必ず解放・クローズする。
- ファイル先頭に，何回のどの課題かを示すコメントを書く。コメントは日本語で，処理の意図や注意点（境界・終端・所有者など）を簡潔に書く。書きすぎない。
- 文字コードは BOM 付き UTF-8・LF。「[仕上げ](#仕上げ)」の `python3 tools/update_generated.py` でそろう。

## 自動テスト（`tests/`）

結果が決まるプログラムには必ずテストを付ける。演習ページの検証表・境界の値はすべてテストケースにする。

| ファイル | 内容 |
| --- | --- |
| `tests/<ケース>.out` | 期待する標準出力（**必須**。このファイルがあるとテストとして登録される） |
| `tests/<ケース>.args` | コマンドライン引数（1 行 1 引数。空行は空文字列の引数） |
| `tests/<ケース>.in` | 標準入力 |
| `tests/<ケース>.err` | 期待する標準エラー出力（任意。メッセージまで固定したいときだけ） |
| `tests/<ケース>.code` | 期待する終了コード（省略時 0） |
| `tests/<ケース>.setup/` | 実行前に作業フォルダへコピーするファイル（ケース専用の入力ファイル） |
| `tests/<ケース>.files/` | 実行後に作業フォルダにあるべきファイル（`.bin` はバイト単位，他は改行コードを無視して比較） |

- 「値を変えて確かめる」「一時的に書き換える」小問は，フォルダに `CMakeLists.txt` を置き，`softprac_add_program(<名前> <ソース>)` に続けて
  `softprac_add_variant(<名前> <ソース> <ケース名> "<置換前>" "<置換後>")` を書くと，ソースの一部を置き換えた版をビルドしてテストできる
  （期待値は `variants/tests/<ケース名>.out`，同じ版を別の入力で試すときは `<ケース名>--<名前>.out`。置換文字列には `;` も書ける。
  同じフォルダの main を持たない `.c` も自動でリンクされる。詳しくは `cmake/SoftpracVariant.cmake`，例は `week02/Rectangle/`）。
- `softprac_add_variant` で生成されるソースのコメントも実態に合わせる。コメント行も置換の組に含め，「〜に書き換えた版」「誤りの例」など，その版の説明に置き換える（生成ソースは `<ビルド先>/projects/weekNN/<プロジェクト>/variants/<ケース>/` で確認できる）。
- README に載せた確認用・比較用のプログラムで結果が決まるものは，`<プロジェクト>/versions/*.c` に置き，置換なしの `softprac_add_variant` でテストする（README だけに結果を書かない）。
- テストはプロジェクトフォルダのデータファイル（ソース以外）をコピーした一時フォルダで実行される。
- アドレスの表示など，実行ごとに変わる出力はテストにしない（README に実行例を載せる）。
- ケース名は内容が分かるようにする（`basic`，`zero`，`boundary_100`，`too_many_args` など）。

```sh
# 1 つの回だけビルド・テストする（他の作業と衝突しないよう，ビルド先は自分専用にする）
cmake -S . -B /tmp/build-week05 -G Ninja -DSOFTPRAC_WEEKS=week05 -DSOFTPRAC_WERROR=ON -DSOFTPRAC_SANITIZE=ON
cmake --build /tmp/build-week05
ctest --test-dir /tmp/build-week05 --output-on-failure
```

## 各回の README.md（解答・解説）

TA が授業で解説・採点に使う資料。演習ページの**すべての問い**に答える。冒頭は次のひな形どおりに書く（`N` は回の番号，`NN` は 2 桁）。

```markdown
# 第N回 演習 解答・解説（テーマ）

- 演習ページ: [exNN](https://t-yokoga.github.io/softprac1/exNN.html)（原稿: [docs/exNN.md](https://github.com/t-yokoga/softprac1/blob/main/docs/exNN.md)）・講義: [lecNN](https://t-yokoga.github.io/softprac1/lecNN.html)（例題: [docs/sample/NN/](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/NN/)）
- TA 用の資料: [実務の手引き 第N回](../ta-guide/README.md#<その回の節の見出しのアンカー>)・デバッグの題材 [Bug<名前>](../debugging/Bug<名前>/README.md)，[Bug<名前>](../debugging/Bug<名前>/README.md)
- 今回の範囲: その回までに講義で扱った文法・関数と，使わないもの（任意）
```

- 1 行目の（）の中のテーマは，ルートの README の「各回の解答と題材の表」にそのまま使われる（`tools/gen_readme_index.py`）。
- 「今回の範囲」の行は任意。箇条書きの後の文章で書いてもよい。
- 例題は，講義の例題のフォルダ `docs/sample/NN/` への 1 本のリンクにする（ファイルごとに並べない）。
- 「TA 用の資料」の行は，実務の手引きのその回の節と，その回のデバッグの題材（`debugging/README.md` の一覧の「回」の列）へリンクする。題材がない回は手引きだけを書く。
  手引きの節へのアンカーは見出しから作られるので，手引きの見出しを変えたら各回のリンクも直す（`python3 tools/check_docs.py` で見つかる）。

続く構成:

1. プロジェクト一覧の表（課題・プロジェクト・ソースへのリンク・テスト数）。
2. 課題ごとの節。見出しは ``## 課題N　題名（`Project` / `file.c`）`` の形にする（「課題N」と題名の間は全角の空白。発展は ``## 発展N　題名（`Project` / `file.c`）``）。見出しはほかの文書からアンカーで参照されるので，変えたら `python3 tools/check_docs.py` で参照元を見つけて直す。節の中は:
   - 要点（何を学ぶ課題か，1〜3 行）
   - 解答コードへのリンク（必要なら重要部分の抜粋）
   - 実行結果（実際に実行した出力をそのまま貼る）
   - 演習ページの「説明すること」「記録すること」「考察」「確認すること」への回答
   - 演習ページの表（「記入してください」の欄）はすべて埋めた表として載せる
   - 「値を変えて確かめる」「書き換える」などの小問の結果と，途中版のコード
   - **採点のポイント・よくある誤り**（TA が学生の提出物を見るときの観点）
3. 発展課題も同じ形式で。
4. 確認問題: 番号ごとに，結論を先に書き，理由を添える。
5. チェックリストの各項目について，どの課題の何で確認できるかを書く。

- 実行結果は推測で書かず，実際にビルドして実行した出力を貼る。環境で変わる値（アドレス，`sizeof long` など）は「Windows x64 (MSVC) では…，Linux x64 では…」のように違いを明記する。
- 意図的なエラー（第1回の `broken.c`，第12回のリンクエラーなど）は，エラーになる版を README にコードブロックで示し，MSVC での診断（エラー番号 `C2143`，`LNK2019` など）と GCC での診断の例を書く。
- 用語は講義ページに合わせる。

## 読者に向けた書き方

README・手引き・題材の README とソースのコメントは，TA と学生が読む完成した資料として書く。

- 書くのは「何をするか」「なぜそうなるか」「どこを見るか」。作業の経緯（「〜を直した」「〜に変更した」「採点の指摘」「最終版」など）やコミット・CI の実行番号は書かない。
- テストのしくみ・実行環境・MSVC の診断番号の扱いはルートの README.md にまとめてあるので，各回の README で繰り返さない。書き換えた版を示すときは，テスト名（`variant_<名前>`）を添えるだけでよい。
- MSVC の番号は「MSVC では C4244（`int` から `char` への変換）」のように番号と意味を書く。文面を「」で引用しない。
- 学生が読むソース（`weekNN/<プロジェクト>/*.c`・`*.h`・`versions/*.c`）のコメントには，テストやビルドのしくみ（variant・CMakeLists.txt など）を書かない。
- Visual Studio の画面の表記（メニュー・ウィンドウ名・プロパティ名と値・ダイアログや出力の文面）は **Visual Studio 2026（英語版）** に合わせ，**太字**で書く。メニューの階層は ` > ` でつなぐ（例: **Configuration Properties > Debugging > Command Arguments**，フォルダを開くのは **File > Open > Folder**）。本文と，概念としての「プロジェクト」「ブレークポイント」などは日本語のままでよい。
- VS Code の画面の表記も英語版に合わせて**太字**で書く（例: **File > Open Folder**，**Run and Debug** ビュー，**Source Control** ビュー，**Command Palette**）。`.vscode/launch.json` の構成名（「開いている課題を実行」など）はそのまま「」で書く。
- 用語: `debugging/` は「デバッグの題材」，`ta-guide/` は「実務の手引き」と呼ぶ。「指導資料」は両方をまとめて指すときだけ使う。
- 文体は 1 ファイルの中でそろえる（ルートの README.md はです・ます，ほかは本文の多数派に合わせる）。`.md` に BOM を付けない。

## デバッグの題材（`debugging/`）

学生にデバッガで原因を探させるための，誤りを 1 つ入れたプログラムの置き場所（TA 用）。評価は [ta-material-reviewer](.claude/agents/ta-material-reviewer.md) の手順 5 で行う。

```
debugging/
├── README.md            ← 使い方・デバッグの進め方の型・題材の一覧
└── Bug<名前>/           ← 1 題材 = 1 実行ファイル（weekNN/ のプロジェクトと同じ規則で自動登録。実行ファイルは bin/debugging/）
    ├── <ソース名>.c      ← バグ入りの版
    ├── input.txt・run.args など（必要なら）
    ├── CMakeLists.txt   ← softprac_add_program と，直した版の softprac_add_variant(<名前> <ソース> fixed ...)
    ├── tests/           ← バグ入りの版の症状（間違った出力）
    ├── variants/tests/  ← 直した版の正しい出力（fixed.out，fixed--<名前>.out）
    └── README.md        ← TA 用の解説
```

- 題材名は `Bug` で始める（全回のプロジェクト名と重複させないため）。`_` で始まるフォルダはビルドしない，`CMakeLists.txt` があればそれを使う，など weekNN/ と同じ規則で登録される。
  `SOFTPRAC_WEEKS` で回を絞ったときは，`debugging` を含めたときだけビルドする（空ならすべて）。題材だけをビルド・テストするときは `-DSOFTPRAC_WEEKS=debugging` を付けて構成する。
- その回までに講義で扱った文法・関数だけを使う。誤りは学生が実際にしそうなもので，**コンパイラの警告では見つからない**ものにする（MSVC `/W4`，GCC/Clang `-Wall -Wextra -Wpedantic` で警告 0。CI は `-Werror`・`/WX` でビルドする）。種類（境界・条件・初期化の位置・入力の読み方・範囲外・ポインタ・メモリ・再帰など）を偏らせない。
- ソースの先頭コメントは「デバッグ題材: ○○（第N回）」と，プログラムが**するはずのこと**だけを書く。バグの場所やヒントになるコメントは書かない。
- 決まった結果になる題材は，`tests/` でバグ入りの版の症状を固定し，直した版を `softprac_add_variant` で作って `variants/tests/` で正しい出力をテストする（置き換えは README の「直し方」の差分と同じにし，先頭コメントも「〜を直した版」に置き換える）。
- 未定義動作（範囲外アクセス・解放後の使用など）の題材は全体で 3〜4 個までにする。バグ入りの版はテストで実行せず（CI は AddressSanitizer 付きでテストする），直した版だけをテストする。異常終了・無限ループになる題材も同じ。README では「症状は環境で変わる」と断り，Debug 構成の MSVC と Linux での症状を分けて書く。
- `tools/check_launch.py` は，バグ入りの題材が異常終了や MSVC の実行時チェックのダイアログで止まり得るので，`debugging/` の起動構成を起動せず，実行ファイルの存在だけを確かめる。
- 題材の README.md の構成: 対象の回と前提 / プログラムがするはずのこと / 症状（再現の手順と，実際にビルド・実行した出力）/ 学生への渡し方（最初に言うこと。答えは言わない）/ 探し方（症状 → 範囲を絞る → 仮説 → 確かめる。その回の学生が使える Visual Studio の操作を中心に，未習の操作は「授業では未習」と書く）/ ヒントの段階（3 段階）/ 原因 / 直し方（差分）/ 学生への問い / 関連。
  「関連」の先頭は `[題材の一覧と渡し方の共通ルール](../README.md)` にし，続けてその回の解答 README の節と実務の手引きの節を挙げる。
- 題材を足したら，`debugging/README.md` の一覧の表と，その回の `weekNN/README.md` の「TA 用の資料」の行と，実務の手引きのその回の節の「関連」にも加える。一覧の表と題材のフォルダが一致することは `python3 tools/check_docs.py` が確かめる。

## 実務の手引き（`ta-guide/`）

各回の演習に「実際のソフトウェア開発で必要になること」（テスト・エラーの読み方・デバッグ・バージョン管理など）を添えて教えるための手引き（[ta-guide/README.md](ta-guide/README.md)）。ビルドの対象ではない。評価は [ta-material-reviewer](.claude/agents/ta-material-reviewer.md) で行う。

- 内容は各回の演習と解答に合わせ，回や課題名を変えたら合わせて直す。その回までに講義で扱った文法・関数・操作だけを前提にし，授業で扱わない操作は「授業では未習」と書く。
- 各回の節の見出しは `## 第N回　実務のテーマ（授業のテーマ）` の形にする。各回の `weekNN/README.md` の「TA 用の資料」が見出しのアンカーでリンクしているので，見出しを変えたら各回のリンクも直す。
- 各回の節は「テーマと理由 → 声かけ → 見せ方 → 確かめる問い → よくある反応 → 副テーマ → デバッグの補足 → 関連」の順にする。「関連」には，その回の解答 README の節と，その回のデバッグの題材を挙げる。
- 冒頭の「使い方」の表記の対応表（英語版の表記・授業資料の表記・日本語版の画面の表記）は，手引きと題材の README で使う Visual Studio の操作の用語集を兼ねる。新しい操作を使ったら表に足す。

## 仕上げ

commit の前に，次の 2 つを実行する。

```sh
python3 tools/update_generated.py   # ソースの BOM・改行をそろえ，生成物を作り直す（--check を付けると確認だけ）
python3 tools/check_docs.py         # 文書のリンクとアンカー，デバッグの題材の一覧を確かめる
```

- 生成されたファイルも同じコミットに含める（テスト数が変わったのに作り直さないと，CI の repository-checks が失敗する）。
- push して CI の repository-checks が失敗したら，手元でこの 2 つを実行し，変わったファイルを commit する。Visual Studio の **Debug and Launch Settings** で `.vs/launch.vs.json` の引数を書き換えたまま commit したときも失敗する（既定の引数は `run.args` で変える）。
- push したら CI の全ジョブが成功したことを確かめる。

`tools/` のスクリプト:

| スクリプト | 内容 |
| --- | --- |
| `update_generated.py` | 次の 3 つを順に実行する。`--check` は書き換えずに確かめる（CI 用） |
| `normalize_sources.py` | `weekNN/`・`debugging/` の `.c`・`.h` を BOM 付き UTF-8・LF・末尾改行ありにそろえる。引数に回のフォルダ名（`week05`，`debugging`）を付けるとその回だけ |
| `gen_launch_vs.py` | Visual Studio の起動構成 `.vs/launch.vs.json` を作り直す（作業ディレクトリ = プロジェクトフォルダ，引数 = `run.args`） |
| `gen_readme_index.py` | ルートの README.md の「各回の解答と題材の表」（テスト数を含む）を作り直す |
| `check_docs.py` | すべての `.md` の相対リンクとアンカーがあること，`debugging/README.md` の一覧と `Bug*` フォルダが一致すること |
| `check_launch.py` | IDE の起動構成が実際に動くこと（`python3 tools/check_launch.py <ビルド先>`。CI 用。手元でも確かめられる） |
| `projects.py` | プロジェクトの列挙（ルートの `CMakeLists.txt` と同じ規則）を各スクリプトで共有するライブラリ |

## CI（GitHub Actions）

`.github/workflows/ci.yml` で次を確かめる。

| ジョブ | 内容 |
| --- | --- |
| `windows-msvc-preset` | MSVC `/W4 /WX`。CMakePresets の `msvc-debug`・`msvc-release`（Visual Studio の **File > Open > Folder** と同じ構成）。IDE の起動構成で全プロジェクトを起動する（`debugging/` は起動せず，実行ファイルの存在だけを確かめる） |
| `windows-msvc-sln` | Visual Studio ジェネレーター（.sln）での MSBuild |
| `windows-mingw` | MSYS2 UCRT64 の gcc（VS Code + MinGW）。Visual Studio の構成の一覧に MinGW が出ないよう，プリセットを使わず CMake のオプションで指定する |
| `linux` | GCC・Clang × Debug・Release。`-Werror`，AddressSanitizer/UBSan |
| `macos` | Apple Clang。プリセット `gcc-debug`。IDE の起動構成で全プロジェクトを起動する（`debugging/` は起動せず，実行ファイルの存在だけを確かめる） |
| `repository-checks` | Windows で使えないファイル名，生成物が最新か（`update_generated.py --check`），文書のリンクと題材の一覧（`check_docs.py`） |

- 全ジョブに時間制限があり，同じブランチに新しい push が来ると古い実行は取り消される。
- 非公開リポジトリでは Actions の実行時間が課金対象になる（Windows は 2 倍，macOS は 10 倍で数える）。そのため非公開のときの push・PR では，MSVC Debug・Linux Debug・repository-checks だけを動かす。すべてのジョブは Actions タブから手動で実行すると動く。
