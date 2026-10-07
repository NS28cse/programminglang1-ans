# 第9回 演習 解答・解説（ポインタ2）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex09/>（原文: [docs/ex09.md](https://github.com/t-yokoga/softprac1/blob/main/docs/ex09.md)）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec09/>（例題: `docs/sample/09/double_pointer.c`，`matrix.c`）

## プロジェクト一覧

| 課題 | プロジェクト | ソース | テスト |
| --- | --- | --- | ---: |
| 課題1（見つからない場合・同点・失敗時・二重ポインタの代入） | `FindMax` | [double_pointer.c](FindMax/double_pointer.c)（講義の例題そのもの） | 9（本体 1，書き換え版 8） |
| 課題1（値を返す版と場所を返す版） | `ReturnMaximum` | [return_maximum.c](ReturnMaximum/return_maximum.c) | 4（本体 1，書き換え版 3） |
| 課題2 表示順を変更する | `Names` | [names.c](Names/names.c)，途中版 [versions/names_direct.c](Names/versions/names_direct.c) | 6（本体 1，書き換え版・途中版 5） |
| 課題3 行ごとの平均 | `MatrixMean` | [matrix.c](MatrixMean/matrix.c) | 10（本体 1，書き換え版 9） |
| 課題4 二次元配列の行を交換する | `SwapRows` | [swap_rows.c](SwapRows/swap_rows.c) | 7（本体 1，書き換え版 6） |
| 発展1 長さが異なる行を扱う | `RaggedRows` | [ragged_rows.c](RaggedRows/ragged_rows.c)，例 [versions/animal.c](RaggedRows/versions/animal.c)・[versions/letters.c](RaggedRows/versions/letters.c) | 5（本体 1，書き換え版・別の例 4） |
| 発展2 型の説明 | `ArrayTypes`（※） | [array_types.c](ArrayTypes/array_types.c) | 1 |
| 合計 | | | 42 |

※ 発展2 には演習ページでプロジェクト名の指定がありません。型と `sizeof` を実際に確かめるため，解答用に `ArrayTypes` という名前で作りました（README の説明だけでも解答は成り立ちます）。
`ReturnMaximum`・`Names`・`SwapRows`・`RaggedRows` もソース名の指定がないため，プロジェクト名を小文字と `_` で書いた名前（`return_maximum.c` など）にしています。

### この回の解答の作り方（テストについて）

- 演習ページに「今回の入力はソース中の初期値です．数値や添字を変更するたびに再ビルドします」とあるので，プログラムは入力を読みません。
- **本体**（各フォルダのソース）は配布コード・演習ページの表示どおりにしました。`FindMax` は講義の例題そのもの，`ReturnMaximum` と `RaggedRows` は演習ページの「期待する表示」と 1 文字も違わない出力です。テストは `tests/basic.out` です。
- 演習ページの「`n` を 0 にする」「配列を変える」「断片を追加する」などの**書き換え**は，学生と同じ書き換えを CMake が行う `softprac_add_variant`（各フォルダの `CMakeLists.txt`）で別の実行ファイルとしてビルドし，`variants/tests/<ケース名>.out` と比べてテストしています。
  関数へ分ける前の途中版や，演習ページの別の小さな例（`dog`/`cat` など）は `versions/` に置き，置き換えなしでビルド・テストしています。
  README の「variant `n0`」などはこのケース名です。各節の実行結果は，本体・各 variant を実際に実行した出力（＝テストの期待値）です。
- 範囲外アクセスになる書き換え（`n=4`，`rows=3`，長さを交換しない行の交換，`int **` への変換など）は演習ページの指示どおり実行せず，型と図で説明しています。
- 実行環境: Linux x64（GCC 13，`-Wall -Wextra -Wpedantic -Werror`，AddressSanitizer/UBSan）で 42 テスト成功。Clang 18（`-Werror`）でも警告 0・42 テスト成功を確認しました。
  表示する内容に処理系依存の値を含めていないので，Windows（MSVC，x64）でも同じ表示になります。可変長配列（VLA）は使っていません（MSVC は非対応）。
  MSVC の診断番号（C4047 など）は MSVC で実行して確認したものではなく，「例（未確認）」として載せています。
- `int *rows[] = {row0, row1};`，`char *editable[] = {city0, city1};`，`char *letters[] = {&first, &second};` のように自動変数のアドレスで配列を初期化する書き方は C99 以降の標準 C で，どれも演習ページ・講義の断片どおりです。MSVC が古い既定で出す C4204/C4221（非定数の集成体初期化・自動変数のアドレスでの初期化）は `/std:c11` 以降では出ません（未確認）。

---

## 課題1　見つからない場合（`FindMax`）

### 要点

- `find_max(int a[], int n, int **out)` は，呼び出し元の**ポインタ変数 `answer` の場所** `&answer` を受け取り，`*out = best;` で `answer` 自体を書き換える（二重ポインタ）。
- 戻り値は成功・失敗。`*answer` を読むのは**成功したときだけ**。`n<=0` のときは要素を読まず，`*out = NULL` にして 0 を返す。
- 同点の扱い（`>` なら最初，`>=` なら最後）は比較演算子で決まる仕様である。

### 解答コード

[FindMax/double_pointer.c](FindMax/double_pointer.c) は講義の例題 `double_pointer.c` そのものです（コメントだけ追加）。演習ページの各書き換えは [FindMax/CMakeLists.txt](FindMax/CMakeLists.txt) の variant です。

| variant | 例題に対する書き換え |
| --- | --- |
| `n1` / `n0` / `n_m1` | `find_max(a, 3, &answer)` の 3 を 1，0，−1 に（`n1` は `a[0]` の表示も追加） |
| `tie` | 配列を `{12, 12, 4}` にし，`if` の本体に `printf("first=%d\n", answer == &a[0]);` を追加 |
| `tie_ge` | `tie` に加えて，条件 `a[i] > *best` を `a[i] >= *best` に |
| `out_first` | `*out = best;` を `*out = &a[0];` に |
| `stale` | `answer` の初期値を `&a[1]` にし，`n=0` で呼び，`printf("answer==NULL: %d\n", answer == NULL);` を追加 |
| `trace` | 二重ポインタの断片を `main` 内（名前の表示の後）に追加 |

```c
int find_max(int a[], int n, int **out)
{
    *out = NULL;  // 失敗したときに以前の結果を残さない
    if (n <= 0) { return 0; }
    int *best = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > *best) { best = &a[i]; }  // > なので，同点なら最初の要素のまま
    }
    *out = best;
    return 1;
}
```

### 実行結果（本体 = 講義の例題）

```text
max=12
a[1]=99
blue
green
red
```

講義ページの表示と同じです。

### `n=0` のとき `answer` と戻り値はどうなるか

**戻り値は 0（失敗），`answer` は `NULL` です。** `find_max` は最初に `*out = NULL;`（= `answer = NULL`）を実行し，`n <= 0` なので要素を 1 つも読まずに `return 0;` します。
`main` の `if` の本体は実行されないので，`*answer` を読むことも `*answer = 99;` も行いません（`NULL` を間接参照しない）。

variant `n0`（`find_max(a, 0, &answer)`）の実行結果。`max=` の行がなく，`a[1]` は 12 のままです。

```text
a[1]=12
blue
green
red
```

### 検索範囲と同点の扱い（表）

検索に使われる要素を `[ ]` で囲むと次のとおりです（元の配列は `{7, 12, 4}`）。

| `n` | 検索に使われる要素 |
| ---: | --- |
| 3 | `[7, 12, 4]` |
| 1 | `[7], 12, 4` |
| 0 | `7, 12, 4`（囲む要素なし） |
| −1 | `7, 12, 4`（囲む要素なし） |

| `n` | 成功・失敗 | 検索結果 | `*answer = 99;`の影響 | 確かめた実行 |
| ---: | --- | --- | --- | --- |
| 3 | 成功 | `a[1]`の12 | `a[1]`が99 | 本体: `max=12`，`a[1]=99` |
| 1 | 成功 | `a[0]`の7 | `a[0]`が99，`a[1]`は12 | variant `n1`: `max=7`，`a[0]=99`，`a[1]=12` |
| 0 | 失敗 | `answer`は`NULL` | 代入を実行しない | variant `n0`: `max=` の行なし，`a[1]=12` |
| −1 | 失敗 | `answer`は`NULL` | 代入を実行しない | variant `n_m1`: `max=` の行なし，`a[1]=12` |

