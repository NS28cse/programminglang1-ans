# 第5回 演習 解答・解説（配列と関数）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex05.html>（[ソース](https://github.com/t-yokoga/softprac1/blob/main/docs/ex05.md)）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec05.html>（例題 [`arrays.c`](https://github.com/t-yokoga/softprac1/blob/main/docs/sample/05/arrays.c)）
- 今回の範囲: 一次元・二次元・三次元配列（初期化子，添字，`sizeof` による要素数），`enum` による定数，関数の定義・呼び出し・戻り値・`void`，
  プロトタイプ宣言，値渡し，配列の引数（`const int a[]` と長さの引数），スコープ（ブロック・局所変数・グローバル変数・隠蔽）。
  第4回までの `if`・`for` は使ってよい。`scanf` やコマンドライン引数（第10回）は使わないので，値を変える小問は「初期値を変えて再ビルド」で行う。
  発展の `(double)total / n` の型変換は演習ページの指示どおりに使う（説明は第6回）。

## プロジェクト一覧

| 課題 | 内容 | プロジェクト | ソース | テスト |
| --- | --- | --- | --- | --- |
| ウォームアップ | 初期化を読む | `Warmup05` | [warmup.c](Warmup05/warmup.c) | 1（basic） |
| 1 | 最大の点数 | `Maximum` | [maximum.c](Maximum/maximum.c) | 6（本体 1 + 書き換え版 5：表の 4 つの配列，`return` をループ内へ移した誤り） |
| 2 | 列ごとの合計 | `ColumnSum` | [arrays.c](ColumnSum/arrays.c) | 4（本体 1 + 書き換え版 3：`table` 2 通り，`sum` の初期化位置の誤り） |
| 2 補足 | 三次元配列の添字 | `Array3D` | [array3d.c](Array3D/array3d.c) | 1（basic） |
| 3 | 値渡し（本体 = 演習ページのプログラム） | `ValueCopy` | [valuecopy.c](ValueCopy/valuecopy.c) | 10（本体 1 + 書き換え版 7：初期値 0/−1，3 つの呼び出し方，2 回代入，`z` の追加，スコープ ＋ 別ソース 2：確認問題5・6 の [plus_one.c](ValueCopy/versions/plus_one.c)・[shadow_count.c](ValueCopy/versions/shadow_count.c)） |
| 4 | 平均と累乗の関数 | `Functions` | [functions.c](Functions/functions.c) | 9（本体 1 + 書き換え版 8：表の 6 呼び出し，範囲の端，`result = 0` の誤り，変数に保存する前の版） |
| 発展 | 合計と平均の役割分担 | `SumMean` | [summean.c](SumMean/summean.c) | 5（本体 1 + 書き換え版 4：表の 2 通り，範囲の最大，合計関数単独の `n = 0`） |

合計 36 テスト。GCC 13.3（`-Wall -Wextra -Wpedantic -Werror`，AddressSanitizer/UBSan）と Clang 18.1（`-Werror`）で警告 0・全テスト成功を確認済み。CI の MSVC（`/W4 /WX`）でもビルド・テストが成功している（統合担当の CI で確認）。

- 演習ページがプロジェクト名を指定しているのは `Maximum`・`ColumnSum`・`ValueCopy`・`Functions` だけ。ソース名の指定は課題2の `arrays.c`（講義の例題を入れる）だけなので，
  ほかはプロジェクト名を小文字にした名前（`Warmup05` だけは回の番号を除いた `warmup.c`）にした。
- 発展は名前の指定がないので `SumMean`，ウォームアップは他の回と重ならないよう `Warmup05`，三次元配列の補足は `Array3D` とした（CMake ではプロジェクト名＝実行ファイル名が全回で一意である必要がある）。

### テストの構成（書き換え版）

- `<プロジェクト>/tests/basic.out` … フォルダのソース（本体。演習ページの期待する表示を出す版）の期待する出力。期待する表示が指定されていない課題では，指示をすべて反映した版。
- `<プロジェクト>/variants/tests/<ケース>.out` … 「値を変えて確かめる」「`main` の中だけを変更する」などの書き換え版の期待する出力。
  各プロジェクトの `CMakeLists.txt` で `softprac_add_variant(...)`（[cmake/SoftpracVariant.cmake](../cmake/SoftpracVariant.cmake)）を呼び，
  提出用のソースの文字列（例: `{72, 85, 60, 93, 80}` → `{0}`）を置き換えた版をビルドしてテストする。学生が初期値を書き換えて再ビルドするのと同じ操作を CMake が行う。
  置き換え前の文字列がソースにちょうど 1 回現れないと構成の段階でエラーになるので，ソースを直したときに気付ける。テスト名は `weekNN/<プロジェクト>/variant_<ケース>`。
- 書き換え版は先頭コメントの 2 行目（〜3 行目）も「〜に書き換えた版」「誤りの例: 〜」という版の説明に置き換え，生成されたソースのコメントがコードと合うようにしている。
- `ValueCopy/versions/` の `plus_one.c`・`shadow_count.c` は確認問題5・6 の確認用の別ソース。置換なしの `softprac_add_variant` でビルドしてテストする（本体の実行ファイルにはリンクされない）。
- 書き換え版の実行ファイルは `bin/` ではなくビルドフォルダの `variants/week05/` にでき，Visual Studio の起動構成（`.vs/launch.vs.json`）には現れない。
- どのプログラムも入力を取らず表示が 1 通りに決まるので，各版のテストは標準出力の完全一致と終了コード 0。
- 実行結果は Linux x64（GCC 13.3 / Clang 18.1，`-std=c17 -Wall -Wextra -Wpedantic -Werror`，GCC では AddressSanitizer/UBSan も有効）で実際にビルド・実行した出力。
  表示は ASCII だけで，`%p`（アドレス）と `sizeof` の一部を除き Windows（MSVC）でも同じになる。配列の長さはすべて定数（リテラルか `enum`）なので MSVC でもビルドできる（VLA なし）。
