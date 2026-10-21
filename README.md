# programminglang1-ans

「プログラミング言語I・ソフトウェア演習I」（C 言語）の **TA 用解答・解説** リポジトリです。

- 授業サイト: <https://t-yokoga.github.io/softprac1/>（資料: <https://github.com/t-yokoga/softprac1>）
- 全 14 回の演習について，課題・発展課題のソースコードと，解答・解説（各回の `README.md`）をまとめています。

> [!WARNING]
> 公開リポジトリで，解答を含みます。学生にこのリポジトリを案内するかどうかと，その時期・範囲は，担当教員の指示に従ってください。

## ブランチ

| ブランチ | 内容 | 使う人 |
| --- | --- | --- |
| `main` | 解答（ソース・入力ファイル）と解説（各回の README）。ビルドに必要な最小限のファイルだけを置いています | TA・学生 |
| `ta` | `main` に，TA 用の資料（実務の手引き・デバッグの題材），自動テスト（期待する出力），IDE の設定，CI，保守の規約とツールを加えたもの。入口は `ta` ブランチの `TA.md` です | TA・保守する人 |
| `ta-results` | `ta` のすべてのテストを実際に実行した結果（標準出力・標準エラー出力・終了コード・作られたファイル）を `results/` に加えたもの。学生の出力と比べるときに使います | TA |
| `practice` | 解答を雛形（空の `main`）に置き換え，入力ファイルと自動テスト（期待する出力）だけを残したもの。解答を見ずに課題を解き，学生と同じ手順と難しさを体験するときに使います | TA |

解答（`weekNN/` のソース・データファイル）と各回の README は，3 つのブランチで同じ内容です。
保守は `ta` ブランチで行い（テストと CI で確かめるため），解答と解説の変更を `main` に反映します（手順と規約は `ta` ブランチの `CONTRIBUTING.md`）。

## 各回の解答

