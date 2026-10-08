# 第12回 演習 解答・解説（コンパイル：分割コンパイルとライブラリ）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex12.html>（[ソース](https://github.com/t-yokoga/softprac1/blob/main/docs/ex12.md)）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec12.html>（例題 [`sample/12/`](https://github.com/t-yokoga/softprac1/tree/main/docs/sample/12)：`calc.h`・`calc.c`・`main.c`，`vector.h`・`matrix.h`・`vector.c`・`matrix.c`・`vector_main.c`）
- 今回の範囲: 前処理・コンパイル・リンク，翻訳単位，宣言と定義，ヘッダ（インクルードガード `PL1_..._H`），1 プロジェクトに複数の `.c`，
  静的ライブラリ（`.lib`）と動的ライブラリ（`.dll`），ファイルスコープの `static`／`extern`，標準ライブラリ（`math.h`・`ctype.h`・`float.h`・`limits.h`・
  `string.h`・`assert.h`・`stdlib.h` の `strtol`・`qsort`・`rand`・`srand`）。第10回のコマンドライン引数と `strtol` による検査，第8回のポインタで結果を返す関数も使う。

## プロジェクト一覧

| 課題 | プロジェクト | ソース | テスト |
| --- | --- | --- | --- |
| 課題1〜3 | `SplitCalc` | [main.c](SplitCalc/main.c)，[calc.c](SplitCalc/calc.c)，[calc.h](SplitCalc/calc.h)，[CMakeLists.txt](SplitCalc/CMakeLists.txt) | 7（[basic](SplitCalc/tests/basic.out)：本体の 4 行，[書き換え版](SplitCalc/variants/tests/) 6：課題1 の講義版 `lecture`，検証表の `sub_0_0`・`sub_2_5`・`div_m6_2`・`div_0_2`・`div_6_0`） |
| 課題4 | `VectorCalc` | [vector_main.c](VectorCalc/vector_main.c)，[vector.c](VectorCalc/vector.c)，[matrix.c](VectorCalc/matrix.c)，[vector.h](VectorCalc/vector.h)，[matrix.h](VectorCalc/matrix.h)，[CMakeLists.txt](VectorCalc/CMakeLists.txt) | 5（[basic](VectorCalc/tests/basic.out)：講義の 4 行，[書き換え版](VectorCalc/variants/tests/) 4：手順3〜5 の `identity`・`alpha0`・`unchanged`，直接の include を外した `no_direct_include`） |
| 発展1（ライブラリ側） | `CalcLib` | [calc.c](CalcLib/calc.c)，[calc.h](CalcLib/calc.h)，[CMakeLists.txt](CalcLib/CMakeLists.txt) | ―（静的ライブラリなので実行しない） |
| 発展1（アプリ側） | `CalcApp` | [main.c](CalcApp/main.c)，[CMakeLists.txt](CalcApp/CMakeLists.txt) | 2（[basic](CalcApp/tests/basic.out)，講義の 2 関数だけの版 [lecture](CalcApp/variants/tests/lecture.out)） |
| 発展2 | `SortModule` | [sort_main.c](SortModule/sort_main.c)，[intlib.c](SortModule/intlib.c)，[intlib.h](SortModule/intlib.h)，[CMakeLists.txt](SortModule/CMakeLists.txt)，[run.args](SortModule/run.args)（`5`） | 18（[tests/](SortModule/tests/) の 17 ＋ [INT_MAX/INT_MIN 版](SortModule/variants/tests/) 1） |
| 発展3 | `LibraryCheck` | [library_check.c](LibraryCheck/library_check.c)，[CMakeLists.txt](LibraryCheck/CMakeLists.txt) | 2（[basic](LibraryCheck/tests/basic.out)，[NDEBUG 版](LibraryCheck/variants/tests/ndebug.out)：偽の `assert` に変えても終了コード 0） |
| 課題3・4 のエラー版 | `_BuildErrors`（ビルドしない） | [split/](_BuildErrors/split/)（課題1 の講義どおりの 3 ファイルと，エラーの 3 版），[noguard/](_BuildErrors/noguard/)（ガードを外した `vector.h` と組み合わせる一式），[noinclude/](_BuildErrors/noinclude/)（`#include "vector.h"` を外した `matrix.h` と，それだけを読む `vector_main.c`） | ― |

合計 34 テスト（GCC＋ASan/UBSan，Clang ともに警告 0・全成功）。

- フォルダ名＝Visual Studio のプロジェクト名＝実行ファイル名。フォルダ内の `.c` はすべて 1 つの実行ファイルにリンクされる（Visual Studio で「ソース ファイル」に登録したのと同じ）。
  `main` を持つのは `SplitCalc/main.c`・`VectorCalc/vector_main.c`・`CalcApp/main.c`・`SortModule/sort_main.c`・`LibraryCheck/library_check.c` の各 1 つだけ。
- `SplitCalc` の本体（フォルダのソース）は，演習ページの期待する表示（課題2 の「5.0 から 2.0 を引いた 3.0 を表示」と `calc_divide` の成功例）を出す**課題2 の関数を追加した版**。
  課題1 の講義どおりの版（加算・乗算だけ）と課題2 の検証表の残りの行は，[CMakeLists.txt](SplitCalc/CMakeLists.txt) の `softprac_add_variant` で書き換えた版としてテストする（講義どおりの 3 ファイルは [_BuildErrors/split/](_BuildErrors/split/) にもある）。
- `CalcLib` と `CalcApp` は同じ名前の `calc.h`・`calc.c`・`main.c` を `SplitCalc` とは別のフォルダに持つ（演習の「元の `SplitCalc` は残し，別のソリューションで試す」に合わせた）。
- `SplitCalc`・`VectorCalc`・`SortModule`・`LibraryCheck` の `CMakeLists.txt` は，ソースの登録は自動の規則と同じで，演習ページの「書き換えて確かめる」版（`softprac_add_variant`）を登録するためだけに置いている。
  `CalcApp` の `CMakeLists.txt` は，それに加えて `CalcLib` の参照（`target_link_libraries`）と追加のインクルード ディレクトリ（`target_include_directories`）のために必要（発展1）。
  フォルダのソース（本体）は演習ページの期待する表示を出す版で，書き換えは CMake がビルド時に行う（学生と同じ書き換えをした別の実行ファイルとしてテストする。生成したソースの先頭コメントもその版の説明に置き換える）。

---

## 課題1　分割ビルド（`SplitCalc` / `main.c`・`calc.c`・`calc.h`）

**要点**: 1 つの実行ファイルを，宣言を書いたヘッダ `calc.h`，実装 `calc.c`，利用側 `main.c` に分ける。
`main.c` と `calc.c` は**別々の翻訳単位**としてコンパイルされ（`main.obj`・`calc.obj`），リンカが `add` の呼び出しと定義を結び付けて `.exe` を作る。

講義どおりの 3 ファイル（[_BuildErrors/split/](_BuildErrors/split/) の `calc.h`・`calc.c`・`main.c`）:

```c
/* calc.h */                         /* calc.c */                        /* main.c */
#ifndef PL1_CALC_H                   #include "calc.h"                   #include <stdio.h>
#define PL1_CALC_H                   double add(double a, double b)      #include "calc.h"
double add(double a, double b);      {                                   int main(void)
double multiply(double a, double b);     return a + b;                   {
#endif                               }                                       printf("add=%.1f\n", add(1.5, 2.0));
                                     double multiply(double a, double b)     printf("multiply=%.1f\n", multiply(1.5, 2.0));
                                     {                                       return 0;
                                         return a * b;                   }
                                     }
```

### 手順1・4　予測と実行結果

`main.c` だけを見ると，`add` は `double` 2 つを受け取り `double` を返す（`calc.h` の宣言から分かる）。名前から 1.5＋2.0＝3.5，1.5×2.0＝3.0 と予測し，`%.1f` なので小数 1 桁で表示される。
実装を見なくても型は分かるが，**値が正しいかは実装次第**であり，「名前どおりの計算をしている」というのは予測であることに注意させる。

実行結果（講義の 3 ファイル。予測どおり。`SplitCalc` の本体から課題2 で加えた行を除いた版 `lecture` としてテストしている）:

```text
add=3.5
multiply=3.0
```

### 手順2　宣言と定義の対応

| `calc.h` の宣言（末尾は `;`） | `calc.c` の定義（本体がある） | 呼び出し（`main.c`） |
| --- | --- | --- |
| `double add(double a, double b);` | `double add(double a, double b) { return a + b; }` | `add(1.5, 2.0)` |
| `double multiply(double a, double b);` | `double multiply(double a, double b) { return a * b; }` | `multiply(1.5, 2.0)` |
| （課題2）`double subtract(double a, double b);` | `double subtract(double a, double b) { return a - b; }` | `subtract(5.0, 2.0)` |
| （課題2）`int calc_divide(double a, double b, double *out);` | `int calc_divide(double a, double b, double *out) { ... }` | `calc_divide(6.0, 2.0, &q)` |

戻り値の型・関数名・引数の型と個数が一致していることを確かめる（引数名は一致しなくてよい）。`calc.c` も `calc.h` を読むので，一致していなければ `calc.c` のコンパイルで分かる（課題3）。

### 手順3　ビルドの警告とエラー

このリポジトリの GCC/Clang（`-Wall -Wextra -Wpedantic -Werror`）で**警告 0・エラー 0** を確かめた。Visual Studio（C17・`/W4`・`/TC`）で警告になる書き方（C4996 になる関数，可変長配列など）も使っていない（MSVC での実行はこの環境では確かめていない）。
警告が出た場合は，拡張子が `.cpp` になっていないか（C++ としてコンパイルされる），`calc.h` の保存場所が `main.c` と同じ実フォルダか，を確認させる。

### 手順5　出力ウィンドウの比較（`calc.c` だけ保存し直した場合と，何も変えない場合）

Visual Studio 2022（日本語）での表示の例（版・言語設定・タイムスタンプで文言や行は変わる）:

```text
（calc.c だけを保存し直してビルド）
1>------ ビルド開始: プロジェクト: SplitCalc, 構成: Debug x64 ------
1>calc.c
1>SplitCalc.vcxproj -> C:\...\PL1\week12\SplitCalc\x64\Debug\SplitCalc.exe
========== ビルド: 1 正常終了、0 失敗、0 更新不要、0 スキップ ==========

（何も変えずにもう一度ビルド）
========== ビルド: 0 正常終了、0 失敗、1 更新不要、0 スキップ ==========

（何も変えずに「リビルド」）
1>------ すべてのリビルド開始: プロジェクト: SplitCalc, 構成: Debug x64 ------
1>calc.c
1>main.c
1>SplitCalc.vcxproj -> C:\...\PL1\week12\SplitCalc\x64\Debug\SplitCalc.exe
========== すべてリビルド: 1 正常終了、0 失敗、0 スキップ ==========
```

このリポジトリの CMake（Ninja）で同じ操作をした実際の記録（各コマンドの最初に出る `[0/2] Re-checking globbed directories...` の行は省略）:

```text
$ touch week12/SplitCalc/calc.c && cmake --build $B --target SplitCalc     ← calc.c だけ更新
[1/2] Building C object projects/week12/SplitCalc/CMakeFiles/SplitCalc.dir/calc.c.o
[2/2] Linking C executable bin/week12/SplitCalc
$ cmake --build $B --target SplitCalc                                      ← 何も変えずにビルド
ninja: no work to do.
$ cmake --build $B --target SplitCalc --clean-first                        ← リビルド
[1/1] Cleaning all built files...
Cleaning... 57 files.
[1/3] Building C object projects/week12/SplitCalc/CMakeFiles/SplitCalc.dir/calc.c.o
[2/3] Building C object projects/week12/SplitCalc/CMakeFiles/SplitCalc.dir/main.c.o
[3/3] Linking C executable bin/week12/SplitCalc
$ touch week12/SplitCalc/calc.h && cmake --build $B --target SplitCalc     ← （参考）ヘッダを更新
[1/3] Building C object projects/week12/SplitCalc/CMakeFiles/SplitCalc.dir/calc.c.o
[2/3] Building C object projects/week12/SplitCalc/CMakeFiles/SplitCalc.dir/main.c.o
[3/3] Linking C executable bin/week12/SplitCalc
```

`--clean-first` は，CMake（Ninja）では指定したターゲットだけでなく**ビルドフォルダのすべての生成物を消してから**作り直す（上の `Cleaning... 57 files.` は week12 の全プロジェクトの分）。
Visual Studio の「リビルド」（プロジェクトを右クリックした場合はそのプロジェクトだけ）より範囲が広いが，`SplitCalc` についての動き（全 `.c` を再コンパイルしてリンク）は同じ。

観察の要点: `calc.c` だけが新しくなると**`calc.c` の再コンパイルとリンク**だけが行われ，`main.c` はコンパイルされない（`main.obj` は前のものを使う）。
何も変えなければビルドは「更新不要」で何もしない。リビルドはすべての `.c` をコンパイルし直してリンクする。`calc.h` を変えると，それを読む `main.c` と `calc.c` の両方が再コンパイルされる（講義 1.2）。

### 考察

- **なぜ `main.c` に `add` の本体がなくてもコンパイルできるか**: コンパイルに必要なのは `add` の**宣言**（名前・引数の型・戻り値の型）だけだから。`calc.h` の宣言で，`main.c` のコンパイラは `double` 2 つを渡して `double` を受け取るコードを作れる。
  `main.obj` には「`add` を呼びたい」という未解決の参照が残り，本体（定義）との結び付けは**リンク**で `calc.obj` を使って行われる。
- **`calc.h` を取り込んだだけで `calc.c` もビルド対象になるか**: ならない。`#include "calc.h"` は前処理でヘッダの文字を取り込むだけで，`calc.c` を探してコンパイルしたりリンクしたりはしない（ヘッダ名と `.c` 名が同じなのは人間のための慣習にすぎない）。
  `calc.c` をプロジェクトの「ソース ファイル」に追加しないと，課題3のようにリンクエラー（`LNK2019`）になる。
- **`.obj` と `.exe` は同じものか**: 違う。`.obj`（オブジェクト）は 1 つの翻訳単位をコンパイルした機械語と名前・未解決の参照の情報で，単独では実行できない。
  `.exe` はリンカが `main.obj`・`calc.obj` と標準ライブラリを結び付けて参照をすべて解決した実行ファイル。Visual Studio の既定では `.obj` は `<プロジェクトフォルダ>\x64\Debug\`（例 `SplitCalc\x64\Debug\main.obj`），`.exe` は `<ソリューションフォルダ>\x64\Debug\`（例 `SplitCalc.exe`）にできる
  （このリポジトリの CMake では `projects/week12/SplitCalc/CMakeFiles/SplitCalc.dir/calc.c.o`・`main.c.o` と `bin/week12/SplitCalc`）。
- **`main.c` と `calc.c` を別々の実行アプリ用プロジェクトにしてよいか**: いけない。プロジェクト＝1 つの実行ファイルなので，`calc.c` だけのプロジェクトは `main` がなくリンクに失敗し（`LNK2019: 未解決の外部シンボル main`／`LNK1120`），
  `main.c` だけのプロジェクトは `add` の定義がなく `LNK2019` になる。同じプロジェクトに入れるか，発展1のように `calc.c` を**静的ライブラリ**のプロジェクトにして参照する。

### 採点のポイント・よくある誤り

- `main.c` に `#include "calc.c"` と書いて動かしている（講義 2 で禁止。`calc.c` もプロジェクトに入れると `add` が二重定義になる）。
- `calc.c` をフォルダにコピーしただけでプロジェクトに追加していない（ソリューションエクスプローラーに出ない → `LNK2019`）。
- 拡張子が `main.c.cpp`・`calc.h.txt` になっている，`main` が 2 つあるプロジェクトになっている（`LNK2005 main`）。
- 手順5で「何も表示されなかった」だけを書いている → 「更新不要」の表示と，どのファイルがコンパイルされたかを記録させる。
- 考察で「ヘッダに本体がある」「include でリンクされる」と答えている → 宣言と定義，前処理とリンクを区別させる。

---

## 課題2　関数を追加する（`SplitCalc` の本体）

**要点**: 関数を 1 つ増やすときは**宣言（`calc.h`）・定義（`calc.c`）・呼び出し（`main.c`）の 3 か所**を対応させる。
`calc_divide` は第8回の「戻り値で成功・失敗，ポインタで結果」を別ファイルの関数にしたもので，`calc.h` のコメントが利用者との**契約**になる。

### 変更した 3 か所

1. 宣言 — [calc.h](SplitCalc/calc.h)

   ```c
   double subtract(double a, double b);
   /* b が 0.0 なら 0 を返し，*out を変更しない．それ以外は a / b を *out に保存して 1 を返す．
      out は有効な double を指すこと（呼び出し側の条件） */
   int calc_divide(double a, double b, double *out);
   ```

2. 定義 — [calc.c](SplitCalc/calc.c)

   ```c
   double subtract(double a, double b)
   {
       return a - b;
   }
   int calc_divide(double a, double b, double *out)
   {
       if (b == 0.0) {
           return 0;  /* 割る前に検査する．失敗時は *out に書き込まない */
       }
       *out = a / b;
       return 1;
   }
   ```

3. 呼び出し — [main.c](SplitCalc/main.c)（`q` を 99.0 にしてから呼ぶので，失敗時に保存先が変わらないことが表示で分かる）

   ```c
   printf("subtract=%.1f\n", subtract(5.0, 2.0));
   double q = 99.0;  /* 失敗したときに保存先が変わらないことを確かめるための初期値 */
   int ok = calc_divide(6.0, 2.0, &q);
   printf("calc_divide(6.0, 2.0): ok=%d q=%.1f\n", ok, q);
   ```

### 実行結果（`SplitCalc` の本体）

```text
add=3.5
multiply=3.0
subtract=3.0
calc_divide(6.0, 2.0): ok=1 q=3.0
```

検証表の残りの行は，学生と同じように呼び出しの引数を書き換えた版で確かめた（[CMakeLists.txt](SplitCalc/CMakeLists.txt) の `softprac_add_variant`。
`subtract(5.0, 2.0)`，または `calc_divide(6.0, 2.0, &q)` と表示の `"calc_divide(6.0, 2.0): "` の組を書き換える）。各版の最後の 1 行（前の行は本体と同じ）:

| 版（テスト） | 書き換え | 実際の表示（変わった行） |
| --- | --- | --- |
| `sub_0_0` | `subtract(0.0, 0.0)` | `subtract=0.0` |
| `sub_2_5` | `subtract(2.0, 5.0)` | `subtract=-3.0` |
| `div_m6_2` | `calc_divide(-6.0, 2.0, &q)` | `calc_divide(-6.0, 2.0): ok=1 q=-3.0` |
| `div_0_2` | `calc_divide(0.0, 2.0, &q)` | `calc_divide(0.0, 2.0): ok=1 q=0.0` |
| `div_6_0` | `calc_divide(6.0, 0.0, &q)` | `calc_divide(6.0, 0.0): ok=0 q=99.0`（失敗。`q` は初期値のまま） |

### 検証表（解答）

| 操作 | 入力 | 期待する結果 |
| --- | --- | --- |
| `subtract` | 5，2 | 3.0 を返す（表示 `subtract=3.0`） |
| `subtract` | 0，0 | 0.0 を返す |
| `subtract` | 2，5 | −3.0 を返す（引数の順序が意味を持つ：`a - b`） |
| `calc_divide` | 6，2 | 1（成功）を返し，`*out` に 3.0 を保存 |
| `calc_divide` | −6，2 | 1（成功）を返し，`*out` に −3.0 を保存 |
| `calc_divide` | 0，2 | 1（成功）を返し，`*out` に 0.0 を保存（被除数 0 は正常） |
| `calc_divide` | 6，0 | 0（失敗）を返し，`*out` は変更しない（呼び出し前の 99.0 のまま） |

- 宣言だけを追加すると，`main.c` はコンパイルできるが**リンクで `subtract` が未解決**（`LNK2019`）。本体だけを追加すると，`main.c` からは宣言が見えず，未宣言の関数の呼び出しになる
  （MSVC は `warning C4013: 'subtract' undefined; assuming extern returning int`（文面は例），GCC 13 は `warning: implicit declaration of function 'subtract' [-Wimplicit-function-declaration]`。
  C99 以降の規格では誤りで，GCC 14 以降は既定でエラー，このリポジトリの `-Werror` でもエラー）。
  警告を無視してビルドすると `int` を返す関数と見なされ，`double` の戻り値を正しく受け取れない（未定義動作）。