- 誤りの例の診断は，GCC は実際にコンパイルした出力，MSVC はエラー・警告番号と英語版の文面（日本語版 Visual Studio では同じ番号の日本語訳が表示される）。

---

## ウォームアップ　初期化を読む（`Warmup05` / `warmup.c`）

**要点**: 初期化子を書いた配列では，書かなかった残りの要素が 0 になる。`int a[5] = {1, 1};` は {1, 1, 0, 0, 0}，`int b[5] = {0};` は {0, 0, 0, 0, 0}。

**紙上の予測**

| 添字 `i` | 0 | 1 | 2 | 3 | 4 |
| --- | ---: | ---: | ---: | ---: | ---: |
| `a[i]` | 1 | 1 | 0 | 0 | 0 |
| `b[i]` | 0 | 0 | 0 | 0 | 0 |

**解答**: [Warmup05/warmup.c](Warmup05/warmup.c)（演習ページのコード片を `main` に置いただけ）

**実行結果**

```text
1 0
1 0
0 0
0 0
0 0
```

**説明**: `{0}` は「最初の要素を 0 にし，残りは省略したので 0」という意味で，「全部 0 にする特別な書き方」ではない。だから `{1, 1}` も最初の 2 個だけが 1 になる。
初期化子を書かずに `int a[5];` とした局所配列は 0 にならない（値を入れる前に読んではいけない）。

**採点のポイント・よくある誤り**

- `int a[5] = {1, 1};` を「全部 1」と予測する（`{0}` で全部 0 になることからの誤った類推）。
- `for` の条件を `i <= 5` にして `a[5]` を読む（範囲外。要素数 5 の最後の添字は 4）。

---

## 課題1　最大の点数（`Maximum` / `maximum.c`）

**要点**: 配列と長さを受け取る関数の書き方。最大値の候補 `best` を最初の要素で初期化し，残りと比べて更新する。全要素を調べ終えてから `return` する。

**解答**: [Maximum/maximum.c](Maximum/maximum.c)

```c
enum { COUNT = 5 };

int max_score(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int best = max_score(scores, COUNT);
    printf("max=%d\n", best);
    return 0;
}

int max_score(const int a[], int n)
{
    int best = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > best) {
            best = a[i];
        }
    }
    return best;
}
```

- 表示の形式は演習ページで指定されていないので `max=93` とした。
- 実行前に書き出すこと: 要素数 5，使える添字 0〜4，関数へ渡す値は配列 `scores`（先頭を指す情報）と `n = 5`，返される値は 93。

**実行結果**（予測: 93）

```text
max=93
```

### 最大値の候補を追跡する（表の解答）

| `i` | `a[i]` | 比較前の`best` | 更新後の`best` |
| ---: | ---: | ---: | ---: |
| 1 | 85 | 72 | 85 |
| 2 | 60 | 85 | 85 |
| 3 | 93 | 85 | 93 |
| 4 | 80 | 93 | 93 |

`best` は「添字 0〜`i` の要素の最大値」を保つ。`i = 4` まで調べ終えた時点で配列全体の最大値 93 になる。

### 異なる配列で確かめる（表の解答）

| 配列 | 渡す`n` | 最大値 | 注目点 |
| --- | ---: | ---: | --- |
| {0} | 1 | 0 | 本体を0回で終了する（`i = 1` で `1 < 1` が偽。`best = a[0]` のまま） |
| {60, 60, 60} | 3 | 60 | 等しい値で候補が変わらない（`60 > 60` は偽） |
| {100, 20, 30} | 3 | 100 | 最初が最大（初期値のまま一度も更新されない） |
| {20, 30, 100} | 3 | 100 | 最後が最大（`i = n - 1` の最後の比較で更新される） |

`maximum.c` の `COUNT` と初期化子を表に合わせて書き換えた版の実行結果（[Maximum/CMakeLists.txt](Maximum/CMakeLists.txt)。各行をテストで確認）:

| 変更（`enum { COUNT = … };` と `int scores[COUNT] = …;`） | 実行結果 | テスト |
| --- | --- | --- |
| （元）`COUNT = 5`，`{72, 85, 60, 93, 80}` | `max=93` | `basic` |
| `COUNT = 1`，`{0}` | `max=0` | `variant_zero` |
| `COUNT = 3`，`{60, 60, 60}` | `max=60` | `variant_same` |
| `COUNT = 3`，`{100, 20, 30}` | `max=100` | `variant_first` |
| `COUNT = 3`，`{20, 30, 100}` | `max=100` | `variant_last` |

**要素数の変更と `sizeof`**: 解答では配列の大きさと渡す長さを同じ定数 `COUNT` にしているので，`COUNT` を変えれば両方が一緒に変わる。
`int scores[5]` と `max_score(scores, 5)` のようにリテラルを 2 か所に書いた場合は，配列だけを増やしても呼び出しの 5 は変わらない（演習ページの注意）。
`sizeof scores / sizeof scores[0]` は配列を宣言した `main` では要素数（5）になるが，`max_score` の仮引数 `a` は先頭の要素を指す情報（ポインタ）なので，`sizeof a` はポインタのサイズになり要素数は求められない（確認問題4）。

### 説明すること

- **`i` を 1 から始める理由**: `best` を `a[0]` で初期化した時点で添字 0 は調べ終えているから。0 から始めても結果は同じだが，`a[0]` と自分自身を比べる無駄な 1 回になる。
  候補を 0 などの固定値で初期化しないのは，「配列の中の値」から始めればどんな範囲の値でも正しく動くため（例えば全要素が負なら 0 は誤り）。そのために `n` は 1 以上という約束が必要で，`n = 0` では `a[0]` が存在せず読めない。