variant `n1` の実行結果（`a[0]` の表示を追加した版）:

```text
max=7
a[0]=99
a[1]=12
blue
green
red
```

variant `n_m1` の実行結果（`n0` と同じ）:

```text
a[1]=12
blue
green
red
```

- `n=1` では `a[0]` だけが検索範囲なので，最大は 7 です。プログラム末尾の `a[1]` の表示は検索結果とは別で，`n=1` のときは 12 のままです。
- `n=4` は試しません。`find_max` が受け取るのは先頭のアドレスと `n` だけで，配列の実際の長さ（3）を知る方法がないため，`n=4` を渡すと `a[3]`（範囲外）を読んでしまいます（未定義動作）。
  負の `n` を `n <= 0` で失敗として扱えるのは「値だけで判定できる」からで，大きすぎる `n` を検出できることとは別です。`n` が実際の要素数以下であることは**呼び出し側が守る契約**です。

**同点（`{12, 12, 4}`，`n=3`）**: 条件が `a[i] > *best` なので，`a[1]` の 12 は `*best`（`a[0]` の 12）より大きくなく，候補は `a[0]` のままです。`first=1` になり，99 が入るのは `a[0]` なので `a[1]=12` です。
variant `tie` の実行結果:

```text
max=12
first=1
a[1]=12
blue
green
red
```

条件を `>=` にすると，同じ値でも候補を更新するので `a[1]` が選ばれ，`first=0`，`a[1]=99` になります。variant `tie_ge` の実行結果:

```text
max=12
first=0
a[1]=99
blue
green
red
```

確認後は `>` に戻します（本体は `>`）。

### 説明すること: `*out = best;` を `*out = &a[0];` に変えたら

**コンパイルは警告なしで通りますが，探索結果 `best` を捨てて常に先頭要素 `a[0]` の場所を返す関数になります。** `&a[0]` も `best` も `int *` なので型は合っています（variant `out_first` は `-Werror` でもビルドできます）。
variant `out_first` の実行結果（全文）。最大値 12 ではなく 7 が表示され，99 が代入されるのも `a[0]` なので `a[1]` は 12 のままです。

```text
max=7
a[1]=12
blue
green
red
```

「ビルドできた」「警告が出ない」ことは仕様どおりであることを意味しません。期待する結果（`max=12`，`a[1]=99`）と比べて確認する必要があります。

### 失敗時に古い結果を残さない

`answer` を最初に `&a[1]` にして `n=0` で呼ぶと，戻り値は 0，`answer` は `NULL` になります。関数の先頭で `*out = NULL;` を実行するので，以前のアドレス `&a[1]` は残りません。
これは `find_max` が採用した仕様で，失敗時に出力先をどうするか（変更しない，`NULL` にするなど）は関数ごとに確認が必要です。variant `stale` の実行結果:

```text
answer==NULL: 1
a[1]=12
blue
green
red
```

- `out` 自体に `NULL` を渡す実験はしません。`find_max` は `*out = NULL;` で `out` が指す先へ書き込むので，`out` は**有効なポインタ変数のアドレス**でなければなりません（契約）。
- `&answer` は「ポインタ変数 `answer` の場所」（`int **`，`out` に渡すもの），`answer` は「検索結果の場所」（`int *`，失敗なら `NULL`）です。「出力として `NULL` を受け取る」ことと「`out` に `NULL` を渡す」ことは別です。

### 値を返す版と，場所を返す版（`ReturnMaximum`）

[ReturnMaximum/return_maximum.c](ReturnMaximum/return_maximum.c)。`max_value`（`n>=1` だけに対応）と `max_pointer`（`n<=0` なら `NULL`）は講義のコードと同じです。

```c
int main(void)
{
    int a[] = {7, 12, 4};
    int saved = max_value(a, 3);      // その時点の最大値のコピー
    int *found = max_pointer(a, 3);   // 元の配列の要素を指す
    if (found != NULL) {
        printf("before=%d %d\n", saved, *found);
        *found = 99;                  // 配列 a が変わる。saved は変わらない
        printf("after=%d %d\n", saved, *found);
    }
    return 0;
}
```

本体の実行結果（演習ページの表示と一致）:

```text
before=12 12
after=12 99
```

| variant | 書き換え | 実行結果 |
| --- | --- | --- |
| `negative` | 配列を `{-7, -12, -4}` に | `before=-4 -4`，`after=-4 99` |
| `pointer_n0` | `max_pointer(a, 3)` を `max_pointer(a, 0)` に（値の版は 3 のまま） | 何も表示しない（出力 0 行） |
| `best_zero` | `{-7, -12, -4}` で，`max_value` の `int best = a[0];` を `int best = 0;` に | `before=0 -4`，`after=0 99`（誤り） |

- **`saved` が 12 のままである理由**: `saved` は `max_value` が返した**値のコピー**で，配列とは独立した `int` 変数です。`*found = 99;` は `found` が指す配列の要素 `a[1]` を変えるだけなので，`saved` には影響しません。
  一方 `found` は元の配列の要素 `a[1]` を指すので，`*found` は 99 になり，配列 `a` も `{7, 99, 4}` に変わります。
  `max_pointer` が返すのは関数内の変数 `best` 自体のアドレスではなく，`best` に保存されている「呼び出し元の配列要素のアドレス」なので，関数が終わっても有効です。
- **`{-7, -12, -4}`**: variant `negative` の実行結果は次のとおりです。

  ```text
  before=-4 -4
  after=-4 99
  ```

- **最大候補を 0 から始めない理由**: 全要素が負のとき，0 より大きい要素がないので候補が更新されず，配列にない 0 を返してしまうからです。先頭要素 `a[0]` から始めれば，必ず配列中の値が答えになります
  （そのため `n>=1` という条件が必要です）。variant `best_zero` の実行結果（`saved` が配列にない 0 になる）:

  ```text
  before=0 -4
  after=0 99
  ```

- **場所を返す版だけ `n=0`**: `max_pointer` は `NULL` を返すので `if` の本体が実行されず，何も表示されません（variant `pointer_n0` の出力は空）。値を返す版の `n` は 3 のままにします。
  `max_value` は空入力に対応しないので，`n=0` を渡すと `a[0]` を読む前提が崩れます（長さ 0 の配列なら範囲外）。値の版に無条件で `n=0` を渡してはいけません。

### 二重ポインタの代入を追う

演習ページの断片を例題の `main` 内に追加した版が variant `trace` です。実行結果（最後の 2 行が断片の表示）:

```text
max=12
a[1]=99
blue
green
red
20 30 1
20 40 1
```

| 実行した行 | `x` | `y` | `p` の指す先 | `pp` の指す先 | 表示 |
| --- | ---: | ---: | --- | --- | --- |
| `int x = 10, y = 30;` | 10 | 30 | — | — | |
| `int *p = &x;` | 10 | 30 | `x` | — | |
| `int **pp = &p;` | 10 | 30 | `x` | `p` | |
| `**pp = 20;` | 20 | 30 | `x` | `p` | |
| `printf(... x, y, p == &x)` | 20 | 30 | `x` | `p` | `20 30 1` |
| `*pp = &y;` | 20 | 30 | `y` | `p` | |
| `**pp = 40;` | 20 | 40 | `y` | `p` | |
| `printf(... x, y, p == &y)` | 20 | 40 | `y` | `p` | `20 40 1` |

```text
pp → p → x        **pp = 20; は矢印を2段たどって x を変える
pp → p → y        *pp = &y;  は1段たどった p の中身（アドレス）を変える
```

`*pp = &y;` は整数をコピーしていません。`p` に保存されたアドレスを変えています。`pp` は最初から最後まで `p` を指したままです。

### 採点のポイント・よくある誤り（課題1）

