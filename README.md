# programminglang1-ans

「プログラミング言語I・ソフトウェア演習I」（C 言語）の **TA 用解答・解説** リポジトリです。

- 授業サイト: <https://t-yokoga.github.io/softprac1/>（資料: <https://github.com/t-yokoga/softprac1>）
- 全 14 回の演習について，課題・発展課題のソースコード，自動テスト，解答・解説（各回の `README.md`）をまとめています。
- TA 用の資料として，各回の演習に実際の開発で必要になることを添える**実務の手引き**と，誤りを 1 つ入れた**デバッグの題材**があります。
- 1 つのリポジトリで **Visual Studio**（Windows）と **VS Code**（Windows / macOS / Linux）のどちらからでもビルド・実行できるように，CMake で管理しています。

> [!WARNING]
> 公開リポジトリで，解答を含みます。学生にこのリポジトリを案内するかどうかと，その時期・範囲は，担当教員の指示に従ってください。

## 読者別の入口

| 読者 | すること | 読むもの（順に） |
| --- | --- | --- |
| TA（授業の準備） | その回の解答と採点のポイントを確かめ，演習中の声かけを用意する | 1. 下の表からその回の README（解答・解説・採点のポイント）<br>2. README の冒頭の「TA 用の資料」から[実務の手引き](ta-guide/README.md)のその回の節<br>3. その回の[デバッグの題材](debugging/README.md)（第4回〜第14回） |
| TA・学生（環境の準備） | 手元でビルド・実行・テストする | [Visual Studio で使う](#visual-studio-で使うwindows)，または [VS Code で使う](#vs-code-で使うwindows--macos--linux)。困ったら[よくあるトラブル](#よくあるトラブル) |
| 保守する人 | 解答・手引き・題材を追加・修正する | [CONTRIBUTING.md](CONTRIBUTING.md)（規約，テストの形式，仕上げのツール，CI） |

## 各回の解答

<!-- WEEK-TABLE:BEGIN -->
| 回 | テーマ | プロジェクト | テスト数 | 演習ページ |
| --- | --- | --- | ---: | --- |
| [第1回](week01/README.md) | プログラミングの基礎 | Broken，House，Message，Version，Welcome | 11 | [ex01](https://t-yokoga.github.io/softprac1/ex01.html) |
| [第2回](week02/README.md) | 変数 | Exchange，Observe，Profile，Rectangle，Temperature | 21 | [ex02](https://t-yokoga.github.io/softprac1/ex02.html) |
| [第3回](week03/README.md) | 演算子 | Conditions，Flags，Leap，TimeParts，Update | 40 | [ex03](https://t-yokoga.github.io/softprac1/ex03.html) |
| [第4回](week04/README.md) | 制御構造 | EvenSum，Fee，Powers，Table，YearGroup | 127 | [ex04](https://t-yokoga.github.io/softprac1/ex04.html) |
| [第5回](week05/README.md) | 配列と関数 | Array3D，ColumnSum，Functions，Maximum，SumMean，ValueCopy，Warmup05 | 37 | [ex05](https://t-yokoga.github.io/softprac1/ex05.html) |
| [第6回](week06/README.md) | 文字列 | AsciiTable，Average，CharCode，CompareJoin，CopyCapacity，Length，Lower | 40 | [ex06](https://t-yokoga.github.io/softprac1/ex06.html) |
| [第7回](week07/README.md) | 入出力 | ByteCount，Echo，Formats，LetterCount，LineInput，LowerInput，Typing | 92 | [ex07](https://t-yokoga.github.io/softprac1/ex07.html) |
| [第8回](week08/README.md) | ポインタ1 | CopyText，Decompose，MinMax，PointerWalk，Swap | 43 | [ex08](https://t-yokoga.github.io/softprac1/ex08.html) |
| [第9回](week09/README.md) | ポインタ2 | ArrayTypes，FindMax，MatrixMean，Names，RaggedRows，ReturnMaximum，SwapRows | 42 | [ex09](https://t-yokoga.github.io/softprac1/ex09.html) |
| [第10回](week10/README.md) | ファイル | Arguments，Binary，ByteOrder，CheckValue，LineLengths，NumberFormats，ParseNumber，ReadText，WriteSquares，WriteText | 132 | [ex10](https://t-yokoga.github.io/softprac1/ex10.html) |
| [第11回](week11/README.md) | 構造体 | CopyMembers，PointInit，PointMove，Rect，RectContains，StructLayout，Students | 49 | [ex11](https://t-yokoga.github.io/softprac1/ex11.html) |
| [第12回](week12/README.md) | コンパイル：分割コンパイルとライブラリ | CalcApp，CalcLib，LibraryCheck，SortModule，SplitCalc，VectorCalc | 34 | [ex12](https://t-yokoga.github.io/softprac1/ex12.html) |
| [第13回](week13/README.md) | メモリ管理 | Dynamic，DynamicCopy，DynamicVector，DynamicVectorFail，GrowArray，GrowArrayFail，NewPoint，NewPointFail，SharedCount，StorageCount | 66 | [ex13](https://t-yokoga.github.io/softprac1/ex13.html) |
| [第14回](week14/README.md) | 再帰 | CheckedFactorial，Factorial，Fibonacci，GcdLoop，Trace，TreeTraversal | 63 | [ex14](https://t-yokoga.github.io/softprac1/ex14.html) |
| [デバッグの題材](debugging/README.md) | バグ入りのプログラム（TA 用） | 17 題 | 45 | |
| | | **合計** | **842** | |
<!-- WEEK-TABLE:END -->

テスト数は `tests/` と `variants/tests/` の期待値の数です。この表は `python3 tools/update_generated.py` で作り直します（手で書き換えません）。

## TA 用の資料

- [実務の手引き](ta-guide/README.md)（`ta-guide/`）: 各回の演習に，エラーの読み方・テスト・デバッグ・バージョン管理など実際の開発で必要になることを 1 つずつ添えるための手引きです。巡回中に 1〜3 分で使える声かけ・見せ方・確かめる問いと，どの回でも使う型（デバッグの進め方，質問・バグ報告のテンプレートなど）をまとめています。
- [デバッグの題材](debugging/README.md)（`debugging/`）: 第4回〜第14回の内容に合わせて，コンパイラの警告では見つからない誤りを 1 つずつ入れた短いプログラムです。題材ごとの README に，症状・学生への渡し方・探し方・ヒントの段階・原因・直し方があります。README は答えを含むので，学生にはソースと入力ファイルだけを渡します。

各回の README の冒頭の「TA 用の資料」の行から，その回の手引きの節と題材へ移れます。

## 解答の読み方

- 各回の `weekNN/README.md` に，課題ごとの解答コード・実行結果・説明・表の記入例・確認問題の解答と，TA 向けの**採点のポイント・よくある誤り**をまとめています。
- 各プロジェクトフォルダのソースは，演習ページの「期待する表示」をそのまま出す版です。演習ページの「値を変えて試す」「〜に書き換えて比べる」小問は，
  ソースの一部を書き換えた版を自動でビルドしてテストしています（README では `variant_<名前>` というテスト名で示します）。
  書き換えの内容は各フォルダの `CMakeLists.txt` に，確認用の短いプログラムは `versions/` に置いています。
- 実行結果は，実際にビルド・実行した出力をそのまま載せています。アドレスや `sizeof long` のように環境で変わる値は，その都度環境を書いています。
- コンパイラの診断（エラー・警告の文面）は GCC・Clang で実際に出したものです。MSVC のエラー・警告番号（`C2143` など）は Microsoft のドキュメントに基づく例で，文面は Visual Studio の版や言語設定によって変わります。

### 自動テスト

各プロジェクトの `tests/` に，演習ページの表示例・検証表から作った期待値（`<ケース>.out` と，入力・引数・終了コードなど）が入っています。学生のプログラムの出力を比べるときにも使えます。書き換えた版の期待値は `variants/tests/` にあります。ファイルの形式は [CONTRIBUTING.md の「自動テスト」](CONTRIBUTING.md#自動テストtests)にまとめています。

すべてのプロジェクトは，MSVC（`/W4 /WX`，Debug・Release），MinGW gcc，Apple Clang，GCC・Clang（`-Werror`，AddressSanitizer/UBSan）で警告なしにビルドでき，すべてのテストに成功します（GitHub Actions で確認）。

## しくみ

授業では「1 課題 = 1 つの空のプロジェクト = 1 つの `main`」で作業します。このリポジトリでは同じ単位を **1 フォルダ** で表します。

```
programminglang1-ans/
├── README.md             ← このファイル（入口）
├── CONTRIBUTING.md       ← 追加・修正するときの規約
├── CMakeLists.txt        ← weekNN/・debugging/ のプロジェクトフォルダを自動で見つけて実行ファイルにする
├── CMakePresets.json     ← Visual Studio / VS Code が読むビルド設定（MSVC・GCC/Clang）
├── cmake/                ← テストの実行と，書き換えた版（variant）を作る CMake の関数
├── week01/
│   ├── README.md         ← 第1回の解答・解説
│   ├── Welcome/
│   │   ├── welcome.c     ← ビルドすると Welcome.exe になる
│   │   └── tests/        ← 期待する出力（自動テスト）
│   └── Message/ ...
├── week02/ ...
├── ta-guide/README.md    ← 実務の手引き（TA 用）
├── debugging/            ← デバッグの題材（TA 用。Bug<名前>/ が 1 題）
├── tools/                ← 生成と検査のスクリプト（update_generated.py，check_docs.py など）
├── .vs/launch.vs.json    ← Visual Studio 用の起動設定（tools/ が作る生成物。手で直さない）
└── .vscode/              ← VS Code 用の設定
```

- `weekNN/<プロジェクト名>/` の `*.c` はまとめて `<プロジェクト名>.exe` になります（分割コンパイルの回も同じ）。`debugging/Bug<名前>/` も同じ規則です。
- 授業と同じく **C17・警告レベル4（`/W4`）** でコンパイルします。GCC/Clang では `-Wall -Wextra -Wpedantic` です。
- プログラムの**作業ディレクトリはプロジェクトフォルダ**です（授業の `$(ProjectDir)` と同じ）。`input.txt` などはプロジェクトフォルダに置いてあります。
- コマンドライン引数が必要なプロジェクトには `run.args`（1 行 1 引数）があり，IDE から実行するときの既定の引数になります。
- 新しい `.c` やフォルダを追加すると，次のビルドのときに CMake が自動で再構成し，ターゲットに加わります。

## Visual Studio で使う（Windows）

画面の表記は Visual Studio 2026（英語版）に合わせています。

**準備**: Visual Studio 2022 以降の Visual Studio Installer で **Desktop development with C++** ワークロードを入れます（**C++ CMake tools for Windows** が含まれます）。

1. リポジトリを clone します（または ZIP を展開します）。
2. Visual Studio を起動し，**File > Open > Folder** でリポジトリのフォルダを開きます。
   （`.sln` はありません。CMake プロジェクトとして開きます。）
3. ツールバーの構成のドロップダウンで **`Windows / MSVC (x64 Debug)`** を選びます。**Output** ウィンドウに `CMake generation finished.` と出るまで待ちます。
4. ツールバーの **Startup Item**（▶ の横のドロップダウン）から実行したいものを選びます。
   - `week10 ReadText  [input.txt]` のような項目は，`.vs/launch.vs.json` の設定で**作業ディレクトリ = プロジェクトフォルダ**，**引数 = `run.args`** になっています。デバッグの題材は `debugging BugEvenSum` のような項目です。
   - `ReadText.exe` のような項目（CMake が自動で作るもの）は，作業ディレクトリが出力先フォルダになり，引数もありません。ファイルや引数を使う回では `weekNN 名前` の項目を選んでください。
5. **Ctrl+F5**（**Debug > Start Without Debugging**）で実行，**F5**（**Debug > Start Debugging**）でデバッグ実行，**Ctrl+Shift+B**（**Build > Build All**）ですべてビルドします。

引数を変えたいときは，**Startup Item** で項目を選んだ状態で **Debug > Debug and Launch Settings for \<項目\>** を開き，`args` を書き換えます（授業の **Properties > Configuration Properties > Debugging > Command Arguments** に当たります）。
これは手元で試すための変更です。`.vs/launch.vs.json` は生成物なので，書き換えたまま commit すると CI の生成物の検査が失敗します。既定の引数を変えるときは，プロジェクトフォルダの `run.args` を書き換えて `python3 tools/update_generated.py` を実行します。

テストの実行は **Test > Run CTests for softprac1_answers**，または **Test Explorer** から行います。

**Solution Explorer** は既定でフォルダ表示です。ツールバーの **Select View** ボタンから **CMake Targets View** を選ぶと，実行ファイル（ターゲット）ごとに表示できます。

> [!TIP]
> 授業と同じ形（`.sln` と 1 課題 1 プロジェクト）で確認したいときは，**Create a new project > Empty Project** で空のプロジェクトを作り，該当フォルダの `.c`/`.h` を **Add > Existing Item** で入れるだけで動きます。ソースは BOM 付き UTF-8 なので，`/utf-8` を指定していないプロジェクトでも日本語のコメントは文字化けしません。

## VS Code で使う（Windows / macOS / Linux）

画面の表記は VS Code（英語版）に合わせています。

**準備**

| OS | コンパイラ | その他 |
| --- | --- | --- |
| Windows | Visual Studio 2022 以降，または Build Tools for Visual Studio の **Desktop development with C++** | CMake と Ninja は Visual Studio に含まれる |
| macOS | `xcode-select --install`（Clang） | `brew install cmake` |
| Linux | `sudo apt install build-essential gdb cmake ninja-build` | |

拡張機能 **C/C++**（`ms-vscode.cpptools`）と **CMake Tools**（`ms-vscode.cmake-tools`）を入れます（フォルダを開くと推奨拡張機能として表示されます）。

1. **File > Open Folder** でリポジトリのフォルダを開きます。
2. CMake Tools が構成のプリセットを尋ねるので，Windows は **`Windows / MSVC (x64 Debug)`**，macOS / Linux は **`GCC / Clang (Debug, macOS・Linux)`** を選びます（後から変えるときは **Command Palette**（Ctrl+Shift+P）の **CMake: Select Configure Preset**）。
3. **実行したい課題の `.c` ファイルを開いた状態で**，**Run and Debug** ビュー（Ctrl+Shift+D）の構成のドロップダウンから「**開いている課題を実行**」を選び，**F5**（**Run > Start Debugging**）または **Ctrl+F5**（**Run > Run Without Debugging**）で起動します。
   - 開いている `.c` のフォルダのプログラムがビルド・起動され，作業ディレクトリはそのフォルダになります。
   - 引数が必要なときは「**開いている課題を引数つきで実行**」を選び，`.vscode/launch.json` の `args` を書き換えます。
4. すべてのビルドは **Ctrl+Shift+B**（**Terminal > Run Build Task**），テストは **Command Palette** の **CMake: Run Tests**，または **Testing** ビューで実行します。

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

## よくあるトラブル

| 症状 | 対処 |
| --- | --- |
| Visual Studio で `The CMAKE_C_COMPILER: gcc is not a full path and was not found in the PATH` | 構成のドロップダウンで **`Windows / MSVC (x64 Debug)`** を選ぶ（MSVC 以外の構成が選ばれている） |
| Visual Studio の **Startup Item** に項目が出ない | **Project > Delete Cache and Reconfigure**。構成が `Windows / MSVC` になっているか確認 |
| VS Code で `cl.exe` が見つからない | プリセットを `Windows / MSVC` にする。Visual Studio（または Build Tools）の C++ ワークロードが入っているか確認 |
| `input.txt` が開けない | 作業ディレクトリがプロジェクトフォルダか確認（Visual Studio は `weekNN 名前` の項目を，VS Code は `.c` を開いた状態で起動） |
| 日本語が文字化けする | プログラムの表示は ASCII にしています。ソースのコメントが化ける場合はファイルを BOM 付き UTF-8 で保存し直す |
| 入力の終わり（EOF）の入れ方 | Windows は行頭で **Ctrl+Z → Enter**，macOS / Linux は **Ctrl+D** |
| push すると CI の repository-checks が失敗する | 手元で `python3 tools/update_generated.py` と `python3 tools/check_docs.py` を実行し，変わったファイルを commit する（[CONTRIBUTING.md の「仕上げ」](CONTRIBUTING.md#仕上げ)） |

## 追加・修正するとき

解答・実務の手引き・デバッグの題材を追加・修正するときの規約（フォルダ構成，ソースとテストの形式，README の書き方，仕上げのツール，CI）は [CONTRIBUTING.md](CONTRIBUTING.md) にまとめています。