- **戻り値を返す位置**: `for` の後（全要素を調べ終えた後）。ループの中で `return` すると最初の比較で関数が終わり，残りの要素を調べない。
  例えば `if` の後ろ（ループ内）へ `return best;` を移すと，初期値の配列で `max=85` になる（`i = 1` だけ調べて返す。テスト `variant_return_in_loop`）。さらに，値を返さずに関数の終わりに達する経路ができ（コンパイラが警告。GCC: `warning: control reaches end of non-void function [-Wreturn-type]`，MSVC: `C4715: 'max_score': not all control paths return a value`），
  `n = 1` では実際にその経路を通る（ループに 1 回も入らない。その戻り値を使うと未定義動作）。
  テストの版は誤りを示すためのものなので，この版だけ `-Wno-return-type`（MSVC は `/wd4715`）で警告を抑止している（`-Werror`・`/WX` でビルドが止まらないように）。
  入力は `n = 5` で，`i = 1` の繰り返しの中で必ず `return` するため，関数の終わりに達する経路は通らず未定義動作にはならない。
- **`const` を付ける意図**: `max_score` は配列を読むだけで書き換えないことを宣言として示す。配列の引数は要素がコピーされず元の要素を指すので，書き換えると呼び出し元の配列が変わる。
  `const` があれば，誤って `a[i] = 0;` のように書いたときにコンパイルエラーになり（GCC: `assignment of read-only location`，MSVC: `C2166: l-value specifies const object`），呼び出し側も「渡しても壊されない」と分かる。

### 採点のポイント・よくある誤り

- `best` を 0 で初期化している（この課題の範囲 0〜100 では偶然正しいが，「配列の中の値から始める」考え方になっていない）。`n` が 1 以上という前提を説明できているか。
- `return` をループ内に置いている／`else return` で途中終了している。表の {20, 30, 100}（最後が最大）で誤りが分かる。
- ループ条件を `i <= n` にして `a[n]` を読む（範囲外）。
- `max_score(scores, 5)` の 5 を配列の要素数の変更に合わせて直していない（{0} に変えたのに 5 のまま → 範囲外アクセス）。
- `max_score` の中で `sizeof a / sizeof a[0]` で要素数を求めている（x64 では 8 / 4 = 2 になり誤り）。
- `max_score` の中で `printf` して戻り値を返さない（課題の「関数が値を返す」になっていない）。

---

## 課題2　列ごとの合計（`ColumnSum` / `arrays.c`）

**要点**: 二重ループの外側を列，内側を行にする。合計 `sum` は列ごとに 0 へ戻す。ループの順を変えても添字は常に `table[行][列]`。

- 実行前に書き出すこと: `scores` は要素数 5・使える添字 0〜4，`table` は 2 行 3 列で要素数 6・使える添字は第1添字（行）0〜1，第2添字（列）0〜2。関数へ渡す値は `sum_array` へ `scores` と `COUNT`（5），返される値は 390。列の合計は `main` の二重ループで求める（関数には渡さない）。

**解答**: [ColumnSum/arrays.c](ColumnSum/arrays.c)（講義の `arrays.c` の二次元配列の部分だけを変更）

```c
    int table[2][3] = {{1, 2, 3}, {4, 5, 6}};
    for (int col = 0; col < 3; ++col) {
        int sum = 0;
        for (int row = 0; row < 2; ++row) {
            sum += table[row][col];
        }
        printf("col %d: %d\n", col, sum);
    }
```

**実行結果**（演習ページの「変更後のプログラム全体の表示」と一致）

```text
total=390 mean=78.0
col 0: 5
col 1: 7
col 2: 9
```

### 訪問順と合計を確認する（表の解答）

| 外側の`col` | 内側で読む要素 | 計算 |
| ---: | --- | --- |
| 0 | `table[0][0]`，`table[1][0]` | 0 + 1 + 4 = 5 |
| 1 | `table[0][1]`，`table[1][1]` | 0 + 2 + 5 = 7 |
| 2 | `table[0][2]`，`table[1][2]` | 0 + 3 + 6 = 9 |

（先頭の 0 は列ごとに初期化した `sum`。）訪問順は `[0][0] → [1][0] → [0][1] → [1][1] → [0][2] → [1][2]` で，メモリ上の並び（行ごとに連続）とは異なる順に読む。

### `table` を変えて確かめる

`table` の初期化子だけを書き換えた版の実行結果（[ColumnSum/CMakeLists.txt](ColumnSum/CMakeLists.txt)。各行をテストで確認）:

| `table` の初期化子 | 実行結果（`total` の行は 3 通りとも `total=390 mean=78.0`） | テスト |
| --- | --- | --- |
| `{{1, 2, 3}, {4, 5, 6}}`（元） | `col 0: 5` / `col 1: 7` / `col 2: 9` | `basic` |
| `{{1, 1, 1}, {2, 2, 2}}` | `col 0: 3` / `col 1: 3` / `col 2: 3` | `variant_ones` |
| `{{0}}`（全要素 0） | `col 0: 0` / `col 1: 0` / `col 2: 0` | `variant_zero` |

`{{0}}` の版の表示全体:

```text
total=390 mean=78.0
col 0: 0
col 1: 0
col 2: 0
```

`{{0}}` は `table[0][0]` だけを 0 と書き，残りの 5 要素は省略したので 0 になる（ウォームアップと同じ規則）。点数配列 `scores` は変えていないので最初の行は変わらない。

**`sum` の初期化を二重ループ全体の前へ移した誤りの版**（演習ページの「5，12，21 の累積」をテスト `variant_sum_outside` で確認）

```c
    int sum = 0;  // 誤り: 二重ループ全体の前で 1 回だけ初期化
    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 2; ++row) {
            sum += table[row][col];
        }
        printf("col %d: %d\n", col, sum);
    }
```

```text
total=390 mean=78.0
col 0: 5
col 1: 12
col 2: 21
```

### `table[row][col]` の添字はループの順と一致しなければならないか