- 0.0 での割り算の判定は**割る前**に行う。`b == 0.0` は −0.0 にも真になる。この課題では小さな有限値だけを扱うので，オーバーフローなどは対象外（仕様どおり）。

### 採点のポイント・よくある誤り

- 関数名を `div` にした（`stdlib.h` の `div` と衝突。`stdlib.h` を読むファイルでは型の不一致エラー）。
- 失敗時に `*out = 0.0;` などと書き込んでいる → 仕様違反（「保存先の値を変更しない」）。保存先の初期値を 0 以外にして確かめているかを見る。
- `a / b` を計算してから `b` を調べる，`*out = a / b;` の後に `if (b == 0.0)`。浮動小数点の 0 除算は C では未定義になり得る（MSVC では inf になることが多いが当てにしない）。
- 成功・失敗の値を逆（成功 0）にした，戻り値を `double` にした → 仕様（成功 1，失敗 0）と呼び出し側の `if` の書き方を確認。
- `calc.h` に宣言を足さず `main.c` の先頭に `double subtract(double, double);` と手書きした → 共通のヘッダを両方から読む形にする（講義 2.2）。
- 呼び出し側で `calc_divide(6.0, 0.0, NULL)` のように無効なポインタを渡す（`out` が有効な `double` を指すのは呼び出し側の条件）。

---

## 課題3　リンクエラーを調べる（`SplitCalc` と `_BuildErrors/split/`）

**要点**: ビルドの失敗を**前処理・コンパイル・リンク**のどの段階かに分け，最初の原因に近い診断を読む。ヘッダの検索先を直す場面（`C1083`）と，リンクする実装を確かめる場面（`LNK2019`・`LNK2005`）を区別する。

エラーになる版は [_BuildErrors/split/](_BuildErrors/split/) に置いた（`_` で始まるフォルダはビルドしない）。
**MSVC の診断は文面の例**（版・言語設定で変わる。GCC/Clang の診断は実際に実行して得た。`$` の行がコマンド）。

### `calc.c` を「ビルドから除外」した場合

`calc.c` のプロパティ → 構成プロパティ → 全般 →「ビルドから除外」を「はい」にしてリビルドすると，`main.c` のコンパイルは成功し，**リンク**で失敗する。

MSVC（x64）の診断の例（日本語版の文面は「未解決の外部シンボル add が関数 main で参照されました」）:

```text
1>main.obj : error LNK2019: unresolved external symbol add referenced in function main
1>main.obj : error LNK2019: unresolved external symbol multiply referenced in function main
1>main.obj : error LNK2019: unresolved external symbol subtract referenced in function main
1>main.obj : error LNK2019: unresolved external symbol calc_divide referenced in function main
1>C:\...\x64\Debug\SplitCalc.exe : fatal error LNK1120: 4 unresolved externals
```

（課題1の 3 ファイルの版なら `add` と `multiply` の 2 つで `LNK1120: 2 unresolved externals`。x86（Win32）構成では名前が `_add`，`_main` のように表示される。）

GCC（`calc.c` を渡さないビルド。`SplitCalc` の本体）:

```text
$ gcc -std=c17 -Wall -Wextra -Wpedantic main.c
/usr/bin/ld: <一時ファイル>.o: in function `main':
main.c:(.text+0x34): undefined reference to `add'
/usr/bin/ld: main.c:(.text+0x6f): undefined reference to `multiply'
/usr/bin/ld: main.c:(.text+0xaa): undefined reference to `subtract'
/usr/bin/ld: main.c:(.text+0xf9): undefined reference to `calc_divide'
collect2: error: ld returned 1 exit status
```

`gcc -c main.c` だけなら `main.o` は正常にできる（コンパイルは成功している）ことも確かめた。「ビルドから除外」を「いいえ」に戻してリビルドすると成功し，元の 4 行（本体の表示）に戻る。
ビルド失敗時に「最後に成功したビルドを実行しますか」と出ても**実行しない**（古い `.exe` を動かしても修正の確認にならない）。

### エラーの比較（表の解答）

| 変更 | 予想する段階 | 元に戻す操作 |
| --- | --- | --- |
| `main.c` の `include` を存在しない `calc_missing.h` にする | **前処理**（`#include` のファイルが見つからない） | `calc.h` へ戻す |
| `calc.c` の `add` の戻り値型だけを `int` にする | **コンパイル**（`calc.c` が読む `calc.h` の宣言と定義の型が食い違う） | `double` へ戻す |
| `calc.c` をビルドから除外する | **リンク**（`add` などの定義がどの `.obj` にもない） | 除外を「いいえ」へ戻す |
| `add` の本体を `main.c` にもコピーする | **リンク**（`add` の定義が `main.obj` と `calc.obj` に 1 つずつある） | コピーした本体だけを除く |

### ビルド記録（解答例）

| # | 変更箇所 | 予想 | 実際の段階 | 診断の要点（MSVC は文面の例 / GCC は実際の出力） | 復旧後の成功 |
| --- | --- | --- | --- | --- | --- |
| 1 | [main_missing_header.c](_BuildErrors/split/main_missing_header.c) 3 行目 `#include "calc_missing.h"` | 前処理 | 前処理（`main.c` のコンパイルの最初で停止） | MSVC `fatal error C1083: Cannot open include file: 'calc_missing.h': No such file or directory`（インクルード ファイルを開けません）／ GCC `fatal error: calc_missing.h: No such file or directory` | `calc.h` に戻してビルド成功，`add=3.5`・`multiply=3.0` |
| 2 | [calc_int_add.c](_BuildErrors/split/calc_int_add.c) 3 行目 `int add(double a, double b)` | コンパイル | コンパイル（`calc.c`） | MSVC `error C2371: 'add': redefinition; different basic types`（再定義されています。異なる基本型です）＋ `/W4` で `warning C4244: 'return': conversion from 'double' to 'int'` ／ GCC `error: conflicting types for 'add'; have 'int(double,  double)'` と `note: previous declaration of 'add' with type 'double(double,  double)'`（calc.h:4） | `double` に戻して成功，元の 2 行 |
| 3 | `calc.c` を「ビルドから除外」 | リンク | リンク | MSVC `LNK2019: unresolved external symbol add referenced in function main` と `LNK1120` ／ GCC(ld) `undefined reference to 'add'` | 「いいえ」に戻してリビルド成功，元の 2 行 |
| 4 | [main_dup_add.c](_BuildErrors/split/main_dup_add.c) に `add` の本体をコピー | リンク | リンク | MSVC `calc.obj : error LNK2005: add already defined in main.obj`（既に main.obj で定義されています）と `fatal error LNK1169: one or more multiply defined symbols found` ／ GCC(ld) `multiple definition of 'add'; ...main_dup_add.c: first defined here` | コピーした本体を削除して成功，元の 2 行 |

GCC で実際に出た診断（[_BuildErrors/split/](_BuildErrors/split/) で実行）:

```text
$ gcc -std=c17 -Wall -Wextra -Wpedantic main_missing_header.c calc.c
main_missing_header.c:3:10: fatal error: calc_missing.h: No such file or directory
    3 | #include "calc_missing.h"
      |          ^~~~~~~~~~~~~~~~
compilation terminated.

$ gcc -std=c17 -Wall -Wextra -Wpedantic main.c calc_int_add.c
calc_int_add.c:3:5: error: conflicting types for 'add'; have 'int(double,  double)'
    3 | int add(double a, double b)
      |     ^~~
In file included from calc_int_add.c:2:
calc.h:4:8: note: previous declaration of 'add' with type 'double(double,  double)'
    4 | double add(double a, double b);
      |        ^~~

$ gcc -std=c17 -Wall -Wextra -Wpedantic main.c
/usr/bin/ld: <一時ファイル>.o: in function `main':
main.c:(.text+0x21): undefined reference to `add'
/usr/bin/ld: main.c:(.text+0x5c): undefined reference to `multiply'
collect2: error: ld returned 1 exit status

$ gcc -std=c17 -Wall -Wextra -Wpedantic main_dup_add.c calc.c
/usr/bin/ld: <一時ファイル>.o: in function `add':
calc.c:(.text+0x0): multiple definition of `add'; <一時ファイル>.o:main_dup_add.c:(.text+0x0): first defined here
collect2: error: ld returned 1 exit status
```

Clang 18 も同じ段階で失敗する（前処理 `fatal error: 'calc_missing.h' file not found`，コンパイル `error: conflicting types for 'add'` と `note: previous declaration is here`，
リンクの 2 つは同じ `ld` のメッセージに `clang: error: linker command failed with exit code 1` が続く）。

### 診断の違いから分かること

- **`C1083`（前処理）** → ヘッダの**検索先**の問題。ファイル名の綴り・拡張子（`calc.h.txt`）・保存した実フォルダ・「追加のインクルード ディレクトリ」を確認する。`.c` をプロジェクトに足しても直らない。
- **`C2371` など（コンパイル）** → 宣言と定義（またはヘッダと呼び出し）の**型**の不一致。どちらが正しい契約かを決め，ヘッダに合わせる。
- **`LNK2019`（リンク）** → 宣言は見えているが**定義がリンクされていない**。実装の `.c` がプロジェクトに入っていてビルド対象か，ライブラリが参照・リンクされているか，名前の綴りを確認する。インクルードパスを直しても直らない。
- **`LNK2005`（リンク）** → 定義が**2 か所以上**。ヘッダや `main.c` に関数本体を書いていないか，`#include "calc.c"` をしていないか，`main` が 2 つないかを確認する。インクルードガードでは直らない。

### 補足：`calc.c` が `calc.h` を読まないと，型の不一致を見逃す

講義 3.1 のとおり，実装側も自分のヘッダを読むのは型の不一致をコンパイルで見つけるため。記録 2 の `calc_int_add.c` から `#include "calc.h"` を消すと，**リンクエラーは出ずにビルドが通る**（リンカは C の関数の型を照合しない）。GCC/Clang は警告もなし，MSVC `/W4` では型の不一致ではなく `C4244`（`return` での `double` → `int` の変換）だけが出る（例）。
GCC で試すと `add=3.5` と表示されたが，これは呼び出し側が `double` を受け取る場所にたまたま計算途中の値が残っていただけで，**未定義動作**である（最適化や環境で結果が変わる）。「動いたから正しい」と判断させないこと。