- `n=0` で `*answer` を読んでいないか（`if` の外で `printf("max=%d\n", *answer);` を書くと `NULL` の間接参照）。「`answer` は `NULL`，戻り値は 0」と両方答えているか。
- 表の `n=1` で「`a[0]` が 99，`a[1]` は 12」まで書けているか（末尾の `a[1]` の表示と検索結果を混同しやすい）。
- 各ケースを毎回例題の初期状態から試しているか（`n` を変えた版で配列を戻し忘れない）。
- `n=4` を実際に試していないか。試して「動いた」ことを根拠にしていないか。負の `n` の検出と大きすぎる `n` の検出の違いを説明できているか。
- 同点で `a[0]` を選ぶ理由を「`>` だから」と比較演算子に結び付けているか。`>=` で `first=0` になることを確認したか。
- `*out = &a[0];` を「エラーにならないから正しい」としていないか。
- `ReturnMaximum` で `saved` を「値のコピー」，`found` を「配列要素の場所」と区別しているか。「関数内の `best` のアドレスを返している」という誤解がないか。
- `&answer` と `answer` の役割の違い，`out` に `NULL` を渡すことと出力が `NULL` になることの違いを説明できているか。
- 二重ポインタの断片で，`*pp = &y;` の後に `x` も 40 になると予測する誤りが多い。

---

## 課題2　表示順を変更する（`Names`）

### 要点

- `const char *names[]` は文字列の**先頭アドレス（ポインタ）を並べた配列**。要素の交換はポインタ値の交換で，文字列本体は移動しない。
- 仮引数の `const char *names[]` は `const char **names` に調整される。
- 表示に `-city` を付けることと，文字列を書き換えることは違う。文字を変えるなら変更可能な `char` 配列を用意する。

### 解答コード

[Names/names.c](Names/names.c)。交換を `swap_names` へ移した最終版で，`main` から `swap_names(names, 0, 2);` と呼び，`main` には元の交換処理を残していません。

```c
void swap_names(const char *names[], int i, int j)
{
    const char *temp = names[i];
    names[i] = names[j];
    names[j] = temp;
}

int main(void)
{
    const char *names[] = {"Tokyo", "Osaka", "Nagoya"};
    swap_names(names, 0, 2);
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", names[i]);
    }
    return 0;
}
```

最初に `main` に直接書いた版（関数へ分ける前の途中版）は [Names/versions/names_direct.c](Names/versions/names_direct.c) で，variant `direct` としてそのままビルド・テストしています。

```c
#include <stdio.h>
int main(void)
{
    const char *names[] = {"Tokyo", "Osaka", "Nagoya"};
    const char *temp = names[0];
    names[0] = names[2];
    names[2] = temp;
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", names[i]);
    }
    return 0;
}
```

| variant | 書き換え |
| --- | --- |
| `direct` | 途中版 `versions/names_direct.c`（置き換えなし） |
| `swap_1_1` | `swap_names(names, 0, 2);` を `swap_names(names, 1, 1);` に |
| `swap_twice` | `swap_names(names, 0, 2);` を 2 回続けて呼ぶ |
| `city` | `printf("%s\n", names[i]);` を `printf("%s-city\n", names[i]);` にし，続けて `printf("%s %zu\n", names[i], strlen(names[i]));` を追加 |
| `editable` | 変更可能な配列 `city0`，`city1` の断片を `main` の最後に追加 |

### 実行結果

本体（`swap_names(names, 0, 2);`）と途中版 `direct` の実行結果（同じ）:

```text
Nagoya
Osaka
Tokyo
```

### 表示順の予測と，長さが違っても交換できる理由

予測（= 実行結果）: `Nagoya`，`Osaka`，`Tokyo`。

```text
交換前                                   交換後（swap_names(names, 0, 2)）
names[0] [*]--> "Tokyo\0"  (6バイト)      names[0] [*]--> "Nagoya\0"
names[1] [*]--> "Osaka\0"  (6バイト)      names[1] [*]--> "Osaka\0"
names[2] [*]--> "Nagoya\0" (7バイト)      names[2] [*]--> "Tokyo\0"
                                         文字列本体（リテラル）の場所と内容は変わらない
```

配列 `names` の各要素は `const char *` という**固定サイズのポインタ値**（x64 では 8 バイト）で，文字列の長さ（6 バイトと 7 バイト）とは関係ありません。
交換するのはこのポインタ値 2 個だけなので，`strlen` で長さを求めたり文字をコピーしたりする必要がありません。文字列本体（文字列リテラル）は元の場所にあり，一切書き換えていません。

### 関数へ分ける（表）

各ケースは初期状態から別々に試します（それぞれ別の variant としてビルド）。

| 呼び出し | 表示の順番 | 確かめた実行 |
| --- | --- | --- |
| `swap_names(names, 0, 2);` | `Nagoya`，`Osaka`，`Tokyo` | 本体 |
| `swap_names(names, 1, 1);` | `Tokyo`，`Osaka`，`Nagoya`（変わらない） | variant `swap_1_1` |
| `swap_names(names, 0, 2);`を2回 | `Tokyo`，`Osaka`，`Nagoya`（2回目の交換で元に戻る） | variant `swap_twice` |

variant `swap_1_1` と `swap_twice` の実行結果（同じ）:

```text
Tokyo
Osaka
Nagoya
```

- `i == j` のときは `temp = names[1]; names[1] = names[1]; names[1] = temp;` となり，同じ値を書き戻すだけなので変わりません（一時変数を使う交換なので安全）。
- **`const char **names` との関係**: 仮引数の配列型は，要素型へのポインタに調整されます。要素型 `T = const char *` について `T names[]` は `T *names`，つまり `const char **names` です。
  どちらで書いても同じ型で，`main` からは配列 `names`（`const char *[3]`）が先頭要素へのポインタ `&names[0]`（`const char **`）に変換されて渡されます。関数内の `names[i] = ...` は呼び出し元の配列の要素を書き換えるので，交換が `main` に反映されます。
  先頭の `const` は「指す先の文字を書き換えない」という意味で，配列に保存したポインタの交換は禁止しません。
- `i`，`j` が 0〜2 であることは呼び出し側の条件です（関数は配列の長さを知らないので検査できません）。

参考: 要素が `char *` の配列（`char *names[] = {s0, s1, s2};`）をこの関数に渡すと，`char **` から `const char **` への変換になり，GCC/Clang は警告します（実際の診断）。

```text
gcc:   warning: passing argument 1 of 'swap_names' from incompatible pointer type [-Wincompatible-pointer-types]
       note: expected 'const char **' but argument is of type 'char **'
clang: warning: passing 'char *[3]' to parameter of type 'const char **' discards qualifiers in nested pointer types [-Wincompatible-pointer-types-discards-qualifiers]
```

多段のポインタでは `char *` → `const char *` と同じようには変換できません。キャストで合わせず，配列を `const char *names[]` と宣言して関数と要素型をそろえます。

### 表示と書き換えを区別する

variant `city` の実行結果:

```text
Nagoya-city
Nagoya 6
Osaka-city
Osaka 5
Tokyo-city
Tokyo 5
```

- `printf("%s-city\n", names[i]);` は，`names[i]` の文字列を表示した**後に** `-city` という別の文字列（書式の一部）を表示しているだけです。続けて `printf("%s %zu\n", names[i], strlen(names[i]))` で表示すると `Nagoya 6` で，元の文字列のままであり，`strlen` にも `-city` の 5 文字は加わっていません。
- 変更可能な配列の例: **予測・結果とも `tokyo tokyo`**。variant `editable` の実行結果（最後の行が断片の表示）:

  ```text
  Nagoya
  Osaka
  Tokyo
  tokyo tokyo
  ```

  `char city0[] = "Tokyo";` はリテラルの内容をコピーして作った**書き換え可能な `char` 配列**です。`editable[0]` は `city0` の先頭を指すので，`editable[0][0] = 't';` は `city0[0]` を変えます。`city0` と `editable[0]` は同じ文字列を表すので，どちらで表示しても `tokyo` です。
  これは `editable` のポインタ値を変える操作ではなく，ポインタの先にある文字を変える操作です（`city1` は変わりません）。既存の `names` と名前が重ならないよう，断片の変数名（`city0`，`city1`，`editable`）はそのまま使えます。

**禁止する実験について**: `names[0]` は文字列リテラルを指しており，リテラルを書き換える動作は未定義です（読み取り専用の領域に置かれて異常終了することもあれば，同じ内容の別のリテラルまで変わることもある）。
`const` を外したりキャストしたりしても，書き込んでよい領域になるわけではありません。また `%s` は終端 `'\0'` まで読むので，文字列の長さより先を `%s` で表示させると範囲外を読みます。これらは実行せず，型と図で説明します。

### 採点のポイント・よくある誤り（課題2）