**一致させる必要はない**。添字の意味は宣言 `int table[2][3]` で決まり，第1添字は常に行（0〜1），第2添字は常に列（0〜2）。
ループの外側・内側をどちらにするかは「どの順に訪問するか」を決めるだけで，外側を `col` にしても要素は `table[row][col]` と書く。

### 説明すること：`table[col][row]` へ入れ替えてはいけない理由

`table` は 2 行 3 列なので，第1添字に使えるのは 0〜1，第2添字に使えるのは 0〜2。この課題の `col` は 0〜2，`row` は 0〜1 を動く。
`table[col][row]` にすると，範囲 0〜2 の `col` を範囲 0〜1 の第1添字に使うことになり，`col = 2` のとき `table[2][0]`・`table[2][1]` という**存在しない 3 行目**を読む（範囲外アクセス＝未定義動作）。
`col` が 0・1 のときも `table[0][0] + table[0][1]` のように「列」ではなく行の中の要素を足すので，合計自体も誤る。危険な変更なので実行はせず，紙上で判断する。

### 補足：三次元配列の添字（`Array3D` / `array3d.c`）

| 問い | 答え |
| --- | --- |
| `int data[2][3][4] = {0};` の総要素数 | 2 × 3 × 4 = **24** |
| 最後の要素を表す式 | **`data[1][2][3]`**（各次元の「要素数 − 1」を並べる） |
| 各次元の添字の範囲 | 第1添字 0〜1，第2添字 0〜2，第3添字 0〜3 |

```c
    int data[2][3][4] = {0};
    data[1][2][3] = 7;
    printf("last=%d count=%zu\n", data[1][2][3],
           sizeof data / sizeof data[0][0][0]);
```

```text
last=7 count=24
```

「3 行 4 列のまとまりが 2 つ」で，最後の添字（第3添字）の方向に要素が連続する。`data[2][3][4]` は宣言と同じ数字だが，式としては 3 つとも範囲外。

### 採点のポイント・よくある誤り

- 表示が `col 0: 5` の形（`col` と数字の間に空白，コロンの後に空白 1 個）で，`total=390 mean=78.0` の行を残しているか（演習ページの表示と 1 文字ずつ比べる）。
- `sum` の初期化位置。外側ループの中（列ごと）でないと 5，12，21 になる。
- ループの順を変えたときに添字まで `table[col][row]` に入れ替えている（範囲外。`col` の範囲 0〜2 と第1添字の範囲 0〜1 が合わない）。たまたま値が表示されても正しくない。
- 外側・内側のループ上限を取り違える（`col < 2`，`row < 3` など）。`{{1, 1, 1}, {2, 2, 2}}` の確認で各列 3 にならないことから気づける。
- 三次元配列で最後の要素を `data[2][3][4]` と書く（宣言の数字は要素数で，最後の添字ではない）。

---

## 課題3　値渡しを確認する（`ValueCopy` / `valuecopy.c`）

**要点**: 仮引数は呼び出しのたびに作られる別の局所変数で，実引数の値のコピーを受け取る。関数内で仮引数を変えても呼び出し元の変数は変わらない。呼び出し元の変数が変わるのは，戻り値を**代入したとき**だけ。

- 実行前に書き出すこと: 配列は使わない。関数へ渡す値は `main` の `x` の値 10（仮引数 `x` へコピーされる），返される値は 11。

**解答**: [ValueCopy/valuecopy.c](ValueCopy/valuecopy.c)（演習ページのプログラムそのもの）

```c
int increment(int x)
{
    x = x + 1;
    return x;
}

int main(void)
{
    int x = 10;
    int y = increment(x);
    printf("%d %d\n", x, y);
    return 0;
}
```

演習ページのその後の実験（呼び出し方の変更，初期値の変更，`z` の追加，スコープ）は，この本体の `main` の一部を書き換えた版としてビルドし，テストしている（[ValueCopy/CMakeLists.txt](ValueCopy/CMakeLists.txt)）。

**実行結果**（予測: `10 11`，テスト `basic`）

```text
10 11
```

`increment` の仮引数 `x` は 10 のコピーを受け取り，11 に変えて返す。`main` の `x` は別の変数なので 10 のまま，戻り値 11 が `y` に入る。

### 3つの呼び出し方を比べる（表の解答）

| 呼び出し方 | 呼び出し後の`main`の`x` | 戻り値の扱い |
| --- | ---: | --- |
| `increment(x);` | 10 | 戻り値 11 はどこにも保存されず捨てられる |
| `int y = increment(x);` | 10 | 戻り値 11 で新しい変数 `y` を初期化する（`x` は変わらない） |
| `x = increment(x);` | 11 | 戻り値 11 を `main` の `x` へ代入して上書きする |

3 行目で `x` が変わるのは関数の中の処理によるものではなく，呼び出し元の代入によるもの。

確認に使った書き換え版（`int x = 10;` の後の行を置き換えた。毎回 `x` は 10 から始まる）と実行結果:

| `int x = 10;` の後 | 実行結果 | テスト |
| --- | --- | --- |
| `increment(x);` / `printf("%d\n", x);` | `10` | `variant_call_discard` |
| `int y = increment(x);` / `printf("%d %d\n", x, y);`（本体のまま） | `10 11` | `basic` |
| `x = increment(x);` / `printf("%d\n", x);` | `11` | `variant_call_assign` |

### 初期値を 0，−1 へ変更した場合（元の完全なプログラムの `int x = 10;` を書き換えた版）

| `main` の初期値 | 予測 | 実行結果 | テスト |
| ---: | --- | --- | --- |
| 10 | `10 11` | `10 11` | `basic` |
| 0 | `0 1` | `0 1` | `variant_x_0` |
| −1 | `-1 0` | `-1 0` | `variant_x_m1` |

範囲 −100〜100 では `x + 1` が `int` の範囲を超えないので，どの値でも「`x` はそのまま，`y` は `x + 1`」になる。

### 呼び出しごとに別の局所変数になる