### 採点のポイント・よくある誤り

- 4 つを同時に変更して，どの変更がどの診断を出したか分からない記録になっている（1 つずつ試し，毎回元に戻して成功を確認させる）。
- 最初の 1 行ではなく，後続の大量のエラーや `LNK1120` だけを記録している（`LNK1120`／`LNK1169` は件数のまとめ。原因は直前の `LNK2019`／`LNK2005`）。
- 記録 2 を「リンク」と予想・記録している → `calc.c` が `calc.h` を読んでいるのでコンパイルで分かる。逆に読んでいなければ見逃される（上の補足）。
- 記録 4 を「インクルードガードで防げる」と書いている → ガードは同じ翻訳単位の中の再取り込みを防ぐだけ（確認問題2）。
- 復旧後に「エラーが消えた」だけで，元の出力に戻ったことを書いていない。

---

## 課題4　ベクトルと行列を分割する（`VectorCalc` / 5 ファイル）

**要点**: 構造体の型（`Vector`・`Matrix`）を含むモジュールの分割。`matrix.h` は `Vector` を使うので**自分で `vector.h` を読む**。
`vector_main.c` には `vector.h` が 2 経路で入るが，インクルードガードで同じ翻訳単位に 2 回展開されるのを防ぐ。

ソースは講義 7 の 5 ファイルそのまま（先頭にコメントだけ追加）。手順3〜5 は演習ページどおり `vector_main.c` を書き換えて確かめるもので，
[CMakeLists.txt](VectorCalc/CMakeLists.txt) の `softprac_add_variant` で同じ書き換えをした 3 つの版（`identity`・`alpha0`・`unchanged`）をビルド・テストしている。
ソースとして登録するのは `vector_main.c`・`vector.c`・`matrix.c` の 3 つで，`SplitCalc` の `main.c` は入れない（入れると `main` が 2 つで `LNK2005`）。

### 手順1　手計算

- `2x + y = (2×1+3, 2×2+4) = (5, 8)`
- `Ax = (1×1 + (−1)×2, (−1)×1 + 1×2) = (−1, 1)` なので `2Ax + y = (−2+3, 2+4) = (1, 6)`
- 手順3: `A = I`（単位行列）なら `Ix = x` なので `2Ix + y = 2x + y = (5, 8)`
- 手順4: `alpha = 0`，`beta = 1` なら `0·Ax + 1·y = y = (3, 4)`
- 手順5: `axpy`・`gemv` は値渡しで新しい `Vector` を返すので，呼び出し後も `x = (1, 2)`，`y = (3, 4)`

### 実行結果

講義どおりの `vector_main.c`（手順1・2）:

```text
[1.0 -1.0]
[-1.0 1.0]
(5.0, 8.0)
(1.0, 6.0)
```

講義の出力と一致し，手計算 `2x+y = (5, 8)`・`2Ax+y = (1, 6)` とも一致する（手順2）。

手順3: `Matrix a = {{1.0, -1.0, -1.0, 1.0}};` を `Matrix a = {{1.0, 0.0, 0.0, 1.0}};`（単位行列）に変えた版。3 行目（`axpy(2.0, x, y)` = 2x+y）と 4 行目（`gemv(2.0, a, x, 1.0, y)` = 2Ax+y）が一致する:

```text
[1.0 0.0]
[0.0 1.0]
(5.0, 8.0)
(5.0, 8.0)
```

手順4: `print_vector(gemv(2.0, a, x, 1.0, y));` を `print_vector(gemv(0.0, a, x, 1.0, y));`（`alpha` を 0，`beta` は 1 のまま）に変えた版。4 行目が `y` = (3, 4) になる:

```text
[1.0 -1.0]
[-1.0 1.0]
(5.0, 8.0)
(3.0, 4.0)
```

手順5: `return 0;` の前に `print_vector(x);` と `print_vector(y);` を追加した版。呼び出し後も `x` = (1, 2)，`y` = (3, 4) のまま（`axpy`・`gemv` は値渡しで新しい `Vector` を返すので，呼び出し側の変数は変わらない）:

```text
[1.0 -1.0]
[-1.0 1.0]
(5.0, 8.0)
(1.0, 6.0)
(1.0, 2.0)
(3.0, 4.0)
```

手順3・4 は 1 つずつ試して元に戻す（このリポジトリでも別々の版にしている）。学生が `identity` という別の変数を作って比べた場合なども，同じ値になれば正解。

### インクルードガードを調べる（`vector.h` のガード 3 行を外す）

[_BuildErrors/noguard/vector.h](_BuildErrors/noguard/vector.h) は `#ifndef PL1_VECTOR_H`・`#define PL1_VECTOR_H`・`#endif` だけを外した版。`vector_main.c` は `matrix.h` 経由と直接の 2 回 `vector.h` を読むので，
**同じ翻訳単位に `typedef struct { double v[2]; } Vector;` が 2 回現れ，コンパイルエラー**になる（`vector.c`・`matrix.c` は 1 回しか読まないので単独ではエラーにならない）。

```text
$ gcc -std=c17 -Wall -Wextra -Wpedantic -c noguard/vector_main.c
In file included from noguard/vector_main.c:3:
noguard/vector.h:5:3: error: conflicting types for 'Vector'; have 'struct <anonymous>'
    5 | } Vector;
      |   ^~~~~~
In file included from noguard/matrix.h:5,
                 from noguard/vector_main.c:2:
noguard/vector.h:5:3: note: previous declaration of 'Vector' with type 'Vector'
    5 | } Vector;
      |   ^~~~~~
noguard/vector.h:7:8: error: conflicting types for 'axpy'; have 'Vector(double,  Vector,  Vector)'
（以下，print_vector の宣言と gemv の引数の型の不一致が続く）
```

MSVC では `error C2371: 'Vector': redefinition; different basic types`（再定義されています。異なる基本型です）などのコンパイルエラーになる（文面は例）。
タグのない構造体は書くたびに**別の型**になるので，2 回目の `typedef` は「別の型に同じ名前を付ける」ことになる。関数のプロトタイプだけなら同じ宣言の繰り返しは許されるが，構造体の定義が重なるとエラーになる（講義 3.2）。
確認後はガードの 3 行を戻し，ビルドが成功して元の出力に戻ることを確認する。

前処理後の内容（講義 4.2 の `/P`。GCC では `gcc -E`）で `} Vector;` を数えると，ガードありは 1 回，ガードなしは 2 回だった。
ガードありの `vector_main.c` も前処理後は GCC の `-E` で 45 行（元は 15 行）に増える（ヘッダの展開と，元の行位置を表す行のため。標準ヘッダを読むファイルではさらに大きく増える）。`/P` の設定は必ず戻してリビルドさせる（`/P` のままでは `.obj` が作られない）。

### ヘッダの独立性を確認する（直接の `#include "vector.h"` を外す）

予測と結果: **ビルドは成功し，出力も変わらない**（[CMakeLists.txt](VectorCalc/CMakeLists.txt) の `softprac_add_variant` で `#include "vector.h"` の行を外した版 `no_direct_include` をビルド・テストした。講義の 4 行がそのまま出る）。
`matrix.h` が自分で `#include "vector.h"` しているので，`matrix.h` を読めば `Vector`・`axpy`・`print_vector` の宣言もそろう。

逆に `matrix.h` の `#include "vector.h"` を外し，`vector_main.c` も `matrix.h` だけを読むと，`matrix.h` の時点で `Vector` が未定義になる。
このエラー版を [_BuildErrors/noinclude/](_BuildErrors/noinclude/) に置いた（ビルドしない）。

```c
/* noinclude/matrix.h（#include "vector.h" を外した） */
#ifndef PL1_MATRIX_H
#define PL1_MATRIX_H

typedef struct {
    double v[4];
} Matrix;

Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y);
void print_matrix(Matrix a);

#endif
```

```c
/* noinclude/vector_main.c（matrix.h だけを読む） */
#include "matrix.h"

int main(void)
{
    Vector x = {{1.0, 2.0}};
    Vector y = {{3.0, 4.0}};
    Matrix a = {{1.0, -1.0, -1.0, 1.0}};

    print_matrix(a);
    print_vector(axpy(2.0, x, y));
    print_vector(gemv(2.0, a, x, 1.0, y));
    return 0;
}
```

実際の GCC の診断（`_BuildErrors/` で実行。最初の部分）:

```text
$ gcc -std=c17 -Wall -Wextra -Wpedantic -c noinclude/vector_main.c
In file included from noinclude/vector_main.c:2:
noinclude/matrix.h:10:1: error: unknown type name 'Vector'
   10 | Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y);
      | ^~~~~~
noinclude/matrix.h:10:37: error: unknown type name 'Vector'
（以下，vector_main.c の Vector x などにも同じ error と，print_vector の暗黙の宣言の警告が続く）
```

MSVC では `error C2061: syntax error: identifier 'Vector'`（構文エラー: 識別子 'Vector'）などのコンパイルエラーになる（文面は例）。最初のエラーが `matrix.h` の中で出ることから，ヘッダ自身が必要な型を用意していないと分かる。

2 つの工夫の区別:

| 工夫 | 何を防ぐか | 仕組み |
| --- | --- | --- |
| インクルードガード（同じ内容を二度読まない） | **同じ翻訳単位**に同じヘッダの内容（構造体の定義）が 2 回現れること | 1 回目に `PL1_VECTOR_H` を定義し，2 回目は `#endif` まで飛ばす |
| ヘッダが自分で必要なヘッダを読む（必要な型をヘッダ自身で用意する） | 利用者が「先に `vector.h` を読む」順序を守らないと `matrix.h` がコンパイルできないこと | `matrix.h` の中で `#include "vector.h"` する |

前者だけでは「型がない」問題は解決せず，後者だけでは（複数経路で読まれたときの）重複が起きる。両方を組み合わせて，どの順序・何回読んでも正しくなるヘッダにする。直接の `#include "vector.h"` は，`vector_main.c` 自身が `Vector` を使うことを示すために残しておくのがよい。

