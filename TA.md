# TA 用ブランチ（ta）

`ta` ブランチの入口です。`main`（解答と解説だけ）に，TA 用の資料・自動テスト・IDE の設定・CI・保守のための規約とツールを加えています。
解答の読み方とビルドの基本は [README.md](README.md)（`main` と共通）にあります。

> [!WARNING]
> 解答と，学生に渡す前提でないデバッグの題材の答えを含みます。学生への案内は担当教員の指示に従ってください。

## ブランチの関係

| ブランチ | 内容 | 作り方 |
| --- | --- | --- |
| `main` | 解答（`weekNN/` のソース・データファイル・`versions/`）と各回の README，ルートの README.md と最小の CMakeLists.txt | `ta` で直して確かめた解答・解説を `tools/export_main.py` で写し，`main` に PR を出す |
| `ta` | `main` ＋ このファイルの「[`ta` だけにあるもの](#ta-だけにあるもの)」 | 保守はここで行う。`main` の PR がマージされたら `git merge origin/main` で取り込む（`ta` を `main` へはマージしない） |
| `ta-results` | `ta` ＋ すべてのテストの実際の出力（`results/`） | `ta` へ push すると CI（`.github/workflows/results.yml`）が作り直して force push する。手で commit しない |
| `practice` | `main` の解答を雛形（空の `main`）にし，`ta` の `tests/` を加えた練習用。解答を見ずに課題を解き，テストで自己採点する | `tools/make_practice.py` で作る。練習は `practice` から切った自分のブランチで行う |

詳しい手順は [CONTRIBUTING.md の「ブランチ」](CONTRIBUTING.md#ブランチ)にあります。
`ta-results` と `practice` は作り直すたびに履歴が置き換わるので，`git pull` では更新できません。手元の `ta-results` は `git fetch origin && git switch -C ta-results origin/ta-results` で最新にします（`practice` から切った自分のブランチの載せ替えは `practice` の README.md）。

## 読者別の入口

| 読者 | すること | 読むもの（順に） |
| --- | --- | --- |
| TA（授業の準備） | その回の解答と採点のポイントを確かめ，演習中の声かけを用意する | 1. [各回の解答と題材の表](#各回の解答と題材の表)からその回の README（解答・解説・採点のポイント）<br>2. [実務の手引き](ta-guide/README.md)のその回の節<br>3. その回の[デバッグの題材](debugging/README.md)（第4回〜第14回） |
| TA（採点） | 学生の出力を期待値と比べる | 各プロジェクトの `tests/`（入力と期待値）と，`ta-results` ブランチの `results/`（実際の出力。見方は `results/README.md`） |
| TA（課題を体験する） | 解答を見ずに課題を解き，学生と同じ手順と難しさを確かめる | `practice` ブランチの README.md（`git switch -c practice-<名前> origin/practice`） |
| TA（環境の準備） | IDE から引数・作業ディレクトリの設定なしで実行する | [IDE で使う](#ide-で使う) |
| 保守する人 | 解答・テスト・手引き・題材を追加・修正する | [CONTRIBUTING.md](CONTRIBUTING.md)（ブランチ，規約，テストの形式，仕上げのツール，CI） |

## 各回の解答と題材の表

<!-- WEEK-TABLE:BEGIN -->
| 回 | テーマ | プロジェクト | テスト数 | 演習ページ |
| --- | --- | --- | ---: | --- |
| [第1回](week01/README.md) | プログラミングの基礎 | Broken，House，Message，Version，Welcome | 11 | [ex01](https://t-yokoga.github.io/softprac1/ex01.html) |
| [第2回](week02/README.md) | 変数 | Exchange，Observe，Profile，Rectangle，Temperature | 24 | [ex02](https://t-yokoga.github.io/softprac1/ex02.html) |
| [第3回](week03/README.md) | 演算子 | Conditions，Flags，Leap，TimeParts，Update | 43 | [ex03](https://t-yokoga.github.io/softprac1/ex03.html) |
| [第4回](week04/README.md) | 制御構造 | EvenSum，Fee，Powers，Table，YearGroup | 141 | [ex04](https://t-yokoga.github.io/softprac1/ex04.html) |
| [第5回](week05/README.md) | 配列と関数 | Array3D，ColumnSum，Functions，Maximum，SumMean，ValueCopy，Warmup05 | 50 | [ex05](https://t-yokoga.github.io/softprac1/ex05.html) |
| [第6回](week06/README.md) | 文字列 | AsciiTable，Average，CharCode，CompareJoin，CopyCapacity，Length，Lower | 40 | [ex06](https://t-yokoga.github.io/softprac1/ex06.html) |
| [第7回](week07/README.md) | 入出力 | ByteCount，Echo，Formats，LetterCount，LineInput，LowerInput，Typing | 119 | [ex07](https://t-yokoga.github.io/softprac1/ex07.html) |
| [第8回](week08/README.md) | ポインタ1 | CopyText，Decompose，MinMax，PointerWalk，Swap | 50 | [ex08](https://t-yokoga.github.io/softprac1/ex08.html) |
| [第9回](week09/README.md) | ポインタ2 | ArrayTypes，FindMax，MatrixMean，Names，RaggedRows，ReturnMaximum，SwapRows | 50 | [ex09](https://t-yokoga.github.io/softprac1/ex09.html) |
| [第10回](week10/README.md) | ファイル | Arguments，Binary，ByteOrder，CheckValue，LineLengths，NumberFormats，ParseNumber，ReadText，WriteSquares，WriteText | 191 | [ex10](https://t-yokoga.github.io/softprac1/ex10.html) |
| [第11回](week11/README.md) | 構造体 | CopyMembers，PointInit，PointMove，Rect，RectContains，StructLayout，Students | 49 | [ex11](https://t-yokoga.github.io/softprac1/ex11.html) |
| [第12回](week12/README.md) | コンパイル：分割コンパイルとライブラリ | CalcApp，CalcLib，LibraryCheck，SortModule，SplitCalc，VectorCalc | 52 | [ex12](https://t-yokoga.github.io/softprac1/ex12.html) |
| [第13回](week13/README.md) | メモリ管理 | Dynamic，DynamicCopy，DynamicVector，DynamicVectorFail，GrowArray，GrowArrayFail，NewPoint，NewPointFail，SharedCount，StorageCount | 75 | [ex13](https://t-yokoga.github.io/softprac1/ex13.html) |
| [第14回](week14/README.md) | 再帰 | CheckedFactorial，Factorial，Fibonacci，GcdLoop，Trace，TreeTraversal | 65 | [ex14](https://t-yokoga.github.io/softprac1/ex14.html) |
| [デバッグの題材](debugging/README.md) | バグ入りのプログラム（TA 用） | 17 題 | 45 | |
| | | **合計** | **1005** | |
<!-- WEEK-TABLE:END -->

テスト数は `tests/` と `variants/tests/` の期待値の数です。この表は `python3 tools/update_generated.py` で作り直します（手で書き換えません）。

## TA 用の資料

- [実務の手引き](ta-guide/README.md)（`ta-guide/`）: 各回の演習に，エラーの読み方・テスト・デバッグ・バージョン管理など実際の開発で必要になることを 1 つずつ添えるための手引きです。巡回中に 1〜3 分で使える声かけ・見せ方・確かめる問いと，どの回でも使う型（デバッグの進め方，質問・バグ報告のテンプレートなど）をまとめています。
- [デバッグの題材](debugging/README.md)（`debugging/`）: 第4回〜第14回の内容に合わせて，コンパイラの警告では見つからない誤りを 1 つずつ入れた短いプログラムです。題材ごとの README に，症状・学生への渡し方・探し方・ヒントの段階・原因・直し方があります。README は答えを含むので，学生にはソースと入力ファイルだけを渡します。
- [説明用スライド](slides/README.md)（`slides/`）: 演習の前に全員へ数分で見せる説明のスライド（Slidev）です。HTML と PDF は CI（`slides` ワークフロー）が作ります。

## `ta` だけにあるもの

```
programminglang1-ans/（ta ブランチ）
├── TA.md                 ← このファイル
├── CONTRIBUTING.md       ← 追加・修正するときの規約（ブランチ，テストの形式，仕上げ，CI）
├── CLAUDE.md，.claude/   ← Claude で保守するときの指示と評価エージェント
├── CMakeLists.txt        ← main の CMakeLists.txt にテスト・書き換えた版・CI 用のオプション・debugging/ を加えたもの
├── CMakePresets.json     ← Visual Studio / VS Code が読むビルド設定（MSVC・GCC/Clang）
├── cmake/                ← テストの実行（RunTest.cmake）と，書き換えた版（variant）を作る関数
├── weekNN/<プロジェクト>/
│   ├── tests/            ← 自動テスト（入力・引数と期待する出力）
│   ├── variants/tests/   ← 書き換えた版の期待値
│   ├── CMakeLists.txt    ← 書き換えた版（softprac_add_variant）の定義
│   └── run.args          ← IDE から実行するときの既定の引数
├── ta-guide/README.md    ← 実務の手引き
├── debugging/            ← デバッグの題材（Bug<名前>/ が 1 題）
├── slides/               ← 説明用スライド（Slidev。HTML と PDF は CI が作る）
├── tools/                ← 生成・検査・結果の収集のスクリプト
├── .vs/launch.vs.json    ← Visual Studio 用の起動設定（tools/ が作る生成物。手で直さない）
├── .vscode/              ← VS Code 用の設定
├── .github/workflows/    ← CI（ci.yml）と ta-results の作成（results.yml）
└── .editorconfig，.gitattributes
```

## 自動テスト

各プロジェクトの `tests/` に，演習ページの表示例・検証表から作った期待値（`<ケース>.out` と，入力・引数・終了コードなど）が入っています。
演習ページの「値を変えて試す」「〜に書き換えて比べる」小問は，ソースの一部を書き換えた版を CMake が自動で作ってテストしています（テスト名は `variant_<名前>`。書き換えの内容は各プロジェクトの `CMakeLists.txt`，期待値は `variants/tests/`）。
ファイルの形式は [CONTRIBUTING.md の「自動テスト」](CONTRIBUTING.md#自動テストtests)にまとめています。

すべてのプロジェクトは，MSVC（`/W4 /WX`，Debug・Release），MinGW gcc，Apple Clang，GCC・Clang（`-Werror`，AddressSanitizer/UBSan）で警告なしにビルドでき，すべてのテストに成功します（GitHub Actions で確認）。

```sh
cmake --preset gcc-debug          # Windows の「Developer PowerShell for VS」では msvc-debug
cmake --build --preset gcc-debug
ctest --preset gcc-debug          # すべての自動テスト
ctest --preset gcc-debug -R week07/Echo   # 1 つのプロジェクトだけ
```

実際の出力を `results/` に保存するには `python3 tools/collect_results.py` を実行します（`ta-results` ブランチと同じものが手元にできます。`results/` は `ta` では commit しません）。

## IDE で使う

`ta` ブランチには IDE の設定ファイル（`CMakePresets.json` など）があるので，ビルド先は各回の README の `out\build\x64-Debug\` ではなくプリセット名の `out\build\msvc-debug\`（macOS / Linux は `out/build/gcc-debug/`）になります。また，[README.md の使い方](README.md#使い方)の手順のうち，構成の選び方と引数・作業ディレクトリの設定が次のように簡単になります。

### Visual Studio（Windows）

1. **File > Open > Folder** でリポジトリのフォルダを開き，ツールバーの構成のドロップダウンで **`Windows / MSVC (x64 Debug)`** を選びます。**Output** ウィンドウに `CMake generation finished.` と出るまで待ちます。
2. ツールバーの **Startup Item** から `week10 ReadText  [input.txt]` のような項目を選んで **Ctrl+F5** で実行します。
   - この項目は `.vs/launch.vs.json` の設定で，**作業ディレクトリ = プロジェクトフォルダ**，**引数 = `run.args`** になっています。デバッグの題材は `debugging BugEvenSum` のような項目です。
   - `ReadText.exe` のような項目（CMake が自動で作るもの）は，`main` と同じく実行ファイルのフォルダ（データファイルがコピーされている）で，引数なしで起動します。
3. テストは **Test > Run CTests for softprac1_answers**，または **Test Explorer** から実行します。

引数を変えたいときは **Debug > Debug and Launch Settings for \<項目\>** で `args` を書き換えます。これは手元で試すための変更です。
`.vs/launch.vs.json` は生成物なので，書き換えたまま commit すると CI の生成物の検査が失敗します。既定の引数を変えるときは，プロジェクトフォルダの `run.args` を書き換えて `python3 tools/update_generated.py` を実行します。

### VS Code（Windows / macOS / Linux）

1. **File > Open Folder** で開き，CMake Tools が尋ねる構成のプリセットで，Windows は **`Windows / MSVC (x64 Debug)`**，macOS / Linux は **`GCC / Clang (Debug, macOS・Linux)`** を選びます。
2. **実行したい課題の `.c` ファイルを開いた状態で**，**Run and Debug** ビュー（Ctrl+Shift+D）の「開いている課題を実行 (Windows / MSVC)」（macOS / Linux は「開いている課題を実行 (macOS / Linux)」）を選び，**F5** または **Ctrl+F5** で起動します（作業ディレクトリはその `.c` のフォルダ）。
   引数が必要なときは「開いている課題を引数つきで実行 (Windows / MSVC)」（macOS / Linux は「開いている課題を引数つきで実行 (macOS / Linux)」）を選び，`.vscode/launch.json` の `args`（既定は `["input.txt"]`）を書き換えます。
   `.vscode/launch.json` は commit 対象なので，書き換えたまま commit しません（試し終わったら戻します）。
3. すべてのビルドは **Ctrl+Shift+B**，テストは **Command Palette** の **CMake: Run Tests**，または **Testing** ビューで実行します。

### よくあるトラブル（ta ブランチ）

| 症状 | 対処 |
| --- | --- |
| Visual Studio で `The CMAKE_C_COMPILER: gcc is not a full path and was not found in the PATH` | 構成のドロップダウンで **`Windows / MSVC (x64 Debug)`** を選ぶ（MSVC 以外の構成が選ばれている） |
| Visual Studio の **Startup Item** に `weekNN 名前` の項目が出ない | **Project > Delete Cache and Reconfigure**。構成が `Windows / MSVC` になっているか確認 |
| VS Code で `cl.exe` が見つからない | プリセットを `Windows / MSVC` にする。Visual Studio（または Build Tools）の C++ ワークロードが入っているか確認 |