最初の呼び出しの後に `int z = increment(x);` を追加し，表示を `printf("%d %d %d\n", x, y, z);` にした版の実行結果（予測: `x = 10`，`y = 11`，`z = 11`，テスト `variant_add_z`）

```c
    int x = 10;
    int y = increment(x);
    int z = increment(x);
    printf("%d %d %d\n", x, y, z);
```

```text
10 11 11
```

1 回目の呼び出しでは仮引数 `x` が 10 で作られ，11 になって返り，呼び出しが終わると消える。2 回目の呼び出しでは**新しい**仮引数 `x` が再び `main` の `x` の値 10 で作られる。
1 回目の仮引数の変更（10 → 11）は `main` の `x` にも 2 回目の仮引数にも残らないので，`z` も 11 になる。

**`x = increment(x);` を 2 回続ける場合**（予測・実行結果ともに `x = 12`。`printf("%d\n", x);` で `12` と表示されることをテスト `variant_assign_twice` で確認）

```c
    int x = 10;
    x = increment(x);  // 仮引数 10 → 11 を返す → main の x に 11 を代入
    x = increment(x);  // 仮引数 11 → 12 を返す → main の x に 12 を代入
```

関数の内側では，どちらの呼び出しでも仮引数（コピー）が 1 増えるだけで，呼び出しが終わると消える。`main` の `x` が 10 → 11 → 12 と変わるのは，**呼び出し元の代入**が 2 回行われたから。

### スコープの読解

```c
{
    int a = 123;
    printf("%d\n", a);
}
{
    int a = 345;
    printf("%d\n", a);
}
```

予測・実行結果（`main` の本体をこの 2 つのブロックに置き換えた版。テスト `variant_scope_blocks`）:

```text
123
345
```

- 2 つの `a` は別々のブロックで宣言された別の局所変数。後半は前半の `a` への代入ではなく，新しい変数の宣言と初期化。
- **この直後に `printf` で `a` を表示できるか → できない**。どちらの `a` もスコープは自分のブロックの `}` まで。ブロックの外では名前 `a` が見えず，コンパイルエラーになる
  （GCC: `error: 'a' undeclared (first use in this function)`，MSVC: `C2065: 'a': undeclared identifier`）。
- **2 つの宣言を同じブロックへ移せるか → そのままではできない**。同じブロックで同じ名前を 2 回宣言すると重複になる
  （GCC: `error: redefinition of 'a'`，MSVC: `C2374: 'a': redefinition; multiple initialization`）。同じブロックにするなら 2 つ目を代入 `a = 345;` に変える（この場合は同じ変数を上書きする）。
- **仮引数 `x` と `main` の `x` が共存できる理由**: 仮引数 `x` のスコープは `increment` の本体だけ，`main` の `x` のスコープは `main` のブロックだけで，2 つの範囲は重ならない。
  名前が同じでも別の変数（別の領域）であり，`increment` から `main` の `x` を名前で直接読むことはできない。必要な値は引数で渡し，結果は戻り値で受け取る。

### 採点のポイント・よくある誤り

- `increment(x);` だけで `main` の `x` が 11 になると予測する（値渡しの誤解）。「仮引数」「実引数」「コピー」「戻り値の代入」の用語で説明できているか。
- `z` を 12 と予測する（1 回目の呼び出しの変更が残ると考えている）。
- `x = increment(x);` 2 回で 12 になる理由を「関数が `main` の `x` を変えたから」と説明している（正しくは呼び出し元の代入）。
- スコープの問題で，2 つ目のブロックの `a = 345` を前の `a` への代入と説明している。字下げではなく波括弧が範囲を決める。
- 初期値を変える実験で `main` を複製してしまう（演習ページの指示は「初期値を変えて再ビルド」）。

---

## 課題4　平均と累乗を関数にする（`Functions` / `functions.c`）

**要点**: 複数の引数・戻り値の型・プロトタイプ宣言。計算は関数，表示は `main` と役割を分ける。関数が受け付ける値の範囲（契約）を先に決める。

### 関数の型（表の解答）

| 関数 | 引数 | 戻り値 | この課題での範囲 |
| --- | --- | --- | --- |
| `average` | `float`の`a`と`b` | `float`（2 つの平均） | 各値−100〜100 |
| `power` | `int`の`base`と`exponent` | `int`（`base` の `exponent` 乗） | `base`は1〜5，`exponent`は0〜5 |

範囲内なら `power` の結果は最大 5<sup>5</sup> = 3125，`average` の結果は −100〜100 で，どちらも戻り値の型に収まる。

- 実行前に書き出すこと: 配列は使わない。関数へ渡す値は `average` へ `2.0f` と `4.0f`，`power` へ `2` と `5`。返される値は `average` が `float` の 3.0，`power` が `int` の 32。

**解答**: [Functions/functions.c](Functions/functions.c)（本体。演習ページの指示をすべて反映した版で，「戻り値と表示を分ける」の変更まで含む）

```c
#include <stdio.h>

float average(float a, float b);
int power(int base, int exponent);

int main(void)
{
    float result = average(2.0f, 4.0f);
    printf("average=%.1f\n", result);
    printf("power=%d\n", power(2, 5));
    return 0;
}

float average(float a, float b)
{
    return (a + b) / 2.0f;
}

int power(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}
```

**実行結果**（演習ページの最初の表示と一致）

```text
average=3.0
power=32
```

`float` の値を `printf` に渡すと `double` に変換されて渡されるので，書式は `%f`（ここでは小数 1 桁の `%.1f`）でよい。

### 境界の値で確認する（表の解答）