### 採点のポイント・よくある誤り

- `SplitCalc` の `main.c` を同じプロジェクトに入れたまま（`main` の重複 `LNK2005`），`vector.h`・`matrix.h` を別の実フォルダに保存した（`C1083`）。
- `2Ax+y` を `(−1, 1)`（`Ax` だけ）や `(2·(−1)+3, …)` の計算違いで書いている。行列の添字 `v[2*i+j]` の行優先の並びを確認させる。
- ガードを外す実験で `matrix.h` のガードまで外した，本文を書き換えた，戻し忘れて提出した。
- ガードの効果を「別の `.c` に同じ定義を置く問題も防ぐ」と説明している（防がない）。
- 「直接の include を外すとエラーになる」と予測して，実際の結果（成功）を記録していない。成功した理由を `matrix.h` の中身と結び付けて説明できていれば正解。
- ガード名を `HEADER_H` のように使い回す，`_VECTOR_H`（先頭がアンダースコア＋大文字は予約）にしている。

---

## 発展1　静的ライブラリとして使う（`CalcLib` / `CalcApp`）

**要点**: `calc.c` を**静的ライブラリ**（`.lib`）としてビルドし，別のプロジェクト `CalcApp`（`main.c` だけ）から参照してリンクする。
「宣言を読む（インクルード ディレクトリ）」と「実装をリンクする（参照・`.lib`）」が別の設定であることを確かめる。

- [CalcLib/calc.h](CalcLib/calc.h)・[CalcLib/calc.c](CalcLib/calc.c): `add`・`multiply` に課題2の `subtract` を追加した版（`main` はない）。
- [CalcApp/main.c](CalcApp/main.c): `add`・`multiply`・`subtract` を呼ぶ。

### Visual Studio での手順（授業どおり）

1. ソリューション `LibraryDemo` に空のプロジェクト `CalcLib` を作り，「プロパティ → 構成プロパティ → 全般 → 構成の種類」を「スタティック ライブラリ (.lib)」にする。C/C++ → 言語で C17，詳細設定で「C コードとしてコンパイル (/TC)」。
2. `CalcLib` に `calc.c`（ソース ファイル）と `calc.h`（ヘッダー ファイル）を保存・追加する。`main.c` は入れない（ライブラリには `main` は要らない）。
3. 同じソリューションに空のプロジェクト `CalcApp` を追加し，C17・`/TC` を設定して `main.c` だけを入れる。
4. `CalcApp` の「参照」を右クリック →「参照の追加」で `CalcLib` にチェックを付ける。ビルド順（`CalcLib` → `CalcApp`）と `CalcLib.lib` のリンクが自動で設定される。
5. `CalcApp` の「C/C++ → 全般 → 追加のインクルード ディレクトリ」に `calc.h` のある `CalcLib` の実フォルダ（例: `$(SolutionDir)CalcLib`）を追加する。既存の値（`%(AdditionalIncludeDirectories)`）は消さない。
6. 両プロジェクトの構成（Debug/Release）とプラットフォーム（x64）をそろえ，`CalcApp` を右クリック →「スタートアップ プロジェクトに設定」してビルド・実行する。

### このリポジトリ（CMake）での対応

| Visual Studio の操作 | CMake（このリポジトリ） |
| --- | --- |
| `CalcLib` の構成の種類を「スタティック ライブラリ」 | [CalcLib/CMakeLists.txt](CalcLib/CMakeLists.txt) の `add_library(CalcLib STATIC calc.c calc.h)`（授業と同じ警告設定は `softprac_apply_options(CalcLib)`） |
| `CalcApp` に `main.c` だけを入れる | [CalcApp/CMakeLists.txt](CalcApp/CMakeLists.txt) の `softprac_add_program(CalcApp main.c)` |
| 「参照の追加」で `CalcLib` | `target_link_libraries(CalcApp PRIVATE CalcLib)`（ビルド順もこれで決まる） |
| 「追加のインクルード ディレクトリ」に `CalcLib` のフォルダ | `target_include_directories(CalcApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../CalcLib")` |
| `CalcApp` をスタートアップ プロジェクトに | 起動項目（`.vs/launch.vs.json`）で「week12 CalcApp」を選ぶ |

- フォルダ名順では `CalcApp` が `CalcLib` より先に読まれるが，`target_link_libraries` のターゲット名はすべての `CMakeLists.txt` を読み終えてから解決されるので，そのまま参照できる。
- ライブラリは MSVC では `CalcLib.lib`，GCC/Clang では `libCalcLib.a` として `<ビルドフォルダ>/lib/week12/` にできる（他の環境の `.a` が Windows の `.lib` に当たる）。中身は `calc.c` のオブジェクト 1 つで，`add`・`multiply`・`subtract` の定義を持つ（`ar t` → `calc.c.o`，`nm` → `T add`・`T multiply`・`T subtract`）。

実行結果（`CalcApp`）:

```text
add=3.5
multiply=3.0
subtract=3.0
```

まず講義の加算・乗算だけの 3 ファイルで試すと，`add=3.5`・`multiply=3.0` の 2 行（課題1と同じ）。`subtract` を追加した後が上の 3 行。
講義の 2 関数だけの版は，[CMakeLists.txt](CalcApp/CMakeLists.txt) の `softprac_add_variant` で `subtract` の呼び出しを除いた `CalcApp_lecture`（同じく `CalcLib` を参照する）としてテストしている。

### 更新の伝わり方（4 つの作業）

| 作業 | 何をするか | 失敗するとどうなるか |
| --- | --- | --- |
| 1. `calc.h` に宣言を追加して利用側へ見せる | `double subtract(double a, double b);` を追加。`CalcApp` の `main.c` は追加のインクルード ディレクトリからこの宣言を読む | 宣言がないと `main.c` のコンパイルで警告 `C4013`（暗黙の宣言。GCC 14 以降や `-Werror`・`/WX` ではエラー）。無視すると `int` を返すと見なされ，正しい値を受け取れない |
| 2. `calc.c` に実装を追加し，`CalcLib` をビルドして `.lib` を更新する | `subtract` の本体を `CalcLib` でコンパイルし，`CalcLib.lib` を作り直す | `.lib` に `subtract` がないと 4. で `LNK2019` |
| 3. `CalcApp` の呼び出しをコンパイルする | `main.c` を 1. の宣言でコンパイルし，`subtract` への未解決の参照を持つ `main.obj` を作る | 宣言と呼び出しの型が合わないとここでエラー |
| 4. `CalcApp` を更新後の `.lib` とリンクする | `main.obj` と新しい `CalcLib.lib` の `subtract` を結び付けて `CalcApp.exe` を作る | 古い `.lib` とリンクすると `LNK2019`。静的ライブラリの更新は再リンクして初めて `.exe` に入る |

プロジェクト参照が正しければ，`CalcApp` のビルドで 2 → 3 → 4 の順に必要な作業が行われる。このリポジトリで実際に確かめた記録
（各コマンドの最初の `[0/2] Re-checking globbed directories...` と，`main.c` を更新したときに出る `[1/2] Re-running CMake...` から `-- Build files have been written to: ...` までの 3 行は省略。
`main.c` は書き換えた版 `CalcApp_lecture` の元のソースなので，更新すると CMake が構成し直す）:

```text
$ touch week12/CalcLib/calc.c && cmake --build $B --target CalcApp      ← 実装だけを変更
[1/3] Building C object projects/week12/CalcLib/CMakeFiles/CalcLib.dir/calc.c.o
[2/3] Linking C static library lib/week12/libCalcLib.a
[3/3] Linking C executable bin/week12/CalcApp
$ touch week12/CalcApp/main.c && cmake --build $B --target CalcApp      ← 利用側だけを変更
[1/2] Building C object projects/week12/CalcApp/CMakeFiles/CalcApp.dir/main.c.o
[2/2] Linking C executable bin/week12/CalcApp
$ touch week12/CalcLib/calc.h && cmake --build $B --target CalcApp      ← （参考）公開する宣言を変更
[1/4] Building C object projects/week12/CalcLib/CMakeFiles/CalcLib.dir/calc.c.o
[2/4] Building C object projects/week12/CalcApp/CMakeFiles/CalcApp.dir/main.c.o
[3/4] Linking C static library lib/week12/libCalcLib.a
[4/4] Linking C executable bin/week12/CalcApp
```

実装だけの変更では `main.c` は再コンパイルされないが，`.lib` が新しくなったので `CalcApp` は**再リンク**される。`calc.h` を変えると，それを読む `calc.c`（ライブラリ側）と `main.c`（利用側）の両方が再コンパイルされる。
一方，すでに別の場所へコピー・配布した `CalcApp.exe` には古い `add` などのコードが組み込まれているので，`.lib` を作り直しても**その `.exe` の内容は変わらない**（配り直しが必要）。

### 配布済み `.lib` を使う場合との違い（講義 9 の表）

同じソリューションにソースのない（配布された `calc.h` と `CalcLib.lib` だけがある）ライブラリは，プロジェクト参照ではなく次の 3 つを設定する。

| 設定（`CalcApp` のプロパティ） | 役割 | 設定値の例 |
| --- | --- | --- |
| C/C++ → 全般 → 追加のインクルード ディレクトリ | `#include "calc.h"` の**検索先**（宣言を読む）。コンパイル時に使う | `C:\libs\calc\include;%(AdditionalIncludeDirectories)` |
| リンカー → 全般 → 追加のライブラリ ディレクトリ | `.lib` を探す**検索先**。フォルダを足すだけでは何もリンクされない | `C:\libs\calc\lib\x64\Debug;%(AdditionalLibraryDirectories)` |
| リンカー → 入力 → 追加の依存ファイル | 実際にリンクする**`.lib` のファイル名** | `CalcLib.lib;%(AdditionalDependencies)` |