- 「文字列を交換した」「文字をコピーした」と説明していないか。交換したのはポインタ（アドレス）であることを図で示しているか。
- 表の 3 ケースを**初期状態から別々に**試しているか（`(0,2)` の後に続けて `(1,1)` を試すと結果が違う）。
- `swap_names` を `main` より前に定義しているか。`main` に交換処理が残っていないか。仮引数の `const` を外していないか。
- `const char *names[]` と `const char **names` が同じ型であること，`const` がどこに掛かるかを説明できているか。
- `-city` で文字列が変わったと誤解していないか。`editable[0][0] = 't';` の結果を `Tokyo tokyo` と予測する誤りが多い（同じ配列を見ている）。
- 文字列リテラルへの書き込みを実際に試していないか（試して「動いた／落ちた」で説明していないか）。

---

## 課題3　行ごとの平均（`MatrixMean`）

### 要点

- 二次元配列 `int a[2][COLS]` を関数に渡すと，仮引数は `int (*a)[COLS]`（`int` が `COLS` 個の行へのポインタ）になる。列数は型に含まれ，行数は `rows` として別に渡す。
- 平均は `(double)total / COLS` で求める（整数除算にしない）。
- `sizeof` で行数・列数を求められるのは `main` の実際の配列だけ。

### 解答コード

[MatrixMean/matrix.c](MatrixMean/matrix.c)（例題 `matrix.c` の `enum { COLS = 3 };` と二重ループの形をもとにした最終版）

```c
enum { ROWS = 2, COLS = 3 };
void print_means(int (*a)[COLS], int rows)
{
    for (int r = 0; r < rows; ++r) {
        int total = 0;
        for (int c = 0; c < COLS; ++c) {
            total += a[r][c];
        }
        double mean = (double)total / COLS;  // total / COLS だと整数除算になり小数部分が失われる
        printf("row%d mean=%.2f\n", r, mean);
    }
}
int main(void)
{
    int a[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}};
    print_means(a, ROWS);
    return 0;
}
```

| variant | 本体に対する書き換え |
| --- | --- |
| `rows1` / `rows0` | `print_means(a, ROWS);` を `print_means(a, 1);` / `print_means(a, 0);` に |
| `low_high` / `fraction` | 配列の初期値を `{{0, 0, 0}, {100, 100, 100}}` / `{{1, 1, 2}, {2, 2, 3}}` に |
| `int_division` | `fraction` の配列で `(double)total / COLS` を `total / COLS` に |
| `array_param` | 仮引数を `int (*a)[COLS]` から最初の形 `int a[][COLS]` に |
| `sizeof_check` | `main` に `sizeof` の 4 つの式の確認を追加 |
| `overall` / `overall_rows0` | 全体平均を返す関数 `overall_mean` を追加し，`rows=ROWS` / `rows=0` で呼ぶ |

### 実行結果

本体（元の配列，`rows=2`）の実行結果:

```text
row0 mean=2.00
row1 mean=5.00
```

予測は (1+2+3)/3 = 2，(4+5+6)/3 = 5 です。最初に作る形 `void print_means(int a[][COLS], int rows)` から `int (*a)[COLS]` に変えても出力は変わりません。
`int a[][COLS]` と書いた variant `array_param` の出力が本体とまったく同じであることをテストしています（同じ型を別の書き方で書いただけだからです）。

### 入力を変えて確かめる（表）

| 配列の2行 | `rows` | 出力 | 確かめた実行 |
| --- | ---: | --- | --- |
| {1, 2, 3}，{4, 5, 6} | 1 | `row0 mean=2.00`（1行目だけ。2行目は読まない） | variant `rows1` |
| {0, 0, 0}，{100, 100, 100} | 2 | `row0 mean=0.00`，`row1 mean=100.00`（値の範囲 0〜100 の両端） | variant `low_high` |
| {1, 1, 2}，{2, 2, 3} | 2 | `row0 mean=1.33`，`row1 mean=2.33`（4/3 と 7/3。割り切れない） | variant `fraction` |
| 元の配列 | 0 | 何も表示しない（ループが1回も回らない） | variant `rows0`（出力 0 行） |

variant `rows1`:

```text
row0 mean=2.00
```

variant `low_high`:

```text
row0 mean=0.00
row1 mean=100.00
```

variant `fraction`:

```text
row0 mean=1.33
row1 mean=2.33
```

- `rows=3` は存在しない 3 行目（`a[2]`）へ進むので試しません。関数は実際の行数を知らないので，`rows` が 0〜2 であることは呼び出し側の条件です。
- **整数除算の確認**: `fraction` の配列で `(double)total / COLS` を `total / COLS` に変えた variant `int_division` の実行結果（全文）:

  ```text
  row0 mean=1.00
  row1 mean=2.00
  ```

  元の配列（合計 6 と 15）は 3 で割り切れるので整数除算でも 2.00，5.00 と同じ表示になり，**割り切れない `{1, 1, 2}` のケースでないと誤りに気付けません**。`4 / 3` は `int` 同士の除算で 1 になり，それを `double` に変換しても 1.0 です。
  `%.2f` を `%.6f` にしても 1.000000 で，除算で失った情報は戻りません。
  （`printf("%.2f", total / COLS)` のように `int` を `%f` に直接渡すのは書式と型の不一致で未定義動作になり，GCC は `-Wformat` の警告，MSVC は C4477 の警告（例，未確認）を出します。解答では `double` の変数に代入しているので，`(double)` を外しても警告なしで整数除算の結果だけを比べられます。）

### 配列へのポインタで表す

`void print_means(int (*a)[COLS], int rows)` に変えても出力は同じです。`int a[][COLS]` という仮引数はもともと `int (*a)[COLS]` に調整されるので，同じ型を別の書き方で書いただけです。

括弧を落として `int *a[COLS]` にすると，`a` は「`int *` が `COLS` 個の配列」となり，仮引数としては `int **a` に調整されます。
渡している `a`（`int (*)[3]` に変換される）とは別の型なので，次の診断が出ます（GCC・Clang は実際の出力で `-Werror` ならエラー，MSVC は例（未確認））。この形のまま警告を無視して実行してはいけません。

```text
gcc:   warning: passing argument 1 of 'print_means' from incompatible pointer type [-Wincompatible-pointer-types]
       note: expected 'int **' but argument is of type 'int (*)[3]'
clang: warning: incompatible pointer types passing 'int[2][3]' to parameter of type 'int **' [-Wincompatible-pointer-types]
MSVC（例，未確認）: warning C4047: 'function': 'int **' differs in levels of indirection from 'int (*)[3]'
                    warning C4024: 'print_means': different types for formal and actual parameter 1
```

実行すると，関数は `a[r]` の場所に `int *` が保存されていると解釈し，x64 では `int` 2 個分（8 バイト，例えば 1 と 2）をまとめて 1 つのアドレスとして読みます。そのアドレスの先を読むので，範囲外アクセスや異常終了になります（未定義動作）。

### `sizeof` の確認（表）

| 式 | 意味 | Windows x64（MSVC）・Linux x64 での値 |
| --- | --- | ---: |
| `sizeof a` | `2 * COLS * sizeof(int)`（配列全体，`int` 6 個） | 24 |
| `sizeof a[0]` | `COLS * sizeof(int)`（1 行，`int` 3 個） | 12 |
| `sizeof a / sizeof a[0]` | 行数2 | 2 |
| `sizeof a[0] / sizeof a[0][0]` | 列数3 | 3 |

`main` で 4 つの式を確認した variant `sizeof_check` の実行結果（処理系に依存しないよう，バイト数は式との比較（`1` = 成り立つ）で，行数・列数は商を `%zu` で表示）:

```text
row0 mean=2.00
row1 mean=5.00
sizeof a == 2 * COLS * sizeof(int): 1
sizeof a[0] == COLS * sizeof(int): 1
sizeof a / sizeof a[0] = 2
sizeof a[0] / sizeof a[0][0] = 3
```

バイト数（24，12）は `sizeof(int)` が 4 の処理系での値です。

関数内の仮引数 `a` はポインタ（`int (*)[3]`）なので，`sizeof a / sizeof a[0]` で行数は求まりません。仮引数を `int a[][COLS]` と書いた関数で同じ式を表示した実験（Linux x64）:

```text
in main: sizeof a=24 sizeof a[0]=12 sizeof a / sizeof a[0]=2
in function: sizeof a=8 sizeof a[0]=12 sizeof a / sizeof a[0]=0
```