| 呼び出し | 期待する戻り値 | 理由 |
| --- | ---: | --- |
| `average(0.0f, 0.0f)` | 0.0 | 同じ値の平均（(0 + 0) / 2） |
| `average(-4.0f, 2.0f)` | −1.0 | 負の値を含む平均（(−4 + 2) / 2 = −2 / 2） |
| `average(1.0f, 2.0f)` | 1.5 | 小数部を失わない（`2.0f` で割る浮動小数点の除算） |
| `power(2, 0)` | 1 | 本体は0回で初期値を返す（2<sup>0</sup> = 1） |
| `power(5, 1)` | 5 | 1回だけ掛ける（1 × 5） |
| `power(5, 5)` | 3125 | 課題で許す最大の結果（1 × 5 × 5 × 5 × 5 × 5） |

`main` の `average(2.0f, 4.0f)` と `power(2, 5)` の引数を書き換えた版の実行結果（[Functions/CMakeLists.txt](Functions/CMakeLists.txt)。表の 6 つの呼び出しを 3 つの版で覆い，範囲の端も加えた）:

| `average` の引数 | `power` の引数 | 実行結果 | テスト |
| --- | --- | --- | --- |
| `2.0f, 4.0f`（元） | `2, 5`（元） | `average=3.0` / `power=32` | `basic` |
| `0.0f, 0.0f` | `2, 0` | `average=0.0` / `power=1` | `variant_a_0_0_p_2_0` |
| `-4.0f, 2.0f` | `5, 1` | `average=-1.0` / `power=5` | `variant_a_m4_2_p_5_1` |
| `1.0f, 2.0f` | `5, 5` | `average=1.5` / `power=3125` | `variant_a_1_2_p_5_5` |
| `-100.0f, -100.0f`（範囲の下端） | `1, 0` | `average=-100.0` / `power=1` | `variant_a_m100_m100_p_1_0` |
| `-100.0f, 100.0f` | `1, 5` | `average=0.0` / `power=1` | `variant_a_m100_100_p_1_5` |
| `100.0f, 100.0f`（範囲の上端） | `2, 5`（元） | `average=100.0` / `power=32` | `variant_a_100_100` |

表の値は，どれも `float` で正確に表せる値（整数と 0.5 の倍数）なので，表示の丸めの心配はない。
`power` は負の指数（結果が分数になる）や `int` の範囲を超える大きさは扱わない。範囲を守るのは呼び出し側の約束で，関数名が `power` だから何でも計算できるわけではない。

### 説明すること

- **`result` を 0 で初期化してはいけない理由**: `power` は `result` に `base` を掛けていく。0 に何を掛けても 0 なので，どの呼び出しでも 0 が返る
  （実際に `int result = 0;` にすると `average=3.0` / `power=0` と表示される。テスト `variant_result_0`）。掛け算の初期値は単位元の 1 にする。こうすると `exponent = 0` で本体を 0 回実行したときも，正しく 1（= base<sup>0</sup>）が返る。
  足し算で合計を求める `sum` を 0 で初期化するのと対になっている。
- **`return` を `for` の外へ置く理由**: `return` を実行するとその場で関数が終わり呼び出し元へ戻る。`for` の中に置くと 1 回掛けただけで返り，`exponent` 回の繰り返しにならない。
  また `exponent = 0` のときは本体を 1 回も実行しないので，`for` の中の `return` に到達せず，値を返さずに関数の終わりに達する（コンパイラが警告。GCC は `-Wreturn-type`，MSVC は `C4715`。その戻り値を使うと未定義動作）。
- **プロトタイプ宣言の末尾にセミコロンが必要な理由**: プロトタイプ宣言は本体を持たない**宣言**で，変数の宣言と同じく `;` で終わる。`;` がないと，コンパイラは次の行の `int main(void)` を，その関数の旧式の仮引数宣言（本体の前に仮引数の型を並べる古い書き方）の続きとして読み，
  `main` の本体の `{` でエラーになる（`int power(int base, int exponent)` の `;` を消して確かめると，GCC は `main` の `{` の行で `error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token`。
  MSVC の `C2085: 'main': not in formal parameter list` も，`main` を仮引数宣言として読んだという同じ理由。続けて別のエラーが出ることもある）。
  定義（`{ … }` の本体を持つ）の後には `;` を付けない。

**プロトタイプ宣言を書かなかった場合**（関数を `main` の後ろに置いたまま宣言を消した例）: `main` で呼ぶ時点で `average` を知らないので，
GCC は `warning: implicit declaration of function 'average'` の後に `error: conflicting types for 'average'`（戻り値を `int` と仮定したため），
MSVC は `C4013: 'average' undefined; assuming extern returning int` の後に `C2371: 'average': redefinition; different basic types` を出す。
宣言はコンパイル時に呼び出し方（引数と戻り値の型）を確認するためのもので，「後ろの関数が実行時にまだ存在しない」からではない。

### 戻り値と表示を分ける

変更前（戻り値をそのまま `printf` に渡す）と変更後（変数 `result` に保存してから表示する，本体）の `main`:

```c
    // 変更前
    printf("average=%.1f\n", average(2.0f, 4.0f));
```

```c
    // 変更後
    float result = average(2.0f, 4.0f);
    printf("average=%.1f\n", result);
```

どちらも実際の表示は `average=3.0` / `power=32` で同じ（変更後はテスト `basic`，変更前はテスト `variant_before_result` で確認）。
`average` の中で `printf` だけを実行して値を返さない形（例えば `void average(float a, float b)` の中で表示する）では，平均は画面に出るだけで呼び出し元に値が戻らず，
`float result = average(...)` のように変数へ保存したり，別の計算（合計との比較など）に使ったりできない。`return` は呼び出し元へ値を返す操作，表示は `printf` の仕事，と区別する。

### 採点のポイント・よくある誤り

- `average` の戻り値型を `int` にしている（`average(1.0f, 2.0f)` が 1 になる）。
- `(a + b) / 2` と `2.0f` のどちらでもこの場合は `float` の除算になるが，`return (a + b) / 2.0;` は `double` の計算結果を `float` で返すので MSVC `/W4` で `C4244: 'return': conversion from 'double' to 'float', possible loss of data` が出る。
  `average(2.0, 4.0)` のように `double` のリテラルを渡しても MSVC は `C4305: 'function': truncation from 'double' to 'float'` を出す。`f` 接尾辞の有無を確認する。