- 検索先（ディレクトリ）とファイル名は別の設定。ライブラリ ディレクトリだけを設定すると `LNK2019`，依存ファイルだけで検索先がないと `LNK1104: ファイル 'CalcLib.lib' を開くことができません`，インクルード ディレクトリがないと `C1083`。
- `%(...)`／「親またはプロジェクトの既定値から継承」を消すと標準ライブラリなどの既定の設定も失われるので，**既存の継承設定を残して追加**する。
- 今回の `CalcLib` は静的ライブラリなので，実装は `CalcApp.exe` に組み込まれ，**`CalcLib.dll` は存在せず探す必要もない**。ただし `CalcApp.exe` は Visual C++ ランタイムには依存する（Release の `/MD` なら `vcruntime140.dll`・`ucrtbase.dll`，Debug の `/MDd` なら `vcruntime140d.dll`・`ucrtbased.dll` など）。
- プラットフォームが違う（x86 の `.lib` を x64 のアプリに）と `LNK4272`（マシンの種類の競合），実行時ライブラリの設定が違う（`/MT` と `/MD`，Debug と Release）と，C のライブラリでは主に `LNK4098`（既定のライブラリ `LIBCMT` などが他のライブラリと競合する）の警告と，場合により `LNK2005` が出る（C++ では標準ライブラリのヘッダの仕組みで `LNK2038`（`RuntimeLibrary` の不一致）になる）ので，構成・プラットフォーム・実行時ライブラリをそろえる。

### 採点のポイント・よくある誤り

- `CalcLib` に `main.c` を入れた／`CalcApp` に `calc.c` も入れた（後者はライブラリを使わずに直接コンパイルしているだけ。参照も加えると `LNK2005` になることがある）。
- 「参照の追加」をせずにビルド → `LNK2019`。インクルード ディレクトリの設定をしない → `C1083`。この 2 つの違いを説明できているか。
- `CalcLib` を「動的ライブラリ (.dll)」にした，`CalcLib.dll` が見つからないと書いた（静的ライブラリなので不要）。
- Debug x64 と Release x64（あるいは x86）が混在している，`CalcApp` をスタートアップにせず「スタティック ライブラリは起動できません」というメッセージを出している。
- 更新の 4 作業を 1 つの「ビルド」として説明している → 宣言の公開・ライブラリの再ビルド・利用側のコンパイル・再リンクを分けて書かせる。
- 「`.lib` を作り直せば配布済みの `.exe` も新しくなる」と書いている（確認問題4）。

---

## 発展2　並べ替えをモジュールにする（`SortModule` / `sort_main.c`・`intlib.c`・`intlib.h`）

**要点**: 公開する操作（`parse_count`・`sort_ints`）だけをヘッダに出し，`qsort` の比較関数 `compare_int` は `intlib.c` の中の `static` 関数に隠す。
個数の検査は第10回の `strtol` の手順（`end`・`*end`・`errno`・範囲）をモジュールの関数にする。

- [intlib.h](SortModule/intlib.h): `INTLIB_CAPACITY`（8），`int parse_count(const char *text, int *out);`，`void sort_ints(int a[], size_t n);`。`size_t` のために `stddef.h` をヘッダ自身で読む。
- [intlib.c](SortModule/intlib.c): `static int compare_int(...)`（大小比較で −1・0・1），`parse_count`（`strtol` で 0〜8 だけ成功，失敗時は `*out` を変えない），`sort_ints`（`qsort(a, n, sizeof a[0], compare_int)`）。
- [sort_main.c](SortModule/sort_main.c): 引数の個数の検査，`parse_count` の呼び出し，エラー表示（`stderr`・`EXIT_FAILURE`），`sort_ints` の呼び出しと表示。
  配列は `int data[INTLIB_CAPACITY] = {7, -2, 7, 0, 3, 9, -8, 1};` の固定長で，有効な個数 `n` を別に持つ（可変長配列は使わない）。

`intlib.c` の中心部分:

```c
static int compare_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int parse_count(const char *text, int *out)
{
    char *end;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE ||
        value < 0 || value > INTLIB_CAPACITY) {
        return 0;  /* 数字がない・余分な文字・long の範囲外・0〜8 の範囲外 */
    }
    *out = (int)value;
    return 1;
}

void sort_ints(int a[], size_t n)
{
    qsort(a, n, sizeof a[0], compare_int);  /* 関数名を渡す（呼び出した結果ではない） */
}
```

### 引数を設定して検証する（表の解答）

Visual Studio では `SortModule` の「プロパティ → 構成プロパティ → デバッグ → コマンド引数」に設定する（設定の対象が実行する構成・プラットフォームと一致しているか確認）。
このリポジトリでは [run.args](SortModule/run.args)（`5`）が Visual Studio の起動構成の引数になる。エラーの表示は `stderr`，終了コードは 1。

| コマンド引数 | 期待する結果（実際の表示） |
| --- | --- |
| 5 | 先頭 5 個 {7, −2, 7, 0, 3} を昇順にした `-2 0 3 7 7` |
| 0 | 要素を表示せず，改行だけ（空行 1 行） |
| 1 | `7`（1 個の並べ替えは変化なし） |
| 8 | `-8 -2 0 1 3 7 7 9`（全要素。重複する 7 も 2 つ残る） |
| 指定なし，`""`，`abc`，`3x` | すべて拒否（終了コード 1，標準出力には何も出ない）。指定なしは個数の不足で `usage: SortModule N (N is an integer from 0 to 8)`。`""` は引数が 1 つあるが数字がない（`end == text`），`abc` も同じ，`3x` は末尾に余分な文字（`*end != '\0'`）で，`invalid N: "abc" (expected an integer from 0 to 8)` のように表示 |
| −1（半角では`-1`），9 | 拒否（範囲外。`invalid N: "-1" ...`，`invalid N: "9" ...`） |
| 999999999999999999999999 | 拒否（`long` の範囲を超えて `errno == ERANGE`。Windows の 32 ビット `long` でも Linux の 64 ビット `long` でも範囲外） |
| 3 4 | 拒否（引数が 2 つで過剰。`usage: ...`。`3` だけを使って成功にしない） |

実際の実行結果（Linux，GCC。引数は `[]` 内）:

```text
[5] -2 0 3 7 7
[0] （空行）
[1] 7
[8] -8 -2 0 1 3 7 7 9
（引数なし）   usage: SortModule N (N is an integer from 0 to 8)         exit=1
[""]           invalid N: "" (expected an integer from 0 to 8)          exit=1
[abc]          invalid N: "abc" (expected an integer from 0 to 8)       exit=1
[3x]           invalid N: "3x" (expected an integer from 0 to 8)        exit=1
[-1]           invalid N: "-1" (expected an integer from 0 to 8)        exit=1
[9]            invalid N: "9" (expected an integer from 0 to 8)         exit=1
[999999999999999999999999]  invalid N: "999999999999999999999999" (expected an integer from 0 to 8)  exit=1
[3] [4]        usage: SortModule N (N is an integer from 0 to 8)         exit=1
```

`strtol` の性質により，`+5`・`" 5"`（先頭の空白）・`-0`・`08` は受け付け（`+5`・`" 5"` は `-2 0 3 7 7`，`-0` は空行，`08` は 10 進の 8 として全 8 個），`"5 "`（末尾の空白）は拒否する
（第10回の `ParseNumber` と同じ方針。基数 10 を指定しているので `08` を 8 進とは解釈しない。テスト `plus5`・`leading_space`・`minus_zero`・`leading_zero`・`trailing_space`）。

テストは表のすべての行をケースにした: `n5`・`n0`・`n1`・`n8`・`no_args`・`empty_string`（`.args` は空行 1 行＝空文字列の引数 1 つ）・`abc`・`trailing_x`（`3x`）・`minus1`・`n9`・`huge`・`two_args`（`3 4`）と，`plus5`・`leading_space`・`minus_zero`・`leading_zero`・`trailing_space`。
エラーのケースは標準エラー出力（`.err`）と終了コード（`.code`）も比べている。

### `INT_MAX`・`INT_MIN` で試す

`data` の先頭 2 つを `INT_MAX`，`INT_MIN` に変え，`#include <limits.h>` を追加して `N=2` で実行した（[CMakeLists.txt](SortModule/CMakeLists.txt) の `softprac_add_variant` で同じ書き換えをした版をビルド・テストしている）:

```c
#include <limits.h>
...
    int data[INTLIB_CAPACITY] = {INT_MAX, INT_MIN, 7, 0, 3, 9, -8, 1};
```

```text
$ SortModule 2
-2147483648 2147483647
```

小さい方（`INT_MIN`）が先になる（`int` が 32 ビットの Windows・Linux とも同じ値）。

**差を返す比較関数が危険な理由**: `return *(const int *)a - *(const int *)b;` とすると，`INT_MAX - INT_MIN` は約 4.29×10⁹ で `int` の範囲（最大 2147483647）を超え，**符号付き整数のオーバーフロー（未定義動作）**になる。
多くの環境では折り返して負の値（−1）になり，「`INT_MAX` の方が小さい」と誤判定される。実際に試すと UBSan は次を報告し，並べ替え結果も逆になった:

```text
badcmp.c:6:28: runtime error: signed integer overflow: 2147483647 - -2147483648 cannot be represented in type 'int'
2147483647 -2147483648
```

比較関数は大小比較で −1・0・1 を返す（講義 8.4）。`(x > y) - (x < y)` という書き方も同じ意味で安全。

### 設計を説明する

- **`intlib.h` に `compare_int` の宣言を置かないのはなぜか**: `compare_int` は `qsort` に渡すための**実装の都合**で，利用者（`sort_main.c`）が直接呼ぶ操作ではないから。`static` にして `intlib.c` の翻訳単位の中だけの名前にすれば，
  他のファイルの同名関数と衝突せず（`LNK2005` にならない），比較方法を変えても公開する使い方（`sort_ints`）は変わらない。ヘッダに宣言すると `static` と矛盾し，利用者に不要な名前を見せることになる。
- **`sort_main.c` が `qsort` の使い方を知らなくてもよいのはなぜか**: `sort_ints(int a[], size_t n)` という「配列と個数を渡せば昇順になる」契約だけを公開し，`qsort` の引数（要素サイズ・比較関数）や `stdlib.h` の扱いを `intlib.c` に閉じ込めたから。
  並べ替えの方法を自作の挿入ソートなどに変えても `sort_main.c` は修正不要。