関数内の `sizeof a` はポインタ 1 個の大きさ（8）で，8 / 12 = 0 という無意味な値になります。GCC は `warning: 'sizeof' on array function parameter 'a' will return size of 'int (*)[3]' [-Wsizeof-array-argument]` を出します。
だから行数は `rows` として別に渡します。

### 行平均と全体平均

variant `overall`（`overall_mean` を追加し `rows=ROWS` で呼ぶ）と `overall_rows0`（`rows=0` で呼ぶ）の実行結果:

```text
row0 mean=2.00
row1 mean=5.00
overall mean=3.50
```

```text
row0 mean=2.00
row1 mean=5.00
overall mean: undefined
```

```c
// 全要素の平均を *mean へ書いて1を返す。rows<=0 は平均が定義できないので0を返す（*mean は変更しない）
int overall_mean(int (*a)[COLS], int rows, double *mean)
{
    if (rows <= 0) { return 0; }
    double sum = 0.0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < COLS; ++c) {
            sum += a[r][c];
        }
    }
    *mean = sum / ((double)rows * COLS);
    return 1;
}
```

- この例の全体平均は (1+2+3+4+5+6) / 6 = 21 / 6 = **3.5**。行平均 2.0 と 5.0 の平均 (2.0+5.0)/2 = 3.5 とも一致しますが，それは**どの行も要素数が 3 で同じ**だからです。行の長さが違うと一致しません（発展1で 3.0 と 3.25 になる例）。
- `overall_mean` は `rows>=1` を条件にし，`double` で合計して `sum / ((double)rows * COLS)` を求めます。`rows=0` では要素がなく平均が定義できないので，0 で割る前に失敗（戻り値 0）とし，呼び出し側が `undefined` と表示します（`find_max` と同じく，成功・失敗を戻り値，結果を出力引数で返す形）。
- 行平均を表示する `print_means` は `rows=0` なら「何も表示しない」で済みますが，平均値を**返す**関数は何かの値を返さなければならないので，空入力の扱い（失敗を返す，前提条件にする）を仕様として決める必要があります。0.0 を返すと「平均が 0」と区別できません。

### 採点のポイント・よくある誤り（課題3）

- 表の 4 行がすべて埋まっているか。特に `rows=0` を「0.00 と表示」としていないか（何も表示しない）。`{1, 1, 2}` を 1.00 としていたら整数除算の誤り。
- `(double)total / COLS` の括弧の位置。`(double)(total / COLS)` は整数除算の後に変換するので誤り。
- `int (*a)[COLS]` と `int *a[COLS]` の違いを「括弧で `a` がまずポインタになるか配列になるか」で説明できているか。警告を無視して実行していないか。キャストで警告を消していないか。
- `sizeof` の表をバイト数だけで答えていないか（式で答える）。関数内で `sizeof a / sizeof a[0]` を使っていないか。
- `rows=3` を試していないか。全体平均で `rows=0` のとき 0 で割っていないか。
- `COLS` を `const int` や関数の引数（VLA）にしていないか（MSVC では VLA が使えない）。

---

## 課題4　二次元配列の行を交換する（`SwapRows`）

### 要点

- `char names[3][9]` は 27 個の `char` が連続した領域。各行は配列なので `names[i] = names[j];` とは書けず，9 個の `char` を 1 つずつ交換する。
- 終端や初期化で 0 になった残りも含めて**固定幅全体**を交換するので，長さの違う文字列も正しく入れ替わる。
- 行の開始位置（アドレス）は変わらず，そこに保存された内容が変わる（課題2のポインタ交換との違い）。

### 解答コード

[SwapRows/swap_rows.c](SwapRows/swap_rows.c)

```c
enum { ROWS = 3, WIDTH = 9 };

void swap_rows(char names[][WIDTH], int i, int j)
{
    for (int c = 0; c < WIDTH; ++c) {
        char temp = names[i][c];
        names[i][c] = names[j][c];
        names[j][c] = temp;
    }
}
```

`main` は `char names[ROWS][WIDTH] = {"toyama", "ishikawa", "fukui"};` を表示し，`swap_rows(names, 1, 2);` の後にもう一度表示します。
`print_rows` は各行の 9 要素を表示し（値 0 の `char` は `0` と表示），続けて `[ ]` の中に文字列として表示します。

| variant | 本体に対する書き換え |
| --- | --- |
| `same_row` | `swap_rows(names, 1, 2);` を `swap_rows(names, 1, 1);` に |
| `twice` | `swap_rows(names, 1, 2);` を 2 回続けて呼ぶ |
| `empty_fukui` | 初期値の `"fukui"` を `""` に |
| `row_start` | 交換前に `char *row1 = names[1];` を保存し，交換後に `row1 == names[1]` と `row1` を表示 |
| `until_terminator` | `swap_rows` のループを `c < WIDTH` から `c < 6`（`fukui` の終端まで）に（誤り） |
| `fukuiawa` | `swap_rows` の本体を `for (int c = 0; c < 5; ++c) { names[i][c] = names[j][c]; }` に（5 文字だけ上書き，誤り） |

### 実行結果

本体の実行結果:

```text
before:
0: t o y a m a 0 0 0  [toyama]
1: i s h i k a w a 0  [ishikawa]
2: f u k u i 0 0 0 0  [fukui]
after:
0: t o y a m a 0 0 0  [toyama]
1: f u k u i 0 0 0 0  [fukui]
2: i s h i k a w a 0  [ishikawa]
```

予測（= 実行結果）: 交換後は `toyama`，`fukui`，`ishikawa` の順です。

### 交換前後の内容（表）

| 行 | 交換前の9要素 | 交換後の9要素 |
| --- | --- | --- |
| 0 | `t o y a m a 0 0 0` | `t o y a m a 0 0 0` |
| 1 | `i s h i k a w a 0` | `f u k u i 0 0 0 0` |
| 2 | `f u k u i 0 0 0 0` | `i s h i k a w a 0` |

表の 0 は文字 `'0'` ではなく値 0 の `char`（`'\0'`）です。`ishikawa` は 8 文字なので終端を含めてちょうど 9 個，`toyama`・`fukui` の残りは初期化で 0 になります。

### 課題2（ポインタ配列）との違いを図で

```text
課題4: char names[3][9]（27個の char が連続。行の場所は固定）
         names[1] の位置                 names[2] の位置
交換前:  [i s h i k a w a 0]             [f u k u i 0 0 0 0]
交換後:  [f u k u i 0 0 0 0]             [i s h i k a w a 0]
         ↑ 同じ場所。中身の9個の char が入れ替わった（9回の交換）

課題2: const char *names[3]（ポインタが3個。文字列本体は別の場所）
交換前:  names[0] [*]--> "Tokyo"         names[2] [*]--> "Nagoya"
交換後:  names[0] [*]--> "Nagoya"        names[2] [*]--> "Tokyo"
         ↑ 文字列本体は動かない。矢印（ポインタ値）だけが入れ替わった（ポインタ代入3回）
```

variant `row_start` の実行結果の最後の行は `row1 == names[1]: 1, row1 = fukui` です。交換前に `char *row1 = names[1];` として保存した 2 行目の開始位置が交換後も `names[1]` と同じで，その位置の内容が `fukui` に変わったことを示しています。

### 終端も交換する理由

- 短い `fukui` の 5 文字だけを `ishikawa` の先頭へ上書きし，終端を書かないと，`ishikawa` の残り `awa` と終端が残ります。variant `fukuiawa` の実行結果の `after:` 以降:

  ```text
  after:
  0: t o y a m a 0 0 0  [toyama]
  1: f u k u i a w a 0  [fukuiawa]
  2: f u k u i 0 0 0 0  [fukui]
  ```

- `fukui` の終端までの 6 個だけを交換すると，3 行目は `ishika` になり，`ishikawa` の 7〜8 文字目 `wa` が移りません。2 行目には終端の後ろに `w a` が残り `f u k u i 0 w a 0` となります（`%s` では見えません）。variant `until_terminator` の実行結果の `after:` 以降:

  ```text
  after:
  0: t o y a m a 0 0 0  [toyama]
  1: f u k u i 0 w a 0  [fukui]
  2: i s h i k a 0 0 0  [ishika]
  ```

- 固定幅 `WIDTH` 全体（終端と残りの 0 を含む 9 個）を交換すれば，長さにかかわらず両方の行が正しく入れ替わります（本体）。