- 累乗に `^` を使っている（`2 ^ 5` はビットごとの XOR で 7）。
- `result` を 0 で初期化，`return` をループ内，`for (int i = 0; i <= exponent; ++i)`（1 回多く掛ける）。表の `power(2, 0)`・`power(5, 1)` で発見できる。
- 関数の中で `printf` している（演習の指示「関数内で表示はせず，`main` で戻り値を表示」に反する）。
- プロトタイプ宣言がない，または宣言と定義の型が一致しない。関数を `main` の中に定義している。

---

## 発展　役割を分ける（`SumMean` / `summean.c`）

**要点**: 合計を返す `sum_array` と，平均を計算して表示する `main` に役割を分ける。関数の契約（受け付ける `n` の範囲）は関数ごとに違ってよく，呼び出し側はそれに加えて自分の計算の前提（0 で割らない）を守る。

- 実行前に書き出すこと: 配列 `scores` の要素数は `COUNT`（5）で使える添字は 0〜4，そのうち先頭の `n` 個（添字 0〜`n`−1）を使う。関数へ渡す値は `sum_array` へ `scores` と `n`（初期値では 5），返される値は合計 390（平均 78.0 は `main` で計算）。

**解答**: [SumMean/summean.c](SumMean/summean.c)

```c
enum { COUNT = 5 };

int sum_array(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int n = COUNT;
    int total = sum_array(scores, n);
    printf("total=%d mean=%.1f\n", total, (double)total / n);
    return 0;
}

int sum_array(const int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}
```

配列は最大の 5 要素分を用意し，実際に使う要素数 `n`（1〜5）を別の変数にした。値を変えるときは初期化子と `n` を書き換える。`n` が配列の要素数以下である限り範囲外を読まない。

**実行結果**（初期値）

```text
total=390 mean=78.0
```

**値を変えて確かめる**（初期化子と `n` を書き換えた版。[SumMean/CMakeLists.txt](SumMean/CMakeLists.txt)。演習ページの期待どおり）

| 変更 | 実行結果 | テスト |
| --- | --- | --- |
| `int scores[COUNT] = {72, 85, 60, 93, 80};`，`int n = COUNT;`（初期値） | `total=390 mean=78.0` | `basic` |
| `int scores[COUNT] = {0};`，`int n = 1;` | `total=0 mean=0.0` | `variant_zero_n_1` |
| `int scores[COUNT] = {100, 100, 100};`，`int n = 3;` | `total=300 mean=100.0` | `variant_hundred_n_3` |
| `int scores[COUNT] = {100, 100, 100, 100, 100};`，`int n = COUNT;`（範囲の最大） | `total=500 mean=100.0` | `variant_full_100` |
| （合計関数単独）`int n = 0;`，表示を `printf("total=%d\n", total);` に | `total=0` | `variant_sum_only_n_0` |

**説明**

- `(double)total / n` は `total` を `double` に変換してから割るので，浮動小数点の除算になる。`total / n` と書くと `int` 同士の整数除算で小数部が切り捨てられる（例えば合計 7，`n = 2` なら 3）。
  `(double)(total / n)` も，先に整数除算してから変換するので誤り。
- 合計を返す `sum_array` は，`n = 0` なら本体を 0 回実行して 0 を返すので，関数単独では `n = 0` を受け付けてよい（講義の契約「`n` は 0 以上」）。
  `int n = 0;` にして平均を表示せず `printf("total=%d\n", total);` だけにした版で `total=0` と表示されることをテスト `variant_sum_only_n_0` で確認した。
  一方，`main` の平均は `n` で割るので `n = 0` は 0 除算になる。だから**この `main` の `n` は 1 以上**という前提が必要（関数の契約と，呼び出し側の前提は別に考える）。
- 範囲（要素数 1〜5，値 0〜100）なら合計は最大 500 で `int` に収まる。

### 採点のポイント・よくある誤り

- `sum_array` の中で平均を計算・表示している（役割分担になっていない）。
- `total / n` の整数除算，`(double)(total / n)` の変換位置の誤り。`{72, 85, 60, 93, 80}` では 390 / 5 = 78 で割り切れるため誤りが表に出ない。値を変えた確認（例: `{1, 2}`，`n = 2` で 1.5）で見つける。
- 配列の初期化子だけを変えて `n` を直していない。`{0}` の場合は `n` が 5 のままでも表示は `total=0 mean=0.0` で変わらず，出力では見分けられないので，ソースの `n` を確認する。
  `{100, 100, 100}` で `n` を 5 のままにすると `total=300 mean=60.0` になり（残りの 2 要素の 0 も数えて割る。実行して確認），誤りが表に出る。
  配列自体を `int scores[1] = {0};` に変えたのに 5 を渡すと範囲外アクセス。
- `n = 0` を許して 0 で割る。

---

## 確認問題

1. **添字 4，値 0**。要素数 5 の配列の最後の添字は 5 − 1 = 4。初期化子 `{1, 1}` は `a[0]`・`a[1]` だけを指定しており，省略した `a[2]`〜`a[4]` は 0 になる（ウォームアップの実行結果の 5 行目 `0 0` の左の値が `a[4]`）。
2. **範囲外アクセス（未定義動作）だから**。`int table[2][3]` の第2添字（列）の範囲は 0〜2 で，`table[0][3]` は 0 行目の範囲外。メモリ上では 0 行目の後に 1 行目が連続しているが，
   それを当てにして範囲外の添字を使ってはいけない。1 行目の最初の要素なら `table[1][0]` と書く。C は実行時に添字の範囲を自動検査しないので，ビルドが成功しても正しいとは限らない。
