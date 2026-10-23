# programminglang1-ans（practice ブランチ）

「プログラミング言語I・ソフトウェア演習I」（C 言語）の課題を，**解答を見ずに自分で書いて**，学生と同じ手順と難しさを体験するためのブランチです。
各プロジェクトのソースは雛形（空の `main`）になっていて，入力ファイルと自動テスト（期待する出力）だけが入っています。

- 授業サイト: <https://t-yokoga.github.io/softprac1/>
- 解答と解説は [`main`](https://github.com/NS28cse/programminglang1-ans/tree/main) ブランチ，テストの実際の出力は [`ta-results`](https://github.com/NS28cse/programminglang1-ans/tree/ta-results/results) ブランチにあります（このブランチは [`ta`](https://github.com/NS28cse/programminglang1-ans/tree/ta) の `tools/make_practice.py` で作っています）。

## 進め方

1. 自分用のブランチを作ります（`practice` は雛形のまま残しておくと，やり直しや他の人の練習に使えます）。

   ```sh
   git switch -c practice-<名前> origin/practice
   ```

   `practice` はテストが変わると作り直されます（履歴が置き換わるので `git pull` では更新できません）。新しいテストで続けるときは，`git fetch` してから自分のコミットを載せ替えます。

   ```sh
   git fetch origin
   git rebase --onto origin/practice origin/practice@{1}   # origin/practice@{1} は fetch する前の practice
   ```

   `origin/practice@{1}` が使えないとき（clone し直したときなど）は，`git log --oneline` で自分のコミットのすぐ下にある `practice: 解答を雛形にする（main …）` のコミットを探し，その名前（例: `dcc3463`）を代わりに書きます。

2. その回の README（[各回の課題](#各回の課題)）で，課題とプロジェクト・作るファイルを確かめます。
3. 演習ページを読み，プロジェクトフォルダの雛形に解答を書きます。ファイルの名前と分け方は演習ページの指定どおりにしてあります。
4. ビルドして実行し，[テストで確かめます](#テストで確かめる)。
5. 終わったら commit し，`main` の解答と比べます。

   ```sh
   git diff origin/main -- 'week05/Functions/*.c' 'week05/Functions/*.h'   # 自分の解答と main の解答の違い
   ```

## 各回の課題

<!-- WEEK-TABLE:BEGIN -->
| 回 | テーマ | プロジェクト | テスト数 |
| --- | --- | --- | ---: |
| [第1回](week01/README.md) | プログラミングの基礎 | Broken，House，Message，Version，Welcome | 5 |
| [第2回](week02/README.md) | 変数 | Exchange，Observe，Profile，Rectangle，Temperature | 4 |
| [第3回](week03/README.md) | 演算子 | Conditions，Flags，Leap，TimeParts，Update | 5 |
| [第4回](week04/README.md) | 制御構造 | EvenSum，Fee，Powers，Table，YearGroup | 5 |
| [第5回](week05/README.md) | 配列と関数 | Array3D，ColumnSum，Functions，Maximum，SumMean，ValueCopy，Warmup05 | 7 |
| [第6回](week06/README.md) | 文字列 | AsciiTable，Average，CharCode，CompareJoin，CopyCapacity，Length，Lower | 7 |
| [第7回](week07/README.md) | 入出力 | ByteCount，Echo，Formats，LetterCount，LineInput，LowerInput，Typing | 60 |
| [第8回](week08/README.md) | ポインタ1 | CopyText，Decompose，MinMax，PointerWalk，Swap | 5 |
| [第9回](week09/README.md) | ポインタ2 | ArrayTypes，FindMax，MatrixMean，Names，RaggedRows，ReturnMaximum，SwapRows | 7 |
| [第10回](week10/README.md) | ファイル | Arguments，Binary，ByteOrder，CheckValue，LineLengths，NumberFormats，ParseNumber，ReadText，WriteSquares，WriteText | 109 |
| [第11回](week11/README.md) | 構造体 | CopyMembers，PointInit，PointMove，Rect，RectContains，StructLayout，Students | 7 |
| [第12回](week12/README.md) | コンパイル：分割コンパイルとライブラリ | CalcApp，CalcLib，LibraryCheck，SortModule，SplitCalc，VectorCalc | 21 |
| [第13回](week13/README.md) | メモリ管理 | Dynamic，DynamicCopy，DynamicVector，DynamicVectorFail，GrowArray，GrowArrayFail，NewPoint，NewPointFail，SharedCount，StorageCount | 39 |
| [第14回](week14/README.md) | 再帰 | CheckedFactorial，Factorial，Fibonacci，GcdLoop，Trace，TreeTraversal | 6 |
<!-- WEEK-TABLE:END -->

## テストで確かめる

テストは各プロジェクトの `tests/` にあり，`<ケース>.in`（標準入力）・`<ケース>.args`（引数）でプログラムを実行して，標準出力が `<ケース>.out` と一致するかを確かめます（終了コードは `.code`，作られるファイルは `.files/`）。
テストを動かすには CMake を使います（[使い方](#使い方)の 3・4）。

| 方法 | テストの実行 |
| --- | --- |
| コマンド | `cmake -S . -B build && cmake --build build --config Debug` の後，`ctest --test-dir build -C Debug -R week05/Functions --output-on-failure`（`-R` で回やプロジェクトを絞る。`-R week05` なら第5回すべて。`--config`・`-C` は Windows の Visual Studio のジェネレーターで必要で，ほかでは付けても同じ） |
| Visual Studio でフォルダーを開く | **Test > Run CTests for softprac1_answers**，または **Test Explorer** |
| VS Code | **Testing** ビュー，または **Command Palette** の **CMake: Run Tests** |

- 失敗したテストは，期待する出力と実際の出力を並べて表示します（`--output-on-failure`）。
- 雛形のままでは，そのプロジェクトのテストはほとんど失敗します。ただし，何もしないのが正しいケース（入力が空・引数が足りないときに何も表示しない，既にあるファイルをそのまま残すなど）は雛形でも通ります。全部が通れば，演習ページの表示例どおりに書けています。
- 標準エラー出力（エラーメッセージ）の文面は比べません（終了コードは比べます）。メッセージは `main` の解答と見比べます。
- 関数だけを書くファイル（`main` を持たない `.c`）は，空のままだと「空の翻訳単位」の警告が出ます（MSVC は C4206）。中身を書けば消えます。
- 空のプロジェクトやコマンドで作った実行ファイルは，入力を与えて出力をファイルに保存し，`diff`（Windows は `fc`）で `tests/<ケース>.out` と比べます。

  ```sh
  cd week07/Echo
  gcc -std=c17 -Wall -Wextra -Wpedantic *.c -o a.out -lm
  ./a.out < tests/two_lines.in | diff - tests/two_lines.out   # 何も表示されなければ一致
  ```

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
- 第12回の `CalcApp`（ライブラリを使う）と第13回の `DynamicVectorFail`（`DynamicVector` のソースも使う）は，`main` ブランチのそれぞれの回の README のコマンドでビルドします（CMake を使う方法 3・4 ならそのままビルドできます）。
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
- 引数を使う課題は，**Startup Item** で `week10 ReadText  [input.txt]` のような `weekNN 名前  [引数]` の項目を選びます（授業の **Command Arguments** に当たります）。
  引数は各回の README の表の「実行に使うもの」と同じで，作業ディレクトリは `Echo.exe` などの項目と同じく実行ファイルのフォルダです。
  ほかの引数で試すときは，その項目を選んだ状態で **Debug > Debug and Launch Settings for \<項目\>** を開き，`"args"` を書き換えます（`.vs/launch.vs.json` に保存されます。試し終わったら `git restore .vs/launch.vs.json` で戻します）。

- プロジェクトフォルダのデータファイルを書き換えたり足したりしたときは，次のビルドでコピーし直されます（実行ファイルのフォルダで直接書き換えた同名のファイルは上書きされます）。プログラムが書き出したファイルは実行ファイルのフォルダに残り，プロジェクトフォルダには戻りません。

### 4. VS Code で使う（Windows / macOS / Linux）

拡張機能 **C/C++**（`ms-vscode.cpptools`）と **CMake Tools**（`ms-vscode.cmake-tools`）を入れます。

1. **File > Open Folder** でリポジトリのフォルダを開きます。
2. CMake Tools がキット（コンパイラ）を尋ねるので，Windows は **Visual Studio Community 2026 Release - amd64** などの MSVC，macOS / Linux は Clang か GCC を選びます（後から変えるときは **Command Palette**（Ctrl+Shift+P）の **CMake: Select a Kit**）。
3. **Command Palette** の **CMake: Set Launch/Debug Target** で実行したいプロジェクトを選び，**CMake: Run Without Debugging**（Ctrl+Shift+F5）で実行，**CMake: Debug**（Shift+F5）でデバッグ実行します。
   すべてのビルドは **CMake: Build**（F7）です。

- 実行ファイルとデータファイルの場所，作業ディレクトリは 3 と同じです（ビルド先は `build/`）。
- 引数を使う課題は，**File > Preferences > Settings** の **Workspace** タブで `cmake.debugConfig` を検索し，**Edit in settings.json** で次のように書きます（`.vscode/settings.json` に保存されます。このブランチには含めていません）。
  `console` は，デバッグ実行でもキーボードから入力できるようにする設定です（入力を読む課題で使う）。

  ```json
  { "cmake.debugConfig": { "args": [ "input.txt" ], "console": "integratedTerminal" } }
  ```

  この `args` はどのプロジェクトを実行しても渡されるので，その課題が終わったら消します。

- リダイレクト（`<`）を使う課題（第7回）は，**Terminal > New Terminal** で 1 の方法を使います。

## よくあるトラブル

| 症状 | 対処 |
| --- | --- |
| Visual Studio の **Startup Item** にプロジェクトが出ない | **Project > Delete Cache and Reconfigure** |
| VS Code で `cl.exe` が見つからない | キットに MSVC を選ぶ。Visual Studio（または Build Tools for Visual Studio）の C++ ワークロードが入っているか確認 |
| `input.txt` が開けない | 作業ディレクトリに `input.txt` があるか確認（1 はプロジェクトフォルダで実行，2 は `.vcxproj` のフォルダにコピー，3・4 はビルドし直す） |
| 日本語が文字化けする | プログラムの表示は ASCII にしています。ソースのコメントが化ける場合はファイルを BOM 付き UTF-8 で保存し直す |
| 入力の終わり（EOF）の入れ方 | Windows は行頭で **Ctrl+Z → Enter**，macOS / Linux は **Ctrl+D** |