- **型の宣言・数値の検査・エラー表示はどこにあるか**: 公開する型・定数・関数の宣言（`INTLIB_CAPACITY`，`size_t` のための `stddef.h`，`parse_count`・`sort_ints` のプロトタイプ）は `intlib.h`。
  数値の検査（`strtol`・`end`・`errno`・0〜8 の範囲）は `intlib.c` の `parse_count`。引数の個数の検査と，エラーの表示（`stderr` への `fprintf`，`EXIT_FAILURE`）は `sort_main.c`。
  `parse_count` は表示をせず成功・失敗だけを返すので，表示の方法（言語・出力先）を決めるのは呼び出し側になる。
- **固定配列の容量と有効な個数 `N` は同じものか**: 違う。容量 `INTLIB_CAPACITY`（8）は配列の要素数でコンパイル時に決まり，`N` は実行時に引数で決まる「使う要素の個数」（0〜8）。
  `N ≤ 容量` を `parse_count` で保証してから `sort_ints(data, n)` に `n` を渡すので，範囲外にはアクセスしない。`sizeof` で求まるのは容量であって `N` ではない。

### 採点のポイント・よくある誤り

- `qsort(data, n, sizeof data[0], compare_int(...))` と比較関数を**呼び出した結果**を渡している（関数名を渡す）。
- 比較関数で `return *a - *b;` と書いている（`INT_MAX`/`INT_MIN` でオーバーフロー），`const void *` を `int *` 以外（`char *` など）として読んでいる。
- `compare_int` を `static` にせずヘッダに宣言した，`intlib.h` に `#include <stddef.h>` がない（`sort_main.c` の取り込み順に依存）。
- `atoi` を使って `abc` を 0 として成功にしている，`3x` を 3 として受け付けている，`argc` を調べずに `argv[1]` を読んでいる（引数なしで `NULL` を渡す）。
- `3 4` で 3 を使って成功にしている（引数の過剰を拒否する仕様）。`N=0` で何も出さない（改行 1 つを出す仕様）・末尾に空白を出す。
- `int data[n];`（可変長配列。MSVC では使えない）や，容量と `N` を混同して 8 個全部を並べ替えて先頭 `N` 個を表示している（`N=5` が `-8 -2 0 1 3` になる）。

---

## 発展3　標準ライブラリの契約を確かめる（`LibraryCheck` / `library_check.c`）

**要点**: 標準ライブラリも「ヘッダで宣言を読み，決められた条件で呼ぶ」ライブラリ。関数ごとに**ヘッダ・入力条件・戻り値の意味**を確かめる。
ソースは演習ページのコードのまま（先頭に課題のコメントだけ追加）。自作の `calc.c` などは入れない。

### 関数の契約（実行前にまとめる表）

| 関数・マクロ | ヘッダ | 入力条件 | 戻り値・作用の意味 | このプログラムでの値 |
| --- | --- | --- | --- | --- |
| `sqrt(x)` | `math.h` | `x ≥ 0`（負だと定義域エラー） | 非負の平方根（`double`） | `sqrt(9.0)` → 3.0 |
| `pow(x, y)` | `math.h` | `x < 0` で `y` が整数でないと定義域エラー，`x` も `y` も 0 なら定義域エラーになり得る，`x` が 0 で `y` が負だと極エラーになり得る。結果が大きすぎると範囲エラー | `x` の `y` 乗（`double`，丸め誤差あり） | `pow(3.0, 2.0)` → 9.0 |
| `fabs(x)` | `math.h` | 任意の `double` | 絶対値 | `fabs(-2.5)` → 2.5 |
| `isalpha(c)`・`isdigit(c)` | `ctype.h` | `c` は `EOF` か `unsigned char` で表せる値（`char` は `(unsigned char)` に変換して渡す） | 条件に合えば**0 以外**（1 とは限らない），合わなければ 0 | `!= 0` で 0/1 にして 1，1 |
| `FLT_MIN` | `float.h` | ― | `float` の**最小の正の正規化数**（負の最小値ではない。最も負の値は `-FLT_MAX`） | `FLT_MIN > 0.0f` → 1 |
| `strcpy(dst, src)` | `string.h` | `src` は終端 `'\0'` のある文字列，`dst` は終端を含む長さ以上の容量，領域が重ならない | 最初の `'\0'` までを終端ごとコピーし，`dst` を返す | `"ab"` と終端の 3 バイト（容量 10 で十分） |
| `memcpy(dst, src, n)` | `string.h` | `dst`・`src` とも `n` バイト以上の領域，重ならない（重なるなら `memmove`） | `n` バイトをそのままコピー（終端を補わない），`dst` を返す | 5 バイト `a b \0 c d`（容量 10 で十分） |
| `assert(式)` | `assert.h` | 式に副作用を入れない。`NDEBUG` が定義されていると式ごと無効 | 式が偽なら診断を出して異常終了（`abort`），真なら何もしない | 2 つとも真なので何も起きない |
| `srand(seed)` | `stdlib.h` | `unsigned int` の種 | 戻り値なし。同じ種なら同じ処理系では同じ系列を再現する | `srand(123U)` を 2 回 |
| `rand()` | `stdlib.h` | ― | 0〜`RAND_MAX` の `int`（MSVC は `RAND_MAX` = 32767，glibc は 2147483647） | `first == again` → 1 |
| `RAND_MAX` | `stdlib.h` | ― | `rand` の最大値（少なくとも 32767） | `(double)rand() / RAND_MAX` は 0 以上 1 以下（両端を含み得る） |

**コピー先の容量の確認**: `src` は 5 バイトで，3 バイト目に `'\0'` がある。`strcpy` がコピーするのは `"ab"` と終端の 3 バイト，`memcpy` は `sizeof src` = 5 バイトで，どちらも容量 10 の `text`・`bytes` に収まり，コピー元と重ならない。
`text`・`bytes` は `{0}` で全要素 0 に初期化してあるので，`bytes` の 6 バイト目以降も 0。

### 実行結果

```text
math=3.0 9.0 2.5
alpha=1 digit=1 min_positive=1
text=ab bytes=ab cd
same_seed=1
in_range=1
```

- `text=ab`: `strcpy` は最初の `'\0'` で止まるので `c`・`d` はコピーされない（`text[2] == '\0'` の `assert` が通る）。
- `bytes=ab cd`: `memcpy` は 5 バイトすべてをコピーするので `bytes[3] == 'c'`，`bytes[4] == 'd'`。`bytes` を `%s` で表示すると `ab` で止まるので，1 文字ずつ `%c` で表示している。
- `same_seed=1`: 同じ種 123 から始めた最初の値は等しい（値そのものは処理系に依存するので表示しない）。`in_range=1`: `u` は 0 以上 1 以下。
- この 5 行は乱数の値を表示しないので，Windows（MSVC）でも Linux でも同じ表示になる。

Linux の GCC/Clang では `sqrt`・`pow` の実装が数学ライブラリ（libm）にあり，`-lm` に当たるリンク指定が要る（このリポジトリでは共通の `softprac_apply_options` が GCC/Clang で libm をリンクする。指定がないと Clang では `undefined reference to 'sqrt'` になった。GCC は定数の計算をコンパイル時に済ませて通ることがある）。
授業の Visual Studio（MSVC）では標準の実行時ライブラリに含まれるので，`-lm` のような設定は入力しない（講義 5）。

### 追加の観察

1. **`NDEBUG` を定義する**: `#define _CRT_SECURE_NO_WARNINGS` の次（`#include <assert.h>` より前）に `#define NDEBUG` を置いてビルドすると，表示は上と**まったく同じ 5 行**で，終了コードも 0 になった
   （[CMakeLists.txt](LibraryCheck/CMakeLists.txt) の `softprac_add_variant` で同じ書き換えをした版をテストしている。その版では `assert(bytes[3] == 'c');` を**わざと偽になる** `assert(bytes[3] == 'x');` にも変えてあり，それでも異常終了しないことで `assert` が無効になっていることを確かめている）。前処理後を見ると 2 つの `assert(...)` は `((void) (0));` に置き換わっており，式は評価されない。
   一方，`strcpy`・`memcpy`・`srand`・`rand` は `assert` の外にあるので同じように実行される。`#include <assert.h>` の後で定義しても効かない（マクロは取り込んだ時点の定義で決まる）。Visual Studio では Release 構成が既定で `NDEBUG` を定義する。