### 各ケース（別々に確認）

| ケース | 結果 | 理由 | 確かめた実行 |
| --- | --- | --- | --- |
| `swap_rows(names, 1, 1);` | 変わらない | 同じ要素を `temp` 経由で書き戻すだけ | variant `same_row` |
| `swap_rows(names, 1, 2);` を2回 | 元に戻る | 2回目で同じ 9 個をもう一度入れ替える | variant `twice` |
| 初期値の `fukui` を `""` にして1回交換 | 2行目が空行，3行目が `ishikawa` | `""` の行は 9 個すべて 0。固定幅交換なので 0 も移る | variant `empty_fukui` |

variant `same_row` と `twice` の `after:` 以降（交換前と同じ）:

```text
after:
0: t o y a m a 0 0 0  [toyama]
1: i s h i k a w a 0  [ishikawa]
2: f u k u i 0 0 0 0  [fukui]
```

variant `empty_fukui` の実行結果:

```text
before:
0: t o y a m a 0 0 0  [toyama]
1: i s h i k a w a 0  [ishikawa]
2: 0 0 0 0 0 0 0 0 0  []
after:
0: t o y a m a 0 0 0  [toyama]
1: 0 0 0 0 0 0 0 0 0  []
2: i s h i k a w a 0  [ishikawa]
```

### 行の代入ができないこと

`names[1] = names[2];` と書くと，配列（行）には代入できないのでコンパイルエラーです（GCC・Clang は実際の診断，MSVC は例（未確認））。

```text
gcc:   error: assignment to expression with array type
clang: error: array type 'char[9]' is not assignable
MSVC（例，未確認）: error C2106: '=': left operand must be l-value
```

### 比較すること

| | ポインタ配列（課題2） | 二次元配列の行交換（課題4） |
| --- | --- | --- |
| 交換の操作 | ポインタ代入 3 回（長さに無関係で一定） | `WIDTH` 回（9 回）の反復で 9 個の `char` を交換 |
| 文字列本体 | 動かない（別の場所にある） | 動く（内容がコピーされる） |
| 本体の領域 | 文字列ごとに別の場所。連続とは限らない | 27 個の `char` が連続した固定幅の領域 |
| 文字の書き換え | リテラルを指すなら不可（`const`） | 可能（配列の要素） |
| 短い文字列 | 必要な分だけ（終端まで） | 短くても 9 個分を使う |

どちらも「表示順を入れ替える」目的に使えますが，データ構造と操作の費用（交換の回数，領域の使い方）が異なります。

### 採点のポイント・よくある誤り（課題4）

- 行のアドレスを入れ替えようとしていないか（`names[i] = names[j];` はエラー，`char *` 配列に作り替えるのは課題の趣旨と違う）。
- 交換の範囲が `WIDTH` 全体か。`strlen` までや短い方の長さまでしか交換していないと，`fukuiawa` のような表示になる。
- 表の 0 を文字 `'0'` と混同していないか。
- 「行の開始位置は変わらず，内容が変わる」と「課題2はポインタが変わり，本体は動かない」を図で対比できているか。
- 3 ケース（同じ行，2回，空文字列）を初期状態から別々に確かめているか。
- 幅 9 を `"ishikawa"` の 8 文字にしていないか（終端が入らない）。

---

## 発展1　長さが異なる行を扱う（`RaggedRows`）

### 要点

- 配列本体（`row0`，`row1`），先頭を集めたポインタ配列（`rows`），長さの配列（`lengths`）の 3 種類を区別する。
- ポインタ配列は `int **` で指せる（`p[1]` の場所に実際に `int *` がある）。二次元配列 `int a[2][3]` を `int **` で指すのとは違う。
- 行のポインタを交換するときは長さも一組で交換する。

### 解答コード

[RaggedRows/ragged_rows.c](RaggedRows/ragged_rows.c)

```c
int main(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int *rows[] = {row0, row1};  // 行の先頭アドレスを集めただけで，内容はコピーしない
    int lengths[] = {3, 2};      // 長さは型に含まれないので別に管理する
    int **p = rows;
    for (int r = 0; r < 2; ++r) {
        int sum = 0;
        for (int c = 0; c < lengths[r]; ++c) {
            sum += p[r][c];
        }
        printf("row%d sum=%d\n", r, sum);
    }
    p[1][0] = 40;  // p[1] は row1 を指すので row1[0] が変わる
    printf("original=%d\n", row1[0]);
    return 0;
}
```

| variant | 書き換え |
| --- | --- |
| `swap_with_lengths` | 反復処理の前（`int **p = rows;` の直後）に，演習ページの交換の断片（`rows` と `lengths` を一組で交換）を追加 |
| `means` | `p[1][0] = 40;` の前に，全要素の合計・個数と行平均の和を集計して表示する処理を追加 |
| `animal` / `letters` | 二重ポインタの別の使い方の 2 つの断片（[versions/animal.c](RaggedRows/versions/animal.c)，[versions/letters.c](RaggedRows/versions/letters.c)。どちらも変数名 `p` を使うので別のプログラムにした） |

### 実行結果

本体の実行結果（演習ページの表示と一致）:

```text
row0 sum=6
row1 sum=9
original=40
```

### 3 種類の配列とポインタの図

```text
配列本体（別々の領域）       ポインタ配列 rows           長さの配列 lengths
row0: [1][2][3]  <--------- rows[0] [*]                 lengths[0] [3]
row1: [4][5]     <--------- rows[1] [*]                 lengths[1] [2]
                               ^
p ---------------------------- +  （p は rows[0] を指す。int **）
```

- `p[1]` は `rows[1]` に保存された `int *`（`row1` の先頭アドレス），`p[1][0]` は `row1[0]` です。
- `rows` を用意しても `row0`・`row1` の内容はコピーされません。だから `p[1][0] = 40;` は `row1[0]` そのものを変え，`original=40`（`row1[0]` の表示）になります。
- 長さはポインタに含まれないので `lengths` で管理します。`p[1][2]` は 2 要素しかない `row1` の範囲外です。

### 長さも一緒に交換する

**予測・結果**: `row0 sum=9`，`row1 sum=6`，`original=4`。variant `swap_with_lengths` の実行結果:

```text
row0 sum=9
row1 sum=6
original=4
```

交換後は `rows[0]` が `row1`（長さ 2），`rows[1]` が `row0`（長さ 3）を指し，`lengths` も `{2, 3}` になるので，1 行目の合計は 4+5 = 9，2 行目は 1+2+3 = 6 です。
`p[1]` は `row0` を指すので `p[1][0] = 40;` は `row0[0]` を変え，`row1[0]` は 4 のままです（`original=4`）。配列本体は動かず，`rows` のポインタと `lengths` の値だけが入れ替わっています。

```text
交換後（両方を交換）              ポインタだけ交換した場合（誤り。実行しない）
rows[0] [*]--> row1 [4][5]        rows[0] [*]--> row1 [4][5][?]   lengths[0] = 3
lengths[0] = 2                                           ^ row1[2] は範囲外
rows[1] [*]--> row0 [1][2][3]     rows[1] [*]--> row0 [1][2][3]   lengths[1] = 2（3 個目を読まない）
lengths[1] = 3
```

ポインタだけを交換すると，`r=0` のループが `c = 0, 1, 2` まで進み，`p[0][2]`，つまり **`row1[2]`（2 要素の配列の範囲外）** を読みます（未定義動作）。逆に `row0` は 2 要素しか読まれず，合計も誤ります。
ポインタと長さは**一組のデータ**として，必ず同時に交換します。

### 全体の平均と行平均の平均

variant `means` の実行結果:

```text
row0 sum=6
row1 sum=9
all elements: 15 / 5 = 3.00
mean of row means = 3.25
original=40
```

交換前の全要素の平均は (1+2+3+4+5) / 5 = 15 / 5 = **3.0** です。行平均は 6/3 = 2.0 と 9/2 = 4.5 で，その単純な平均 (2.0+4.5)/2 = 3.25 は全体の平均と一致しません。
要素数の違う行を同じ重みで平均してしまうためです。各行の合計（`total`）と個数（`count`）を集計してから割ります。

### 二重ポインタの別の使い方

variant `animal` と `letters` の実行結果:

```text
dog
cat
```

```text
a
b
```