3. **全体 12 バイト，隣接要素の間隔 4 バイト**。要素は添字の順に連続して並ぶので，全体は 4 × 3 = 12 バイト，`&a[1]` は `&a[0]` の 4 バイト後。実際の表示（Linux x64，アドレスは実行ごとに変わる）:
   ```text
   a[0]=12 address=0x7fec0cb00020
   a[1]=3 address=0x7fec0cb00024
   a[2]=5 address=0x7fec0cb00028
   array=12 element=4 count=3
   ```
   （この例は AddressSanitizer を有効にしたビルドのもの。ASan なしでは `0x7ffea78331dc`・`…1e0`・`…1e4` のような `0x7ff…` で始まるスタックのアドレスになる（間隔はやはり 4）。）Windows（MSVC）でも `int` は 4 バイトなので最後の行は同じ。`%p` の表示形式は環境で異なる（MSVC では `0x` なしの大文字 16 桁など）。
4. **関数の仮引数 `a` は配列そのものではなく，先頭の要素を指す情報（ポインタ）だから**。配列を渡しても全要素はコピーされず，`sizeof a` はポインタのサイズになる。
   実際に 3 要素の配列を渡した関数で `sizeof a` を表示すると，Linux x64 では `8`（`main` での `sizeof a` は 12）。Windows x64 でも 8，x86（Win32）では 4。
   GCC は `warning: 'sizeof' on array function parameter 'a' will return size of 'const int *' [-Wsizeof-array-argument]` を出す。だから長さは別の引数 `n` で渡す。
5. **10 のまま**。`plus_one` の仮引数 `value` は `b` の値のコピーで，関数内で 11 になっても `b` は変わらない。戻り値 11 は使われずに捨てられる。
   `int c = plus_one(b);` なら `c` が 11，`b = plus_one(b);` なら代入によって `b` が 11 になる（[ValueCopy/versions/plus_one.c](ValueCopy/versions/plus_one.c) で `b=10` / `b=10 c=11` / `b=11` と表示されることをテスト `variant_plus_one` で確認）。
6. **局所変数のほう**。関数内で同名の局所変数を宣言すると，その関数（そのブロック）では内側の名前が外側を隠す（隠蔽，シャドーイング）。`++count` は局所変数を変え，グローバル変数は変わらない。
   講義の `tick` に `int count = 3;` を追加した [ValueCopy/versions/shadow_count.c](ValueCopy/versions/shadow_count.c) で，`global count=0` → `local count=4` → `global count=0` と表示される（テスト `variant_shadow_count`）。
   MSVC `/W4` は `C4459: declaration of 'count' hides global declaration` を出す（GCC/Clang は `-Wshadow` を付けたときだけで，`-Wall -Wextra` には含まれない）。
   この版は隠蔽を示すためにわざと書いたものなので，CI の `/WX`（警告をエラーにする）で止まらないよう，`ValueCopy/CMakeLists.txt` でこの版だけ MSVC の C4459 を `/wd4459` で抑止している。
7. **`void` 関数の `return;` は値を返さずに呼び出し元へ戻るだけ，`int` 関数の `return 0;` は値 0 を呼び出し元へ返して戻る**。`void` 関数の呼び出しは値を持たないので `int x = hello();` のように受け取れない。
   `void` 関数の末尾の `return;` は省略できるが，`void` でない関数はすべての経路で値を返す必要がある。`main` の `return 0;` は呼び出し元（実行環境）へ 0 を返し，プログラムの正常終了を表す。
8. **呼び出しより前（`main` より前）にプロトタイプ宣言を書く**（例: `int square(int x);`，末尾に `;`）。コンパイラがその位置で引数と戻り値の型を確認できるようにするため。課題4の `functions.c` がこの形。

---

## チェックリスト

| 項目 | どこで確認できるか |
| --- | --- |
| 正常な値だけでなく，課題に示された境界の値でも確認した | 課題1の {0}・`n = 1`（本体 0 回）と最初・最後が最大の配列（`Maximum` の `variant_zero`〜`variant_last`），課題2の全要素 0（`ColumnSum` の `variant_zero`），課題3の初期値 0・−1（`ValueCopy` の `variant_x_0`・`variant_x_m1`），課題4の `power(2, 0)`・`power(5, 5)` と範囲の端（`Functions` の `variant_a_…`），発展の `n = 1` と {100, 100, 100}（`SumMean` の `variant_zero_n_1`・`variant_hundred_n_3`）。すべて自動テストで確認済み |
| 警告を確認し，原因を説明・修正した | 全プロジェクトが GCC 13.3／Clang 18.1 の `-Wall -Wextra -Wpedantic -Werror` で警告 0（MSVC `/W4` で警告になる書き方 ―― VLA，`double` から `float` への暗黙の変換，宣言のない呼び出し ―― も避けている。誤りを示すためにわざと書いた `Maximum` の `return_in_loop` 版と確認問題6 の `shadow_count` 版だけは，その警告を版ごとに抑止し理由を書いている）。CI の MSVC `/W4 /WX` でも成功。よく出る警告: プロトタイプ宣言なし（C4013），`return` がループ内で値を返さない経路（C4715），`double` から `float` への変換（C4244/C4305），グローバル変数の隠蔽（C4459）。課題1・4・確認問題6 で説明 |
| 自分の言葉で，処理の流れと使った型を説明できる | 課題1の `best` の追跡表，課題2の訪問順の表，課題4の関数の型の表（`float average(float, float)`，`int power(int, int)`），発展の `(double)` の説明 |
| 添字の範囲と，関数に渡す要素数が一致している | 課題1・発展で配列の大きさと渡す長さに同じ `COUNT`／`n` を使う。課題2の `table[col][row]` が範囲外になる理由，確認問題2・4 |
| 値を返すこと，変数へ代入すること，画面へ表示することを区別できる | 課題3の 3 つの呼び出し方の表，課題4の「戻り値と表示を分ける」，確認問題5（`variant_plus_one`）・7 |