2. **`assert` の式にコピーや `rand` を入れない理由**: `NDEBUG` を定義した構成（Release など）では `assert` の式自体が評価されないので，`assert(strcpy(text, src) != NULL)` や `assert(rand() >= 0)` と書くと，
   その構成ではコピーも乱数の生成も行われず，プログラムの動作が変わる（乱数の系列もずれる）。`assert` は「ここでは必ず成り立つはず」という開発中の前提の確認であり，入力検査や必要な処理は `if` と通常の文で書く。
   参考: `int n = 9; assert(n >= 0 && n <= 8);` だけのプログラムで試すと，前提が崩れて ``af: af.c:5: main: Assertion `n >= 0 && n <= 8' failed.`` を出して異常終了（Linux では終了コード 134），`NDEBUG` ありでは何も起きずに続行した。
3. **`rand() % 10` が 0〜9 になる理由と偏り**: `rand()` は 0 以上なので，10 で割った余りは 0〜9 になる。しかし `rand()` が取り得る値の個数（`RAND_MAX + 1`）が 10 で割り切れなければ，余りの出やすさに差が出る。
   MSVC の `RAND_MAX` = 32767 では 32768 通りで，32768 = 10×3276 + 8 なので，余り 0〜7 は 3277 通り，8・9 は 3276 通りになる（glibc の 2147483648 通りでも余り 0〜7 がわずかに多い）。
   また `rand` の系列の質は処理系に依存する。何回か実行して偏りが見えなくても，有限回の結果は「偏りがある可能性を否定できない」だけで一様性の**証明にはならない**（逆に偶然の偏りも起こる）。暗号やパスワードには使わない。
4. **発展2 の配列を `rand() % 1024` で用意する（任意）**: `sort_main.c` を次のように変えた版（全文。`intlib.c`・`intlib.h` は発展2 のまま）を試した（README だけに載せる。値は処理系に依存するのでテストにはしない）。

   ```c
   /* 第12回 発展3 追加の観察4: 発展2 の sort_main.c の初期値を rand() % 1024 で用意する版 */
   #include <stdio.h>
   #include <stdlib.h>
   #include "intlib.h"
   static void print_ints(const int a[], int n)
   {
       for (int i = 0; i < n; ++i) {
           if (i > 0) {
               printf(" ");
           }
           printf("%d", a[i]);
       }
       printf("\n");
   }
   int main(int argc, char *argv[])
   {
       int data[INTLIB_CAPACITY];
       int n;

       if (argc != 2) {
           fprintf(stderr, "usage: SortModule N (N is an integer from 0 to %d)\n", INTLIB_CAPACITY);
           return EXIT_FAILURE;
       }
       if (!parse_count(argv[1], &n)) {
           fprintf(stderr, "invalid N: \"%s\" (expected an integer from 0 to %d)\n",
                   argv[1], INTLIB_CAPACITY);
           return EXIT_FAILURE;
       }

       srand(123U);  /* 種はループの前に 1 回だけ．同じ種なら同じ処理系では同じ系列 */
       for (int i = 0; i < n; ++i) {
           data[i] = rand() % 1024;  /* 0〜1023 */
       }
       printf("before: ");
       print_ints(data, n);
       sort_ints(data, (size_t)n);
       printf("after:  ");
       print_ints(data, n);
       return 0;
   }
   ```

   Linux（glibc）での実行例:

   ```text
   $ SortModule 8
   before: 929 661 113 894 903 763 107 958
   after:  107 113 661 763 894 903 929 958
   $ SortModule 3
   before: 929 661 113
   after:  113 661 929
   ```

   確かめるのは値そのものではなく，**要素数が `N` 個のまま**で，after が**昇順**（隣同士で前 ≤ 後）になっていること，before と同じ値の並べ替えであること。MSVC では値が違う。
   `srand` をループの中で毎回呼ぶと，毎回同じ種から始まって同じ値が並ぶ（ループの前に 1 回だけ呼ぶ理由）。

`assert` の効果を確かめるために配列の範囲外アクセスをしたり，`system` で外部コマンドを実行したりはしない（演習ページの注意どおり）。

### 採点のポイント・よくある誤り

- 表で `isdigit` の戻り値を「真なら 1」，`FLT_MIN` を「`float` の最小（最も負）の値」と書いている。
- `isalpha(c)` に `char` の負の値をそのまま渡すコードを書いている（`(unsigned char)` に変換する）。
- `strcpy` と `memcpy` の違いを「同じ」と書いた，`bytes` を `%s` で表示して `ab` だけになり「`memcpy` も `'\0'` で止まる」と誤解している。
- `NDEBUG` の定義を `#include <assert.h>` の後に置いて「変化なし」とだけ書いている（後に置くと `assert` は無効にならない）。
- `_CRT_SECURE_NO_WARNINGS` を「`strcpy` を安全にする設定」と説明している（警告を抑えるだけで，容量の確認は自分で行う）。
- `rand() % 10` の偏りを「何回か実行して均等だったから偏りはない」と結論している。

---

## 確認問題

1. **「`calc.h` を追加したので `calc.c` を追加しなくてもよい」は正しいか** — 正しくない。`calc.h` は宣言を前処理で取り込むだけで，`add` などの定義（本体）は `calc.c` をコンパイルした `calc.obj` にしかない。
   `calc.c` をビルド対象にしなければ，`main.c` のコンパイルは通ってもリンクで `LNK2019`（未解決の外部シンボル）になる（課題3の記録 3）。
2. **インクルードガードで，同じ外部関数を 2 つの `.c` に定義した問題は解決するか** — 解決しない。ガードが防ぐのは**同じ翻訳単位の中**で同じヘッダの内容が 2 回展開されることだけ。
   `main.c` と `calc.c` は別々の翻訳単位なので，それぞれに `add` の定義があれば `main.obj` と `calc.obj` の両方に定義ができ，リンクで `LNK2005`／`LNK1169` になる（課題3の記録 4）。ヘッダに関数本体を書いた場合も同じ。定義は 1 つの `.c` だけに置く。
3. **`.lib` の検索先が正しくても，ヘッダが見つからないことはあるか** — ある。`.lib` の検索先（リンカー → 全般 → 追加のライブラリ ディレクトリ）はリンク時に `.lib` を探す設定で，
   `#include "calc.h"` の検索先（C/C++ → 全般 → 追加のインクルード ディレクトリ）とは別の設定だから。インクルード ディレクトリが正しくなければ，前処理で `C1083` になる（リンクの段階まで進まない）。
4. **静的ライブラリを更新すれば，配布済みの `.exe` も自動的に新しくなるか** — ならない。静的ライブラリのコードはリンク時に `.exe` へ**組み込まれる**ので，配布済みの `.exe` は古いコードのまま。
   更新を反映するには利用側を**再リンク**して新しい `.exe` を作り，配り直す必要がある（発展1「更新の伝わり方」）。DLL なら互換性があれば DLL の差し替えで済む場合があるが，今回の `CalcLib` は静的ライブラリ。
5. **不完全型の `Vector *` を宣言できることと，`Vector` の実体を作れることは同じか** — 同じではない。`typedef struct vector Vector;` だけ（中身を示さない不完全型）でも，ポインタ `Vector *p` は大きさが分かるので宣言・受け渡しができる。
   しかし `Vector x;` の実体を作る，`sizeof(Vector)` を求める，`p->v[0]` のようにメンバを参照するには構造体の中身（大きさ・配置）が必要なので，不完全型のままではコンパイルエラーになる。
   実体の作成やメンバの操作は，`struct vector` の定義を持つ実装の `.c` が提供する関数（作成・取得・解放）を通して行う（講義 7.3）。

### 参考：講義ページの確認問題

1. インクルードはリンクと同じ処理ではない（前処理での宣言の取り込みと，リンクでの定義の結び付け）。
2. ガードは同じ翻訳単位の中でのヘッダの再取り込み（特に構造体の定義の重複）を防ぐ。
3. 宣言が正しくても実装の `.c` をビルドから除外した・ライブラリを参照していない・関数名の綴りが定義と違う，とリンクで失敗する。
4. `calc.c` の本体の変更は `calc.c` の再コンパイルとリンクだけ，`calc.h` の変更はそれを読む `main.c` と `calc.c` の両方の再コンパイルが必要（課題1 手順5 で確認）。
5. `matrix.h` の宣言が `Vector` を使うので，利用者の取り込み順に依存しないよう `matrix.h` 自身が `vector.h` を読む。
6. `extern int count;` は領域を作らない宣言なので何個の `.c` が読んでもよい。ヘッダに `int count = 0;` を書くと読んだ `.c` ごとに定義ができ，`LNK2005` になる。
7. 自動では変わらない（再リンクが必要）。
8. `FLT_MIN` は最小の正の正規化数，`isdigit` の真は 0 以外（1 とは限らない），`assert` は `NDEBUG` で無効になり式も評価されない。

---

## チェックリスト

| 項目 | 確認できる課題・内容 |
| --- | --- |
| 正常な値だけでなく，課題に示された境界の値でも確認した | 課題2 の検証表（`subtract` の 0−0・2−5，`calc_divide` の 0÷2・6÷0）と課題4 の単位行列・`alpha`=0 は書き換えた版（`SplitCalc`・`VectorCalc` の variants），発展2 の `N` = 0・1・8，−1・9・巨大な数・`""`・`3x`・`3 4` は `SortModule/tests/` の引数のケース，`INT_MAX`/`INT_MIN` は `SortModule` の variant で，それぞれ自動テストにしている |
| 警告を確認し，原因を説明・修正した | 全プロジェクトが GCC/Clang `-Wall -Wextra -Wpedantic -Werror` で警告 0。MSVC `/W4` で警告になる書き方も避けている。課題3 の記録 2 で `C4244`（`double` → `int`），課題2 の `C4013`（暗黙の宣言）の原因を説明 |
| 自分の言葉で，処理の流れと使った型を説明できる | 課題1 の考察（宣言 → コンパイル → リンク），課題4 の `Vector`・`Matrix` と値渡し，発展2 の `size_t`・`const void *`・`long` から `int` への変換 |
| 1 つの実行アプリに `main` が 1 つだけあり，必要な `.c` がすべてビルド対象になっている | `SplitCalc`（`main.c`＋`calc.c`），`VectorCalc`（3 つの `.c`），`SortModule`（2 つの `.c`），`CalcApp`（`main.c`＋`CalcLib` の参照）。課題3 の除外・重複の実験 |
| 意図的に作ったエラーと前処理用の設定を元に戻し，最後のビルドが成功した | 課題3 のビルド記録の「復旧後の成功」列，課題4 のガード・`/P` の後のリビルド。リポジトリではエラー版を `_BuildErrors/` に分け，提出用のフォルダは正常版だけ |
| 宣言・定義・呼び出しと，コンパイル・リンクの関係を説明できる | 課題1 の対応表・考察，課題2 の 3 か所，課題3 の段階の切り分け，発展1 の更新の 4 作業 |
| ヘッダのガード名を使い回さず，必要な型をヘッダ自身で取り込んでいる | `PL1_CALC_H`・`PL1_VECTOR_H`・`PL1_MATRIX_H`・`PL1_INTLIB_H` がヘッダごとに異なる。`matrix.h` が `vector.h` を，`intlib.h` が `stddef.h` を自分で読む（課題4 の独立性の実験） |

---

## このリポジトリでのビルド・テスト

```sh
B=/tmp/build-week12
cmake -S . -B $B -G Ninja -DSOFTPRAC_WEEKS=week12 -DSOFTPRAC_WERROR=ON -DSOFTPRAC_SANITIZE=ON
cmake --build $B && ctest --test-dir $B --output-on-failure
```

- 結果: 34 テストすべて成功（GCC 13＋ASan/UBSan，Clang 18 とも警告 0）。
- `SortModule` を別の引数で試すときは，Visual Studio（フォルダーを開く）では [run.args](SortModule/run.args) を書き換えて `python tools/gen_launch_vs.py` を実行するか，
  VS Code では「開いている課題を引数つきで実行」の `args` を書き換える。空文字列の引数は Visual Studio のコマンド引数では `""` と入力する。
- `_BuildErrors/` のエラー版を GCC で再現するには，`_BuildErrors/split/` で課題3 の「GCC で実際に出た診断」のコマンドを，`_BuildErrors/` で `gcc -std=c17 -c noguard/vector_main.c` と `gcc -std=c17 -c noinclude/vector_main.c` を実行する。
