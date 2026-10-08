# programminglang1-ans

「プログラミング言語I・ソフトウェア演習I」（C 言語）の **TA 用解答・解説** リポジトリです。

- 授業サイト: <https://t-yokoga.github.io/softprac1/>（資料: <https://github.com/t-yokoga/softprac1>）
- 全 14 回の演習について，課題・発展課題のソースコード，自動テスト，解答・解説（各回の `README.md`）をまとめています。
- 1 つのリポジトリで **Visual Studio**（Windows）と **VS Code**（Windows / macOS / Linux）のどちらからでもビルド・実行できるように，CMake で管理しています。

> [!WARNING]
> 解答を含みます。学生に公開する範囲とタイミングは担当教員の指示に従ってください。

## 目次

<!-- WEEK-TABLE:BEGIN -->
| 回 | テーマ | プロジェクト | テスト数 | 演習ページ |
| --- | --- | --- | ---: | --- |
| [第1回](week01/README.md) | プログラミングの基礎 | Broken，House，Message，Version，Welcome | 11 | [ex01](https://t-yokoga.github.io/softprac1/ex01.html) |
| [第2回](week02/README.md) | 変数 | Exchange，Observe，Profile，Rectangle，Temperature | 21 | [ex02](https://t-yokoga.github.io/softprac1/ex02.html) |
| [第3回](week03/README.md) | 演算子 | Conditions，Flags，Leap，TimeParts，Update | 40 | [ex03](https://t-yokoga.github.io/softprac1/ex03.html) |
| [第4回](week04/README.md) | 制御構造 | EvenSum，Fee，Powers，Table，YearGroup | 127 | [ex04](https://t-yokoga.github.io/softprac1/ex04.html) |
| [第5回](week05/README.md) | 配列と関数 | Array3D，ColumnSum，Functions，Maximum，SumMean，ValueCopy，Warmup05 | 36 | [ex05](https://t-yokoga.github.io/softprac1/ex05.html) |
| [第6回](week06/README.md) | 文字列 | AsciiTable，Average，CharCode，CompareJoin，CopyCapacity，Length，Lower | 39 | [ex06](https://t-yokoga.github.io/softprac1/ex06.html) |
| [第7回](week07/README.md) | 入出力 | ByteCount，Echo，Formats，LetterCount，LineInput，LowerInput，Typing | 92 | [ex07](https://t-yokoga.github.io/softprac1/ex07.html) |
| [第8回](week08/README.md) | ポインタ1 | CopyText，Decompose，MinMax，PointerWalk，Swap | 43 | [ex08](https://t-yokoga.github.io/softprac1/ex08.html) |
| [第9回](week09/README.md) | ポインタ2 | ArrayTypes，FindMax，MatrixMean，Names，RaggedRows，ReturnMaximum，SwapRows | 42 | [ex09](https://t-yokoga.github.io/softprac1/ex09.html) |
| [第10回](week10/README.md) | ファイル | Arguments，Binary，ByteOrder，CheckValue，LineLengths，NumberFormats，ParseNumber，ReadText，WriteSquares，WriteText | 132 | [ex10](https://t-yokoga.github.io/softprac1/ex10.html) |
| [第11回](week11/README.md) | 構造体 | CopyMembers，PointInit，PointMove，Rect，RectContains，StructLayout，Students | 49 | [ex11](https://t-yokoga.github.io/softprac1/ex11.html) |
| [第12回](week12/README.md) | コンパイル：分割コンパイルとライブラリ | CalcApp，CalcLib，LibraryCheck，SortModule，SplitCalc，VectorCalc | 34 | [ex12](https://t-yokoga.github.io/softprac1/ex12.html) |
| [第13回](week13/README.md) | メモリ管理 | Dynamic，DynamicCopy，DynamicVector，DynamicVectorFail，GrowArray，GrowArrayFail，NewPoint，NewPointFail，SharedCount，StorageCount | 66 | [ex13](https://t-yokoga.github.io/softprac1/ex13.html) |
| [第14回](week14/README.md) | 再帰 | CheckedFactorial，Factorial，Fibonacci，GcdLoop，Trace，TreeTraversal | 63 | [ex14](https://t-yokoga.github.io/softprac1/ex14.html) |
| | | **合計** | **795** | |
<!-- WEEK-TABLE:END -->

## しくみ

授業では「1 課題 = 1 つの空のプロジェクト = 1 つの `main`」で作業します。このリポジトリでは同じ単位を **1 フォルダ** で表します。

```
programminglang1-ans/
├── CMakeLists.txt        ← weekNN/<プロジェクト>/ を自動で見つけて実行ファイルにする
├── CMakePresets.json     ← Visual Studio / VS Code が読むビルド設定（MSVC・GCC/Clang）
├── week01/
│   ├── README.md         ← 第1回の解答・解説
│   ├── Welcome/
│   │   ├── welcome.c     ← ビルドすると Welcome.exe になる
│   │   └── tests/        ← 期待する出力（自動テスト）
│   └── Message/ ...
├── week02/ ...
├── .vs/launch.vs.json    ← Visual Studio 用の起動設定（作業ディレクトリ・コマンド引数）
└── .vscode/              ← VS Code 用の設定
```

- `weekNN/<プロジェクト名>/` の `*.c` はまとめて `<プロジェクト名>.exe` になります（分割コンパイルの回も同じ）。
- 授業と同じく **C17・警告レベル4（`/W4`）** でコンパイルします。GCC/Clang では `-Wall -Wextra -Wpedantic` です。
- プログラムの**作業ディレクトリはプロジェクトフォルダ**です（授業の `$(ProjectDir)` と同じ）。`input.txt` などはプロジェクトフォルダに置いてあります。
- コマンドライン引数が必要なプロジェクトには `run.args`（1 行 1 引数）があり，IDE から実行するときの既定の引数になります。
- 新しい `.c` やフォルダを追加すると，保存時に CMake が再構成されて自動でターゲットに加わります。

## Visual Studio で使う（Windows）

**準備**: Visual Studio 2022 以降で「**C++ によるデスクトップ開発**」ワークロードを入れる（「Windows 用 C++ CMake ツール」が含まれます）。

1. リポジトリを clone する（または ZIP を展開する）。
2. Visual Studio を起動し，**「ファイル → 開く → フォルダー」** でリポジトリのフォルダを開く。
   （`.sln` はありません。CMake プロジェクトとして開きます。）
3. 上部の構成のドロップダウンで **`Windows / MSVC (x64 Debug)`** を選ぶ。出力ウィンドウに「CMake の生成が完了しました」と出るまで待つ。
4. ツールバーの**スタートアップ項目**（▶ の横のドロップダウン）から実行したいものを選ぶ。
   - `week10 ReadText  [input.txt]` のような項目は，`.vs/launch.vs.json` の設定で**作業ディレクトリ = プロジェクトフォルダ**，**引数 = `run.args`** になっています。
   - `ReadText.exe` のような項目（CMake が自動で作るもの）は，作業ディレクトリが出力先フォルダになり，引数もありません。ファイルや引数を使う回では `weekNN 名前` の項目を選んでください。
5. **Ctrl+F5**（デバッグなしで開始）で実行，**F5** でデバッグ実行，**Ctrl+Shift+B** ですべてビルド。

引数を変えたいときは，スタートアップ項目を選んだ状態で **「デバッグ → `<項目>` のデバッグ設定と起動設定」** を開き，`args` を書き換えます（授業の「プロパティ → デバッグ → コマンド引数」に当たります）。

テストの実行は **「テスト → CTest テストの実行」**，またはテスト エクスプローラーから行います。

> [!TIP]
> 授業と同じ形（`.sln` と 1 課題 1 プロジェクト）で確認したいときは，空のプロジェクトを作り，該当フォルダの `.c`/`.h` を「既存の項目の追加」で入れるだけで動きます。ソースは BOM 付き UTF-8 なので，`/utf-8` を指定していないプロジェクトでも日本語のコメントは文字化けしません。

## VS Code で使う（Windows / macOS / Linux）

**準備**

| OS | コンパイラ | その他 |
| --- | --- | --- |
| Windows | Visual Studio 2022 以降，または「Build Tools for Visual Studio」の「C++ によるデスクトップ開発」 | CMake と Ninja は Visual Studio に含まれる |
| macOS | `xcode-select --install`（Clang） | `brew install cmake` |
| Linux | `sudo apt install build-essential gdb cmake ninja-build` | |

拡張機能 **C/C++**（`ms-vscode.cpptools`）と **CMake Tools**（`ms-vscode.cmake-tools`）を入れます（フォルダを開くと推奨拡張機能として表示されます）。

1. **「ファイル → フォルダーを開く」** でリポジトリを開く。
2. CMake Tools がプリセットを尋ねるので，Windows は **`Windows / MSVC (x64 Debug)`**，macOS / Linux は **`GCC / Clang (Debug, macOS・Linux)`** を選ぶ。
3. **実行したい課題の `.c` ファイルを開いた状態で**，「実行とデバッグ」から「**開いている課題を実行**」を選び **F5**（デバッグ）または **Ctrl+F5**（デバッグなし）。
   - 開いている `.c` のフォルダのプログラムがビルド・起動され，作業ディレクトリはそのフォルダになります。
   - 引数が必要なときは「**開いている課題を引数つきで実行**」を選び，`.vscode/launch.json` の `args` を書き換えます。
4. すべてのビルドは **Ctrl+Shift+B**，テストはステータスバーの「テスト」またはコマンド「CMake: テストの実行」。

### ターミナルから実行する（リダイレクト・パイプ）

第7回の `<`・`>`・`|` などはターミナルから実行します。実行ファイルは `out/build/<プリセット名>/bin/weekNN/` にできます。

```powershell
# Windows (PowerShell)。プロジェクトフォルダへ移動してから実行する
cd week07\Echo
Get-Content input.txt | ..\..\out\build\msvc-debug\bin\week07\Echo.exe
cmd /c "..\..\out\build\msvc-debug\bin\week07\Echo.exe < input.txt"   # cmd の < を使う場合
```

```sh
# macOS / Linux
cd week07/Echo
../../out/build/gcc-debug/bin/week07/Echo < input.txt
```

### コマンドラインだけでビルドする

```sh
cmake --preset gcc-debug          # Windows の「Developer PowerShell for VS」では msvc-debug
cmake --build --preset gcc-debug
ctest --preset gcc-debug          # すべての自動テスト
```

## TA 向け

- 各回の `weekNN/README.md` に，課題ごとの解答・実行結果・説明・表の記入例・確認問題の解答と，**採点のポイント・よくある誤り**をまとめています。
- `tests/` の期待値は演習ページの表示例・検証表から作っています。学生のプログラムの出力を比べるときにも使えます。
- 解答の追加・修正の規約は [CONTRIBUTING.md](CONTRIBUTING.md)，採点エージェント（Claude Code のサブエージェント）は [.claude/agents/softprac-grader.md](.claude/agents/softprac-grader.md) にあります。
- GitHub Actions で，Windows（MSVC `/W4 /WX`），Linux（GCC・Clang，`-Werror` と AddressSanitizer/UBSan），macOS でビルドとテストを行います。

### プロジェクトを追加・変更したとき

```sh
python3 tools/normalize_sources.py   # .c/.h を BOM 付き UTF-8・LF にそろえる
python3 tools/gen_launch_vs.py       # .vs/launch.vs.json（Visual Studio の起動設定）を作り直す
python3 tools/gen_readme_index.py    # この README の目次（各回の表とテスト数）を作り直す
```

## よくあるトラブル

| 症状 | 対処 |
| --- | --- |
| Visual Studio でスタートアップ項目が出ない | 「プロジェクト → CMake キャッシュの削除と再構成」。構成が `Windows / MSVC` になっているか確認 |
| VS Code で `cl.exe` が見つからない | プリセットを `Windows / MSVC` にする。Visual Studio（または Build Tools）の C++ ワークロードが入っているか確認 |
| `input.txt` が開けない | 作業ディレクトリがプロジェクトフォルダか確認（Visual Studio は `weekNN 名前` の項目を，VS Code は `.c` を開いた状態で起動） |
| 日本語が文字化けする | プログラムの表示は ASCII にしています。ソースのコメントが化ける場合はファイルを BOM 付き UTF-8 で保存し直す |
| 入力の終わり（EOF）の入れ方 | Windows は行頭で **Ctrl+Z → Enter**，macOS / Linux は **Ctrl+D** |