1. **予測・結果: `dog`，`cat`**。`p` は**ポインタ変数 `animal` 1 個**を指します。`*p` は `animal` なので最初は `dog`。`*p = "cat";` は `animal` の指す先を別のリテラル `"cat"` に変えるので，`animal` を表示すると `cat` です。
   `"dog"` という文字列の中身は変わっていません。`p` は 1 個の変数を指すだけなので，`p + 1` や `p[1]` のように進めて使ってはいけません。
2. **予測・結果: `a`，`b`**。`letters` は 2 個のポインタの配列で，各要素は**1 文字だけ**（`first`，`second`）を指します。`p = letters` は先頭要素 `letters[0]` を指し，`p[i]` は `letters[i]`，`*p[i]` は `*(p[i])` なので `first`・`second` の文字です。
   `letters[i]` は終端のある文字列を指していないので，`%s` に渡すと `'\0'` を探して範囲外を読みます。`%c` で 1 文字ずつ表示します。

| 二重ポインタの直接の対象 | その先 | 例 |
| --- | --- | --- |
| ポインタ変数 1 個 | 文字列の先頭 | `p = &animal` |
| ポインタ配列の要素 | 1 個ずつの文字 | `p = letters` |
| ポインタ配列の要素 | 配列の先頭（長さは別管理） | `p = rows` |

型が同じ二重ポインタでも，扱える要素数や終端の有無は型からは分かりません。

### 採点のポイント・よくある誤り（発展1）

- 3 種類（本体・ポインタ配列・長さ）を図で区別しているか。「`rows` を作ると行がコピーされる」という誤解がないか。
- 交換後の予測で `original` を 40 としていないか（`p[1]` は `row0` を指すので変わるのは `row0[0]`）。
- 長さを交換しない場合に範囲外になる添字（`row1[2]`）を具体的に示しているか。実行して確かめていないか。
- 平均を 3.25 としていないか。
- `letters` の例で `%s` を使っていないか。`*p[i]` を `(*p)[i]` と読み違えていないか（`(*p)[1]` は `first` の次を読む範囲外）。
- `int *rows[] = {{1, 2, 3}, {4, 5}};` のように本体を作らずに初期化しようとしていないか。

---

## 発展2　型の説明（`ArrayTypes`）

### 解答コード

[ArrayTypes/array_types.c](ArrayTypes/array_types.c)。各式の型は「その型の変数を警告なしで初期化できること」（`-Werror` でビルドが通ること）で確かめ，`sizeof` は式との比較で表示します。

```c
int (*row_ptr)[3] = a + 0;      // 1行（int 3個）を1単位とするポインタ
int *int_ptr = a[0] + 0;        // int 1個を1単位とするポインタ
int (*whole)[2][3] = &a;        // 配列全体を指す
int (*first_row)[3] = &a[0];    // 1行を指す
int *first_int = &a[0][0];      // 整数1個を指す
int (*q)[3] = a;
int (**qq)[3] = &q;             // q というポインタ変数自身を指す
int **pp = rows;                // ポインタ配列なら int ** で指せる
```

### 実行結果

```text
sizeof a == 2 * 3 * sizeof(int): 1
sizeof rows == 2 * sizeof(int *): 1
sizeof a[0] == 3 * sizeof(int): 1
sizeof rows[0] == sizeof(int *): 1
(row_ptr + 1) - row_ptr = 1, sizeof *row_ptr == 3 * sizeof(int): 1
(int_ptr + 1) - int_ptr = 1, sizeof *int_ptr == sizeof(int): 1
sizeof *whole == sizeof a: 1
sizeof *first_row == 3 * sizeof(int): 1
sizeof *first_int == sizeof(int): 1
*qq == a: 1, (*qq)[1][2] = 6
same start: 1 1 1 1
&q is not &a: (void *)qq == (void *)whole is 0
a[1][2]=6 rows[1][2]=6 pp[1][2]=6
 flat[0]=1 flat[1]=2 flat[2]=3
 flat[3]=4 flat[4]=5 flat[5]=6
```

### `int a[2][3];` と `int *rows[2];` の `sizeof`

| 宣言 | `sizeof` が数えるもの | 式 | Windows x64・Linux x64 |
| --- | --- | --- | ---: |
| `int a[2][3];` | `int` の本体 6 個（2 行 × 3 列） | `2 * 3 * sizeof(int)` | 24 |
| `int *rows[2];` | ポインタ 2 個だけ（指す先の `int` は数えない） | `2 * sizeof(int *)` | 16 |
| `a[0]` | 1 行（`int` 3 個） | `3 * sizeof(int)` | 12 |
| `rows[0]` | ポインタ 1 個 | `sizeof(int *)` | 8 |

32 ビットの Windows（x86）では `sizeof(int *)` が 4 なので，`sizeof rows` は 8 になります。`rows` を使うには，別に配列本体も必要です。

### アドレスが似ていても型は違う（表）

`int a[2][3] = {{1, 2, 3}, {4, 5, 6}};` のとき。`sizeof a` と `&a` では `a` は配列のまま（変換されない）で，それ以外の通常の式では `a` は先頭要素（1 行目）へのポインタ `int (*)[3]` に変換されます。

| 式 | 型 | 解答欄で説明すること |
| --- | --- | --- |
| `a + 0` | `int (*)[3]` | `int` 3 個の **1 行**を 1 単位とするポインタ。`+1` で次の行へ（`3 * sizeof(int)` バイト先） |
| `a[0] + 0` | `int *` | **`int` 1 個**を 1 単位とするポインタ。`a[0]`（`int [3]`）が先頭要素へのポインタに変換される |
| `&a` | `int (*)[2][3]` | 2 行 3 列の**配列全体**を指す。`&` の対象なので `a` は変換されない。`&a + 1` は配列全体の直後（間接参照不可） |
| `&a[0]` | `int (*)[3]` | **1 行**（`a[0]`）を指す。`a + 0` と同じ型・同じ値 |
| `&a[0][0]` | `int *` | **整数 1 個**（`a[0][0]`）を指す。`a[0] + 0` と同じ型・同じ値 |
| `&q`（`int (*q)[3] = a;`） | `int (**)[3]` | ポインタ変数 `q` 自身を指す。`&a` とは別物 |

- 実行結果の `same start: 1 1 1 1` は，`void *` に変換して比べた 4 組（`&a` と `&a[0]`，`&a[0]` と `&a[0][0]`，`a + 0` と `a[0] + 0`，`a + 0` と `&a`）がすべて等しいことを示します。4 組がつながっているので，`&a`・`&a[0]`・`&a[0][0]`・`a + 0`・`a[0] + 0` の 5 つはどれも同じ位置（格納領域の先頭）です。しかし型（`+1` で進む単位，`*` で得られるもの）は違います。
- `(row_ptr + 1) - row_ptr = 1` と `(int_ptr + 1) - int_ptr = 1`: ポインタの差はバイト数ではなく，指す型の要素数です。`row_ptr + 1` は 12 バイト先，`int_ptr + 1` は 4 バイト先ですが，どちらも差は 1 です。
- `&q is not &a: ... is 0`: `&q` は `q` という**別の変数の場所**で，配列の場所 `&a` とは違います。`*qq` は `q` で，`*qq == a` は 1（`q` が `a` の先頭行を指している）です。

アドレスを `%p` で表示した参考例（Linux x64 の 1 回の実行。値は実行ごとに変わり，テストにはしていません）:

```text
&a       = 0x7ffdc0673b90
a + 0    = 0x7ffdc0673b90
&a[0]    = 0x7ffdc0673b90
a[0] + 0 = 0x7ffdc0673b90
&a[0][0] = 0x7ffdc0673b90
&q       = 0x7ffdc0673b88
a + 1    = 0x7ffdc0673b9c
a[0] + 1 = 0x7ffdc0673b94
&a + 1   = 0x7ffdc0673ba8
sizeof a=24 sizeof a[0]=12 sizeof(int *)=8
```

先頭の 5 つは同じ値ですが，`+1` すると `a + 1` は 0x0c（12）バイト，`a[0] + 1` は 4 バイト，`&a + 1` は 0x18（24）バイト先になり，型の違いが「1 単位の大きさ」の違いとして現れます。

**`int **` では指せない**: `int **bad = a;` や `int **bad2 = &a;` は型が違うので診断が出ます（GCC・Clang は実際の出力，MSVC は例（未確認））。