<!-- WEEK-TABLE:BEGIN -->
| 回 | テーマ | プロジェクト | 演習ページ |
| --- | --- | --- | --- |
| [第1回](week01/README.md) | プログラミングの基礎 | Broken，House，Message，Version，Welcome | [ex01](https://t-yokoga.github.io/softprac1/ex01.html) |
| [第2回](week02/README.md) | 変数 | Exchange，Observe，Profile，Rectangle，Temperature | [ex02](https://t-yokoga.github.io/softprac1/ex02.html) |
| [第3回](week03/README.md) | 演算子 | Conditions，Flags，Leap，TimeParts，Update | [ex03](https://t-yokoga.github.io/softprac1/ex03.html) |
| [第4回](week04/README.md) | 制御構造 | EvenSum，Fee，Powers，Table，YearGroup | [ex04](https://t-yokoga.github.io/softprac1/ex04.html) |
| [第5回](week05/README.md) | 配列と関数 | Array3D，ColumnSum，Functions，Maximum，SumMean，ValueCopy，Warmup05 | [ex05](https://t-yokoga.github.io/softprac1/ex05.html) |
| [第6回](week06/README.md) | 文字列 | AsciiTable，Average，CharCode，CompareJoin，CopyCapacity，Length，Lower | [ex06](https://t-yokoga.github.io/softprac1/ex06.html) |
| [第7回](week07/README.md) | 入出力 | ByteCount，Echo，Formats，LetterCount，LineInput，LowerInput，Typing | [ex07](https://t-yokoga.github.io/softprac1/ex07.html) |
| [第8回](week08/README.md) | ポインタ1 | CopyText，Decompose，MinMax，PointerWalk，Swap | [ex08](https://t-yokoga.github.io/softprac1/ex08.html) |
| [第9回](week09/README.md) | ポインタ2 | ArrayTypes，FindMax，MatrixMean，Names，RaggedRows，ReturnMaximum，SwapRows | [ex09](https://t-yokoga.github.io/softprac1/ex09.html) |
| [第10回](week10/README.md) | ファイル | Arguments，Binary，ByteOrder，CheckValue，LineLengths，NumberFormats，ParseNumber，ReadText，WriteSquares，WriteText | [ex10](https://t-yokoga.github.io/softprac1/ex10.html) |
| [第11回](week11/README.md) | 構造体 | CopyMembers，PointInit，PointMove，Rect，RectContains，StructLayout，Students | [ex11](https://t-yokoga.github.io/softprac1/ex11.html) |
| [第12回](week12/README.md) | コンパイル：分割コンパイルとライブラリ | CalcApp，CalcLib，LibraryCheck，SortModule，SplitCalc，VectorCalc | [ex12](https://t-yokoga.github.io/softprac1/ex12.html) |
| [第13回](week13/README.md) | メモリ管理 | Dynamic，DynamicCopy，DynamicVector，DynamicVectorFail，GrowArray，GrowArrayFail，NewPoint，NewPointFail，SharedCount，StorageCount | [ex13](https://t-yokoga.github.io/softprac1/ex13.html) |
| [第14回](week14/README.md) | 再帰 | CheckedFactorial，Factorial，Fibonacci，GcdLoop，Trace，TreeTraversal | [ex14](https://t-yokoga.github.io/softprac1/ex14.html) |
<!-- WEEK-TABLE:END -->

## 解答の読み方

- 各回の `weekNN/README.md` に，課題ごとの解答コード・実行結果・説明・表の記入例・確認問題の解答と，TA 向けの**採点のポイント・よくある誤り**をまとめています。
- 各プロジェクトフォルダのソースは，演習ページの「期待する表示」をそのまま出す版です。
  演習ページの「値を変えて試す」「〜に書き換えて比べる」小問は，書き換え方と結果を README に載せています（試すときは[ソースを書き換えて試す](#ソースを書き換えて試す)）。
  README に載せた比較用・確認用のプログラムは，プロジェクトフォルダの `versions/` にあります。
- 実行結果は，実際にビルド・実行した出力をそのまま載せています。アドレスや `sizeof long` のように環境で変わる値は，その都度環境を書いています。
- コンパイラの診断（エラー・警告の文面）は GCC・Clang で実際に出したものです。MSVC のエラー・警告番号（`C2143` など）は Microsoft のドキュメントに基づく例で，文面は Visual Studio の版や言語設定によって変わります。
- すべてのプロジェクトは，MSVC（`/W4`），GCC・Clang（`-Wall -Wextra -Wpedantic`）で警告なしにビルドでき，演習ページの表示例と同じ出力になることを `ta` ブランチの自動テストで確かめています。

## フォルダの構成

授業では「1 課題 = 1 つの空のプロジェクト = 1 つの `main`」で作業します。このリポジトリでは同じ単位を **1 フォルダ** で表します。

```
programminglang1-ans/
├── README.md             ← このファイル（入口と使い方）
├── CMakeLists.txt        ← Visual Studio・VS Code でフォルダを開いてビルドするための設定（これだけで全課題をビルドできる）
├── week01/
│   ├── README.md         ← 第1回の解答・解説
│   ├── Welcome/
│   │   └── welcome.c     ← 1 フォルダ = 1 プロジェクト = 1 つの実行ファイル（Welcome.exe）
│   ├── Message/ ...
│   └── _Broken/          ← 名前が _ で始まるフォルダは，意図的にエラーを含むコード（ビルドしない）
├── week02/ ...
└── week14/
```

- `weekNN/<プロジェクト名>/` 直下の `*.c` をまとめると，1 つの実行ファイルになります（分割コンパイルの回も同じ）。`versions/` などのサブフォルダは含みません。
- `input.txt` などのデータファイルは，それを読むプロジェクトのフォルダに置いてあります。
- プロジェクトフォルダの `CMakeLists.txt` は，第12回の `CalcLib`・`CalcApp`（静的ライブラリとそれを使うアプリ）と，第13回の `DynamicVectorFail`（`DynamicVector` のソースを一部使う）にだけあります。

## 使い方

授業と同じく **C17・警告レベル4（`/W4`）** でビルドします。GCC/Clang では `-Wall -Wextra -Wpedantic` です。
ビルドの方法は次の 4 つのどれでもかまいません（`CMakeLists.txt` は 3・4 で使うだけで，1・2 の邪魔はしません）。

| 方法 | 向いているとき |
| --- | --- |
| 1. [コマンドでビルドする](#1-コマンドでビルドする) | 1 つの課題をすぐ試す。リダイレクト（`<`・`>`・`|`）を使う（第7回など） |
| 2. [授業と同じ空のプロジェクトで使う](#2-授業と同じ空のプロジェクトで使うvisual-studio) | 授業の手順どおりに確かめる（Visual Studio） |
| 3. [Visual Studio でフォルダーを開く](#3-visual-studio-でフォルダーを開く) | 全課題をまとめてビルドし，切り替えながら実行・デバッグする |
| 4. [VS Code で使う](#4-vs-code-で使うwindows--macos--linux) | macOS / Linux，または VS Code で作業する |

### 準備

| OS | 入れるもの |
| --- | --- |
| Windows | Visual Studio 2022 以降（Visual Studio Installer で **Desktop development with C++** ワークロード。CMake と Ninja も含まれる） |
| macOS | `xcode-select --install`（Clang）。3・4 の方法を使うときは `brew install cmake` も |
| Linux | `sudo apt install build-essential gdb cmake` |

### 1. コマンドでビルドする

プロジェクトフォルダへ移動して，フォルダ直下の `.c` をまとめてコンパイルします。作業ディレクトリがプロジェクトフォルダになるので，`input.txt` などはそのまま読めます。

```sh
# macOS / Linux（gcc の代わりに clang でもよい）
cd week07/Echo
gcc -std=c17 -Wall -Wextra -Wpedantic *.c -o a.out -lm
./a.out < input.txt
```

```powershell
# Windows: スタート メニューの「Developer PowerShell for VS」で
cd week07\Echo
cl /std:c17 /W4 /utf-8 *.c /Fe:a.exe
Get-Content input.txt | .\a.exe          # PowerShell には < がないので，パイプで渡す
cmd /c "a.exe < input.txt"               # cmd の < を使う場合
```

- コマンドライン引数は実行ファイルの後に並べます（例: `./a.out input.txt`）。各回の README に，課題ごとに使う引数を書いています。
- 第12回の `CalcApp`（ライブラリを使う）と第13回の `DynamicVectorFail`（`DynamicVector` のソースも使う）は，それぞれの回の README のコマンドでビルドします。
- 比較用のプログラム（`versions/*.c`）は，そのファイル 1 つだけをコンパイルします（例: `gcc -std=c17 -Wall -Wextra -Wpedantic versions/powers_while.c -o a.out`）。
- 第13回などでメモリの誤りを確かめるときは，Linux・macOS で `-fsanitize=address,undefined -g` を付けてビルドすると，AddressSanitizer・UBSan が範囲外アクセスやリーク（Linux）を報告します。

### 2. 授業と同じ空のプロジェクトで使う（Visual Studio）

1. 授業の手順どおり，**Create a new project > Empty Project** でプロジェクトを作ります。
2. **Solution Explorer** の **Source Files** を右クリックし，**Add > Existing Item** でプロジェクトフォルダの `.c`（と `.h`）を追加します。
3. `input.txt` などのデータファイルを使う課題は，ファイルを作ったプロジェクトのフォルダ（`.vcxproj` と同じフォルダ。授業の `$(ProjectDir)`）にコピーします。
4. 引数を使う課題は，プロジェクトの **Properties > Configuration Properties > Debugging > Command Arguments** に引数を書きます。
5. **Ctrl+F5**（**Debug > Start Without Debugging**）で実行します。

ソースは BOM 付き UTF-8 なので，`/utf-8` を指定していないプロジェクトでも日本語のコメントは文字化けしません。

### 3. Visual Studio でフォルダーを開く

1. Visual Studio を起動し，**File > Open > Folder** でリポジトリのフォルダを開きます（`.sln` はありません。CMake のプロジェクトとして開きます）。
2. **Output** ウィンドウに `CMake generation finished.` と出るまで待ちます。ツールバーの構成は **x64-Debug** のままでかまいません。
3. ツールバーの **Startup Item**（▶ の横のドロップダウン）で実行したいプロジェクト（`Echo.exe` など）を選びます。
4. **Ctrl+F5**（**Debug > Start Without Debugging**）で実行，**F5**（**Debug > Start Debugging**）でデバッグ実行，**Ctrl+Shift+B**（**Build > Build All**）ですべてビルドします。

- 実行ファイルは `out\build\x64-Debug\bin\weekNN\<プロジェクト名>\` にでき，プロジェクトフォルダの `input.txt` などのデータファイルも同じフォルダにコピーされます。
  作業ディレクトリはこのフォルダなので，データファイルを読む課題もそのまま動きます。プログラムが書き出すファイル（第10回）もこのフォルダにできます。
- 引数を使う課題は，**Startup Item** でプロジェクトを選んだ状態で **Debug > Debug and Launch Settings for \<プロジェクト\>** を開き，表示された構成に `"args"` を足します（授業の **Command Arguments** に当たります）。
  この設定は `.vs/launch.vs.json` に保存されます（リポジトリには含めません）。

  ```json
  {
    "type": "default",
    "project": "CMakeLists.txt",
    "projectTarget": "ReadText.exe (week10\\ReadText\\ReadText.exe)",
    "name": "ReadText.exe (week10\\ReadText\\ReadText.exe)",
    "args": [ "input.txt" ]
  }
  ```

- `input.txt` を書き換えたときは，次のビルドでコピーし直されます。

### 4. VS Code で使う（Windows / macOS / Linux）

拡張機能 **C/C++**（`ms-vscode.cpptools`）と **CMake Tools**（`ms-vscode.cmake-tools`）を入れます。

1. **File > Open Folder** でリポジトリのフォルダを開きます。
2. CMake Tools がキット（コンパイラ）を尋ねるので，Windows は **Visual Studio Community 2026 Release - amd64** などの MSVC，macOS / Linux は Clang か GCC を選びます（後から変えるときは **Command Palette**（Ctrl+Shift+P）の **CMake: Select a Kit**）。
3. **Command Palette** の **CMake: Set Launch/Debug Target** で実行したいプロジェクトを選び，**CMake: Run Without Debugging**（Ctrl+Shift+F5）で実行，**CMake: Debug**（Shift+F5）でデバッグ実行します。
   すべてのビルドは **CMake: Build**（F7）です。

- 実行ファイルとデータファイルの場所，作業ディレクトリは 3 と同じです（ビルド先は `build/`）。
- 引数を使う課題は，**File > Preferences > Settings** の **Workspace** タブで `cmake.debugConfig` を検索し，**Edit in settings.json** で次のように書きます（`.vscode/settings.json` に保存されます。リポジトリには含めません）。

  ```json
  { "cmake.debugConfig": { "args": [ "input.txt" ] } }
  ```

- リダイレクト（`<`）を使う課題（第7回）は，**Terminal > New Terminal** で 1 の方法を使います。

### ソースを書き換えて試す

演習ページの「値を変えて試す」「〜に書き換えて比べる」小問は，README の書き換え方に従ってソースを書き換え，ビルドし直して実行します。確かめたら `git restore <ファイル>`（または **Source Control** ビューの **Discard Changes**）で元に戻します。

## よくあるトラブル

| 症状 | 対処 |
| --- | --- |
| Visual Studio の **Startup Item** にプロジェクトが出ない | **Project > Delete Cache and Reconfigure** |
| VS Code で `cl.exe` が見つからない | キットに MSVC を選ぶ。Visual Studio（または Build Tools for Visual Studio）の C++ ワークロードが入っているか確認 |
| `input.txt` が開けない | 作業ディレクトリに `input.txt` があるか確認（1 はプロジェクトフォルダで実行，2 は `.vcxproj` のフォルダにコピー，3・4 はビルドし直す） |
| 日本語が文字化けする | プログラムの表示は ASCII にしています。ソースのコメントが化ける場合はファイルを BOM 付き UTF-8 で保存し直す |
| 入力の終わり（EOF）の入れ方 | Windows は行頭で **Ctrl+Z → Enter**，macOS / Linux は **Ctrl+D** |