```text
gcc:   warning: initialization of 'int **' from incompatible pointer type 'int (*)[3]' [-Wincompatible-pointer-types]
gcc:   warning: initialization of 'int **' from incompatible pointer type 'int (*)[2][3]' [-Wincompatible-pointer-types]
clang: warning: incompatible pointer types initializing 'int **' with an expression of type 'int[2][3]' [-Wincompatible-pointer-types]
MSVC（例，未確認）: warning C4047: 'initializing': 'int **' differs in levels of indirection from 'int (*)[3]'
```

`int **` は「その場所に `int *` が保存されている」と解釈する型です。二次元配列の先頭には `int` の 1, 2, 3 … が並んでいるだけで，ポインタは保存されていません。
一方，`int *rows[2] = {a[0], a[1]};` のようにポインタ配列を作れば，`rows[1]` の場所に実際に `int *` があるので `int **pp = rows;` で指せます（実行結果の `rows[1][2]=6 pp[1][2]=6`）。

### 連続性と範囲

- `int *p = &a[0][0];` で `p[0]`〜`p[5]` を走査しないのは，`p` が指すのは 1 行目（`int` 3 個の配列 `a[0]`）の要素で，`p[3]` 以降はその配列の範囲を越えるからです。メモリ上は 2 行目が隣にあっても，そのポインタで境界を越えてよいことにはなりません。二次元配列では `a[r][c]` を使います。
- 一次元として扱うなら，最初から `int flat[6] = {1, 2, 3, 4, 5, 6};` を宣言し，幅 3 の行列として `flat[r * 3 + c]` で読みます（実行結果の `flat[0]`〜`flat[5]`。`r=1, c=2` なら `flat[5]` で 6）。6 個すべてが同じ配列の要素なので添字 0〜5 で走査できます。
- 「メモリ上で隣にある」「同じアドレスのように表示される」「正しい型で範囲内にアクセスできる」は別のことです。期待値が出たことは，型や境界の誤りを正当化しません。

### 採点のポイント・よくある誤り（発展2）

- `sizeof` を数値だけで答えていないか（`2 * 3 * sizeof(int)`，`2 * sizeof(int *)` の式で答える）。`sizeof rows` が指す先の `int` まで数えると誤り。
- `&a` を `int **` や `int (*)[3]` と答える誤りが多い（正しくは `int (*)[2][3]`）。`a + 0` と `a[0] + 0` の 1 単位（1 行 / `int` 1 個）を区別しているか。
- `&q` を `&a` と同じものとしていないか。
- `%p` で同じ値が出ることを「同じ型」の根拠にしていないか。`int **` へのキャストで警告を消していないか。
- `&a[0][0]` から 6 個走査する方法を使っていないか。

---

## 確認問題

1. **`int *p` を関数内から変更するには，`p` のアドレス `&p`（型 `int **`）を渡す。**
   関数は `void f(int **pp)` のように受け取り，`*pp = 新しいアドレス;` で呼び出し元の `p` を書き換えます。`p` そのもの（`int *`）を渡すと値渡しでコピーが渡るだけなので，関数内で仮引数に代入しても呼び出し元の `p` は変わりません（`find_max` の `&answer` が例）。
2. **`**pp = 10;` は `p` が指す先の `int`（例えば `x`）を変え，`*pp = &x;` は `p` 自身（`p` に保存されたアドレス，つまり指す先）を変える。**
   どちらも `pp` 自体は変わりません。課題1の断片では `**pp = 20;` で `x` が 20 に，`*pp = &y;` で `p` が `y` を指すようになり，次の `**pp = 40;` で `y` が 40 になりました（`x` は 20 のまま）。
3. **最初の要素（添字の小さい方）を選ぶ。** 条件が `a[i] > *best` なので，同じ値では候補を更新しないからです。`{12, 12, 4}` で `first=1`（`a[0]`）を確認しました。`>=` にすると最後の要素（`a[1]`，`first=0`）になります。
4. **移動しない。** ポインタ配列の交換は要素（ポインタ値＝アドレス）を入れ替えるだけで，文字列本体は元の場所にそのまま残ります。だから長さが違っても固定サイズのポインタ代入 3 回で交換でき，`strlen` やコピーも不要です（課題2）。
5. **`char *names[]` は文字列の先頭アドレス（ポインタ）を，`char names[][9]` は文字そのもの（1 行 9 個の `char`，終端と余りの 0 を含む）を保存する。**
   前者の文字列本体は別の場所にあり（`sizeof` は ポインタの個数 × `sizeof(char *)`），行の交換はポインタの交換で済みます。後者は 3 行なら 27 個の `char` が連続し（`sizeof` は 27），行の交換は 9 個の `char` の交換が必要です（課題2と課題4）。
6. **`a[r][c]` の場所を計算するには 1 行の大きさ（列数）が必要だから。** 二次元配列の仮引数は先頭行へのポインタ `int (*a)[COLS]` に調整され，`a[r]` は先頭から `r` 行分（`r * COLS` 個の `int`）先です。
   列数が分からないと次の行の位置を決められません。一方，行数（第 1 の添字）は型に残らないので `rows` として別に渡します（課題3）。
7. **長さはポインタに含まれず別の配列で管理しているので，ポインタだけを交換すると「行」と「長さ」の対応が崩れるから。** 発展1では，2 要素の `row1` を長さ 3 として読み，`row1[2]`（範囲外）にアクセスしてしまいます。ポインタと長さを一組として同時に交換します。
8. **渡せない（キャストしても正しく動かない）。** 二次元配列 `int a[2][3]` は `int (*)[3]` に変換され，その先には `int` が並んでいるだけで `int *` は保存されていません。`(int **)a` として渡すと，関数は `a[0][0]` などの整数をアドレスとして読み，範囲外アクセスや異常終了になります（未定義動作）。
   キャストは警告を消すだけで，データの形は変わりません。仮引数を `int a[][3]`（= `int (*a)[3]`）にするか，`int *rows[] = {a[0], a[1]};` のようにポインタ配列を作ってから `int **` で渡します（発展2）。

## チェックリスト

| 項目 | 確認できる課題と方法 |
| --- | --- |
| 正常な値だけでなく，課題に示された境界の値でも確認した | 課題1: `n=0`・`n=-1`（失敗），`n=1`，同点 `{12, 12, 4}` と `>=`，失敗時に古い結果を残さない（`FindMax` の variant `n0`・`n_m1`・`n1`・`tie`・`tie_ge`・`stale`）。`ReturnMaximum`: 全要素が負，場所の版だけ `n=0`（`negative`・`pointer_n0`・`best_zero`）。課題2: `swap_names(names, 1, 1)`，2 回交換（`swap_1_1`・`swap_twice`）。課題3: `rows=1`・`rows=0`，値の両端 0 と 100，割り切れない平均，整数除算，全体平均の `rows=0`（`rows1`・`rows0`・`low_high`・`fraction`・`int_division`・`overall_rows0`）。課題4: 同じ行の交換，2 回，空文字列，終端まで・5 文字だけの誤り（`same_row`・`twice`・`empty_fukui`・`until_terminator`・`fukuiawa`）。発展1: 長さも一緒に交換（`swap_with_lengths`）。本体と合わせて 42 テストで自動確認（GCC＋ASan/UBSan・Clang とも成功）。`n=4`・`rows=3`・長さを交換しない行の交換・リテラルへの書き込みなど範囲外になるものは実行せず，型と図で説明した |
| 警告を確認し，原因を説明・修正した | 全プロジェクトを `-Wall -Wextra -Wpedantic -Werror`（GCC/Clang）と AddressSanitizer/UBSan で警告 0・エラー 0 にした。説明した警告: 課題3 の `int *a[COLS]`（`int **` と `int (*)[3]` の不一致，C4047/C4024），関数内の `sizeof a`（`-Wsizeof-array-argument`），課題2 の `char **` → `const char **`，課題4 の行の代入（`array type ... is not assignable`，MSVC では C2106），発展2 の `int **bad = a;`。いずれもキャストではなく宣言を直す |
| 自分の言葉で，処理の流れと使った型を説明できる | 課題1 の二重ポインタの表（`pp → p → x`），課題2・課題4 の図（ポインタの交換と内容の交換），課題3 の `int (*)[3]` と `int **`，発展1 の 3 種類の配列の図，発展2 の型の表 |
