# 第13回 演習 解答・解説（メモリ管理）

- 演習ページ: <https://t-yokoga.github.io/softprac1/ex13/>（資料リポジトリの `docs/ex13.md`）
- 講義ページ: <https://t-yokoga.github.io/softprac1/lec13/>（`docs/lec13.md`，例題は `docs/sample/13/`）

この回は「確保できたら使う」だけでなく，**誰が初期化し，誰が解放し，失敗したら何を残すか**を追跡する回です。
すべてのプログラムは AddressSanitizer・UBSan（Linux では LeakSanitizer も有効）付きでテストし，リーク・二重解放・解放後の使用が出ないことを確認しています。

## プロジェクト一覧

| 課題 | プロジェクト | ソース | テスト数 |
| --- | --- | --- | --- |
| 課題1・課題2 | `Dynamic` | [dynamic.c](Dynamic/dynamic.c)，[CMakeLists.txt](Dynamic/CMakeLists.txt) | 21（うち書き換え版 5） |
| 課題2「追加：独立したコピー」 | `DynamicCopy` | [dynamic.c](DynamicCopy/dynamic.c)，[CMakeLists.txt](DynamicCopy/CMakeLists.txt) | 16（うち書き換え版 1） |
| 課題3 | `NewPoint` | [new_point.c](NewPoint/new_point.c)，[versions/return_styles.c](NewPoint/versions/return_styles.c)，[CMakeLists.txt](NewPoint/CMakeLists.txt) | 5（うち書き換え版・比較用 4） |
| 課題3「失敗を模擬する」 | `NewPointFail` | [new_point.c](NewPointFail/new_point.c)，[CMakeLists.txt](NewPointFail/CMakeLists.txt) | 2（うち書き換え版 1） |
| 課題4 | （実行しない。この README で解答） | — | — |
| 発展1 | `GrowArray` | [grow_array.c](GrowArray/grow_array.c)，[CMakeLists.txt](GrowArray/CMakeLists.txt) | 9（うち書き換え版 8） |
| 発展1「`realloc`の失敗を模擬する」 | `GrowArrayFail` | [grow_array.c](GrowArrayFail/grow_array.c)，[CMakeLists.txt](GrowArrayFail/CMakeLists.txt) | 3（うち書き換え版 2） |
| 発展2 | `StorageCount` | [count.c](StorageCount/count.c)，[CMakeLists.txt](StorageCount/CMakeLists.txt) | 3（うち書き換え版 2） |
| 発展2「共有変数の宣言」 | `SharedCount` | [counter.h](SharedCount/counter.h)，[counter.c](SharedCount/counter.c)，[main.c](SharedCount/main.c) | 1 |
| 発展2 変更1（リンクエラー） | `_SharedCountNoDef`（ビルドしない） | [counter.c](_SharedCountNoDef/counter.c) ほか | — |
| 発展2 変更2（リンクエラー） | `_SharedCountDupDef`（ビルドしない） | [main.c](_SharedCountDupDef/main.c) ほか | — |
| 発展3 | `DynamicVector` | [vector.h](DynamicVector/vector.h)，[vector.c](DynamicVector/vector.c)，[vector_main.c](DynamicVector/vector_main.c)，[CMakeLists.txt](DynamicVector/CMakeLists.txt) | 2（うち書き換え版 1） |
| 発展3「途中で失敗した場合」 | `DynamicVectorFail` | [vector.c](DynamicVectorFail/vector.c)，[CMakeLists.txt](DynamicVectorFail/CMakeLists.txt)（`vector_main.c`・`vector.h` は `DynamicVector` のもの） | 4（うち書き換え版 3） |

合計 66 テスト（うち書き換え版・比較用 27）。

### 失敗を模擬する版・値を変えた版の置き方

各フォルダのソース（本体）は，演習ページの期待する表示を出す版です。表示が変わらない断片（6 つの役割のコメント，複合リテラル）と，演習ページが正常版に「追加します」と指示する断片（課題2の逆順，発展3の `vector_get(result, 2, &out)`。どちらも表示が 1 行増える）は本体に反映しました。
値を変えて試す版，確認のために `printf` を差し込む版は，本体を変えずに書き換えた版（variants）としてテストしています。

演習ページは「正常版を残した別プロジェクトかコピーで行い，完了したら試験設定を戻す」と指示しています。そこで次のようにしました。

- **正常版**（`NewPoint`，`GrowArray`，`DynamicVector`）は，試験用の関数を含まない，試験設定を戻した正常版（`malloc`／`realloc` を直接呼ぶ版）です。
- **模擬する版**は演習ページのとおり別プロジェクトのコピーにしました: `NewPointFail`（`point_allocate`，`simulate_failure = 1`），`GrowArrayFail`（`try_resize`，`simulate_failure = 1`），`DynamicVectorFail`（`vector_allocate`，`fail_on_call = 2`）。
  `DynamicVectorFail` は書き換える `vector.c` だけを持ち，`vector_main.c` と `vector.h` は `../DynamicVector` のものを使います（`CMakeLists.txt` で指定）。
  学生は 3 ファイルをコピーした別プロジェクトを作り，その中の `vector.c` だけを書き換えます。ここでは同じ内容の 2 ファイルを重複させないために正常版を参照しています。
- 値や書き方を変えて試す版（`simulate_failure = 0`，`fail_on_call = 0，1，3`，発展1の `old_n`・`new_n` の組，`Point` の値，複合リテラル前の 2 文の版，`count` の 3 種類，課題2の全要素交換）と，確認用の `printf` を差し込む版（課題1の追跡表，課題2の交換の組，発展3の解放後の `NULL`）は，
  共通関数 `softprac_add_variant`（`cmake/SoftpracVariant.cmake`）で**ソースの文字列を学生と同じように書き換えた別の実行ファイル**としてビルドし，`<プロジェクト>/variants/tests/` の期待値でテストしています。
  フォルダのソース（本体）は書き換えません。どの文字列をどう書き換えたかは各フォルダの `CMakeLists.txt` に書いてあります（書き換えた版のファイル先頭のコメントも，その版の内容に合わせて書き換えています）。
- 課題3「戻り方を比較する」の比較コードは別ソース [NewPoint/versions/return_styles.c](NewPoint/versions/return_styles.c) にし，置換なしの variant `return_styles` としてテストしています。
- 演習ページがコマンドライン引数を使うのは課題1（`Dynamic`）だけです。発展1の `GrowArray` も演習ページどおり `old_n = 3`，`new_n = 5` を `main` の中に書き，境界の表の組は値を書き換えた版で確かめます（テストのために引数を追加することはしていません）。

Visual Studio で 1 つのプロジェクトだけを使う場合は，学生と同じく `simulate_failure` や `fail_on_call` の値を書き換えて 1 回ずつビルド・実行し直せば同じ結果になります。

### 実行結果の表記

実行例は Linux（GCC 13，x86-64）で実際に実行した出力です。`>` の行がコマンド（引数）で，標準出力と標準エラー出力をコンソールに表示される順に並べ，最後に終了コードを書きました。
Windows（Visual Studio，x64）でも表示は同じです（`%zu` などは VS2015 以降の UCRT で使えます）。環境で変わる値は各所に注記しました。

---

## 課題1　動的配列（`Dynamic`）

### 要点

起動引数の個数を**検査してから**バイト数を計算し，`malloc` の戻り値を確認して，初期化してから読み，最後に `free` します。
確保前のエラーには解放対象がなく，確保後のすべての終了経路では解放が必要，という区別がポイントです。

### 準備（起動引数の設定）

- Visual Studio（プロジェクト方式）: ソリューションエクスプローラーでプロジェクトを右クリック →「プロパティ」→「構成プロパティ」→「デバッグ」→「コマンド引数」に `5` だけを入力します。**実行ファイル名（`Dynamic.exe`）は含めません**（`argv[0]` は自動で渡される）。
  ダイアログ上部の「構成」と「プラットフォーム」を，実際に実行する構成（ツールバーの `Debug` と `x64`）に合わせてから設定します。
- よくある誤り: `Release` や `Win32` の構成に引数を設定し，`Debug | x64` で実行している。その構成には引数がないので，`argc` が 1 になり `usage: Dynamic count (1..1000)` と表示して終了コード 1 で終わります。プログラムの誤りではなく設定の誤りです。
- このリポジトリ（CMake のフォルダーを開く方式）では，[Dynamic/run.args](Dynamic/run.args) の `5` が既定の引数になります（Visual Studio は `.vs/launch.vs.json`）。別の値で試すときは，起動構成の `args`（Visual Studio は `.vs/launch.vs.json`，VS Code は `.vscode/launch.json` の「引数つきで実行」）を書き換えます。
- 予測: `5` なら `n=5 sum=15 mean=3.0`。0，-1，1001，`abc` などは**確保の前に**診断を出して終了し，合計は表示されない。

### 解答コード

[Dynamic/dynamic.c](Dynamic/dynamic.c)。講義の `dynamic.c` に，演習ページの 6 つの役割のコメント `(1)`〜`(6)` と，課題2の逆順処理を加えた版（本体）です。

```c
    // (1) 引数の個数と数値を調べる（数字がない・末尾に余計な文字・long の範囲外・1〜1000 以外を拒否）
    ...
    // (2) 有効な要素数へ変換する（1 以上を確認済みなので，負数が size_t へ回り込むことはない）
    size_t n = (size_t)count;
    int *values = NULL;

    // (3) 必要バイト数 n * sizeof *values を表せるかを，掛け算の前に除算で調べる
    if (n > SIZE_MAX / sizeof *values) { ... }

    // (4) 領域を確保し，失敗なら要素を使わず終了する（まだ何も確保していないので解放は不要）
    values = malloc(n * sizeof *values);
    if (values == NULL) { ... }

    // (5) 値を書き込んでから合計を計算する（有効な添字は 0〜n-1 なので i < n）
    ...
    // (6) 使い終わった領域を解放する（values は確保した先頭を指したまま）
    free(values);
    values = NULL;
```

講義の例題から変えたのは，平均の計算を `(double)sum / (double)n` と両方明示的に変換した点だけです（`size_t` から `double` への変換を書き手の意図として明示するため。CI の MSVC 19.51 `/W4 /WX` Debug でこの回の全プロジェクトが警告なしでビルドできることを確認しています）。

### 実行結果

```text
> Dynamic 1
n=1 sum=1 mean=1.0
reversed: 1
（終了コード 0）
> Dynamic 5
n=5 sum=15 mean=3.0
reversed: 5 4 3 2 1
（終了コード 0）
> Dynamic 1000
n=1000 sum=500500 mean=500.5
reversed: 1000 999 998 997 ...（中略）... 3 2 1
（終了コード 0）
> Dynamic 0
count must be 1..1000
（終了コード 1）
> Dynamic -1
count must be 1..1000
（終了コード 1）
> Dynamic 1001
count must be 1..1000
（終了コード 1）
> Dynamic abc
count must be 1..1000
（終了コード 1）
> Dynamic 3x
count must be 1..1000
（終了コード 1）
> Dynamic ""
count must be 1..1000
（終了コード 1）
> Dynamic 999999999999999999999999
count must be 1..1000
（終了コード 1）
> Dynamic
usage: Dynamic count (1..1000)
（終了コード 1）
> Dynamic 5 6
usage: Dynamic count (1..1000)
（終了コード 1）
> Dynamic +5
n=5 sum=15 mean=3.0
reversed: 5 4 3 2 1
（終了コード 0）
```

エラーのメッセージはすべて標準エラー出力で，標準出力には何も出ません（テストの `.out` が空であることで確認しています）。

### 検証表（記入例）

| 引数 | 結果の予測（＝実行結果） | 確認する点 |
| --- | --- | --- |
| 1 | `n=1 sum=1 mean=1.0`，`reversed: 1`。終了コード 0 | 最小個数。要素は `values[0]` だけ |
| 5 | `n=5 sum=15 mean=3.0`，`reversed: 5 4 3 2 1`。終了コード 0 | 通常値。20 バイト（`sizeof(int)` が 4 の場合）を確保 |
| 1000 | `n=1000 sum=500500 mean=500.5`，逆順は 1000 から 1。終了コード 0 | 上限。合計 500500 は `long long` に十分収まる |
| 0，-1，1001 | `count must be 1..1000`（stderr），終了コード 1 | 範囲検査で**確保前に**終了。合計は表示されない |
| `abc`，`3x`，空引数`""` | `count must be 1..1000`（stderr），終了コード 1 | `abc` と `""` は数字がなく `end == argv[1]`。`3x` は `*end == 'x'` で余計な文字 |
| 999999999999999999999999 | `count must be 1..1000`（stderr），終了コード 1 | `strtol` が `LONG_MAX` を返し `errno == ERANGE` |
| 指定なし，5 6 | `usage: Dynamic count (1..1000)`（stderr），終了コード 1 | `argc != 2`。引数の不足・過剰 |

- どのエラーも「何も表示されずに落ちた」のではなく，**診断を出して `return 1` で意図的に終了**しています。終了コードは Visual Studio の出力ウィンドウ（「…はコード 1 (0x1) で終了しました」）で確認できます。
- `strtol` は先頭の空白と `+` を受け付けるので，`+5` は 5 として受理されます（テスト `plus_sign`）。これは講義の説明どおりの仕様です。
- `long` は Windows（MSVC）では 32 ビット，Linux x64 では 64 ビットです。たとえば `3000000000` は Windows では `ERANGE`，Linux では「1000 より大きい」で拒否されます。経路は違っても結果（拒否）は同じです。

### 確保量を説明する

`n=5` で `sizeof *values` が 4 なら，必要量は 5 × 4 = 20 バイトです。確認のために一時的に次の行を追加して実行しました（本体には入れていません。`sizeof values` が環境で変わるため，テストにはせず実行例だけを載せます）。

```c
printf("sizeof *values=%zu sizeof values=%zu bytes=%zu\n", sizeof *values, sizeof values, n * sizeof *values);
```

```text
> Dynamic 5
sizeof *values=4 sizeof values=8 bytes=20
n=5 sum=15 mean=3.0
reversed: 5 4 3 2 1
```

- `sizeof *values` は**要素 1 個**（`int`）の大きさで，Windows x64・Linux x64 とも 4 です。
- `sizeof values` は**ポインタ変数自身**の大きさで，x64 では 8，x86（32 ビット）では 4 です。確保したバイト数（20）とは無関係で，`sizeof values / sizeof values[0]` としても個数 5 は復元できません（x64 なら 2 になる）。
- `values` の型は `int *` であって配列ではないので，個数の情報は `n` として自分で保持する必要があります。

### 追跡表（`n=3`）

| 反復 | `i` | 代入後の `values[i]` | 加算後の `sum` |
| --- | --- | --- | --- |
| 1 回目 | 0 | 1 | 1 |
| 2 回目 | 1 | 2 | 3 |
| 3 回目 | 2 | 3 | 6 |
| （判定） | 3 | — | `i < n` が偽なので終了 |

ループ内に `printf("i=%zu values[i]=%d sum=%lld\n", i, values[i], sum);` を差し込んだ版（variants の `trace`）を `n=3` で実行した結果です。

```text
> Dynamic_trace 3
i=0 values[i]=1 sum=1
i=1 values[i]=2 sum=3
i=2 values[i]=3 sum=6
n=3 sum=6 mean=2.0
reversed: 3 2 1
```

本体を `3` で実行した結果（`n=3 sum=6 mean=2.0`，`reversed: 3 2 1`）もテスト `three_3` にしています。

```text
values ─→ [  1  ][  2  ][  3  ] │ ここから先は確保していない
添字          0      1      2    │   3
          ←── 3 × sizeof(int) = 12 バイト ──→
```

確保したのは添字 0〜2 の 3 要素だけです。`i <= n` にすると `i == 3` で `values[3]` に書き込み，確保した 12 バイトの**直後**へ書く範囲外アクセス（未定義動作）になります。
実際に `i <= n` に変えた版を AddressSanitizer 付きで `n=3` で実行すると，`ERROR: AddressSanitizer: heap-buffer-overflow`，`WRITE of size 4 ... is located 0 bytes after 12-byte region` と報告されました。
サニタイザなしでは何事もなく動いて見えることがあるので，「動いたから正しい」とは言えません。

### 採点のポイント・よくある誤り

- 6 つの役割のコメントが処理の順に付いているか。特に (3) の検査が `malloc` の**前**にあるか（掛け算の後で調べても回り込みは防げない）。
- `count < 1` を検査する前に `(size_t)count` へ変換していないか（-1 が巨大な値になる）。
- `malloc` の戻り値を検査する前に `values[0]` などへ触れていないか。エラー時に `sum` を表示していないか。
- `sizeof(int *)` や `sizeof values` で確保量を計算していないか（`sizeof *values` が正しい）。
- `i <= n` の範囲外アクセス，`free` 忘れ，`free` 後の `values` の使用。
- 検証表で `abc` と `3x` の違い（数字がない／余計な文字がある），`ERANGE` を説明できているか。「エラーになった」だけでなく終了コードと stderr まで確認しているか。
- 環境依存の値（`sizeof values`，アドレス）を固定の正解として書いていないか。

---

## 課題2　配列を逆順にする（`Dynamic`）

### 要点

確保した**同じ領域**の中で，先頭と末尾から組にして `n/2` 回だけ交換します。`malloc` の回数は増やしません。

### 解答コード

[Dynamic/dynamic.c](Dynamic/dynamic.c) の `sum` と `mean` の表示の後，`free(values)` の前に追加しました。

```c
    // 課題2：先頭と末尾から組にして n/2 組だけ交換する（奇数個の中央の要素は動かさない）
    for (size_t i = 0; i < n / 2; ++i) {
        int temp = values[i];
        values[i] = values[n - 1 - i];
        values[n - 1 - i] = temp;
    }
    printf("reversed:");
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", values[i]);
    }
    printf("\n");
```

### 実行結果

```text
> Dynamic 1
n=1 sum=1 mean=1.0
reversed: 1
> Dynamic 2
n=2 sum=3 mean=1.5
reversed: 2 1
> Dynamic 5
n=5 sum=15 mean=3.0
reversed: 5 4 3 2 1
```

### 表（記入例）

| `n` | 交換する添字の組 | 表示される逆順 |
| --- | --- | --- |
| 1 | なし（`n/2 = 0` なのでループは 0 回） | `1` |
| 2 | (0, 1) | `2 1` |
| 5 | (0, 4)，(1, 3)（中央の 2 は交換しない） | `5 4 3 2 1` |

交換のたびに組を表示する行 `printf("swap values[%zu] <-> values[%zu]\n", i, n - 1 - i);` を差し込んだ版（variants の `swap_pairs`。`n=1，2，5` でテスト）の結果です。`n=1` では交換の行が出ません。

```text
> Dynamic_swap_pairs 2
n=2 sum=3 mean=1.5
swap values[0] <-> values[1]
reversed: 2 1
> Dynamic_swap_pairs 5
n=5 sum=15 mean=3.0
swap values[0] <-> values[4]
swap values[1] <-> values[3]
reversed: 5 4 3 2 1
```

`sum` と `mean` は要素の集合が同じなので順序を変えても変わりません。
**奇数個の中央要素を交換しなくてよい理由**: 中央の添字 `m = (n-1)/2` では `n-1-m == m` となり，相手が自分自身です。自分と交換しても値は変わらないので，組を作る必要がありません。

### 考察

- **`n/2` が整数の除算であること**: 小数点以下が切り捨てられるので，`n=5` なら 2 回，`n=1` なら 0 回になります。奇数個のときは中央を除いた組の数と一致し，偶数個のときはちょうど半分です。どちらの場合も「組の数 = 交換の回数」になります。
- **全要素について交換すると元に戻る理由**: `i < n` にすると，前半で (0,4)，(1,3) を交換した後，後半で (3,1)，(4,0) をもう一度交換し，各組を 2 回入れ替えることになります（中央は自分自身と交換）。2 回の交換で元に戻るので，結果は元の順序です。
  `i < n / 2` を `i < n` に書き換えた版（`softprac_add_variant` の `swap_all`）を実行すると，確かに元の順序になりました。
  ```text
  > Dynamic_swap_all 5   （i < n / 2 を i < n に書き換えた版）
  n=5 sum=15 mean=3.0
  reversed: 1 2 3 4 5
  ```
- **`temp` に `free` が不要な理由**: `temp` はループのブロック内の通常の局所変数（自動記憶域）で，ブロックの実行が終わると寿命が自動で終わります。`malloc` などで確保した領域ではないので `free` してはいけません（`free` に渡せるのは動的確保で得た先頭のポインタか `NULL` だけ）。
- **逆順後も `values` が先頭を指していることの利点**: 並べ替えは要素の値を入れ替えただけで，ポインタ `values` は動かしていません。`free` には確保した領域の**先頭のポインタ**を渡す必要があるので，そのまま `free(values)` で正しく解放できます。
  もし `values` 自身を進めながら処理していたら，先頭を別に覚えておかない限り正しく解放できなくなります（`free(values + 1)` は誤り。課題4参照）。

### 追加：独立したコピー（`DynamicCopy`）

演習ページはこの追加課題にプロジェクト名を付けていません。課題2の「同じ領域で逆順にする」と「元の配列を残してコピーだけを逆順にする」は両立しないため，`Dynamic` とは別のプロジェクト `DynamicCopy` にしました。

[DynamicCopy/dynamic.c](DynamicCopy/dynamic.c) の要点:

```c
    // 独立したコピー：ポインタではなく要素をコピーするため，別の領域を確保する
    copy = malloc(n * sizeof *copy);
    if (copy == NULL) {
        fprintf(stderr, "allocation failed\n");
        free(values);   // 先に確保した values はこの経路でも解放する
        return 1;
    }
    for (size_t i = 0; i < n; ++i) {
        copy[i] = values[i];
    }
    // copy だけを逆順にする（values は元の順序のまま残る）
    ...
    // (6) 2 つの領域をそれぞれ解放する
    free(copy);
    copy = NULL;
    free(values);
    values = NULL;
```

```text
> DynamicCopy 1
n=1 sum=1 mean=1.0
values: 1
copy: 1
> DynamicCopy 2
n=2 sum=3 mean=1.5
values: 1 2
copy: 2 1
> DynamicCopy 5
n=5 sum=15 mean=3.0
values: 1 2 3 4 5
copy: 5 4 3 2 1
```

- `int *copy = values;` は**ポインタ値のコピー**で，領域は 1 つのままです。`copy` を通して逆順にすると `values` から見ても逆順になり，さらに両方を `free` すると二重解放になります。
- 要素をコピーするには**別の領域を確保**し，要素を 1 つずつ代入します。所有する領域が 2 つになるので，解放も 2 回（それぞれ 1 回ずつ）必要です。
- `copy` の確保に失敗した経路では，すでに確保済みの `values` を解放してから終了します（この経路のリークが最もよくある誤り）。
  この経路は，`copy = malloc(n * sizeof *copy);` を `copy = NULL;` に書き換えた版（variants の `copy_alloc_fail`。課題3の失敗模擬と同じ考え方）でテストしています。`free(values)` を消すと LeakSanitizer が `20 byte(s) leaked` を報告してテストが失敗することも確かめました。
  ```text
  > DynamicCopy_copy_alloc_fail 5   （copy の確保失敗を模擬した版）
  n=5 sum=15 mean=3.0
  allocation failed
  （終了コード 1）
  ```
- `copy` も同じ `int` の `n` 要素なので，`n > SIZE_MAX / sizeof *values` の検査がそのまま `copy` のバイト数にも有効です（演習ページの「サイズ検査はすでに済んでいる」）。

### 採点のポイント・よくある誤り

- 新しい配列を `malloc` して逆順にコピーしていないか（課題2は**同じ領域**で並べ替える指示）。
- ループ条件を `i < n` にして元に戻っている，`values[n - i]` として範囲外（`i=0` で `values[n]`）を読んでいる。
- 逆順処理を `free` の後に置いている（解放後の使用）。
- 追加課題で `int *copy = values;` としている，`copy` の確保失敗時に `values` を解放していない，`copy` を解放し忘れている。

---

## 課題3　構造体を確保する関数（`NewPoint`）

### 要点

関数の中で確保した `Point` の**所有権を呼び出し元へ移す**設計です。成功・失敗と解放責任を関数の契約（コメント）に書き，呼び出し元は `NULL` を検査してから使い，最後に `free` します。

### 解答コード

[NewPoint/new_point.c](NewPoint/new_point.c)

```c
typedef struct {
    double x;
    double y;
} Point;

// 成功なら初期化済みの Point を返し，呼び出し元が free する．失敗なら NULL を返す．
Point *new_point(double x, double y)
{
    Point *p = malloc(sizeof *p);
    if (p == NULL) {
        return NULL;            // 失敗時はメンバに触れない
    }
    *p = (Point){.x = x, .y = y};   // 左辺は p ではなく本体の *p
    return p;                   // p の寿命は終わるが，本体は free まで有効
}

int main(void)
{
    Point *p = new_point(3.0, 4.0);
    if (p == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    printf("x=%.1f y=%.1f\n", p->x, p->y);
    free(p);                    // 所有者の main が解放する
    p = NULL;
    return 0;
}
```

### 実行結果（予測と記録）

- 予測: `new_point` が (3.0, 4.0) を持つ `Point` を返し，`main` が `x=3.0 y=4.0` と表示して解放し，終了コード 0。
- 結果:
  ```text
  > NewPoint
  x=3.0 y=4.0
  （終了コード 0）
  ```
- 理由: `malloc` した本体は `new_point` から戻った後も `free` まで寿命が続きます。`new_point` の局所変数 `p` の寿命は終わりますが，その値（本体のアドレス）は戻り値として `main` の `p` にコピーされているので，`main` から本体を使えます。

### 関数の契約と寿命の表

| 場面 | `new_point`内の`p` | 動的な`Point`本体 |
| --- | --- | --- |
| 確保成功直後 | 本体を指す | 初期化前（`x`，`y` は不定値。読んではいけない） |
| メンバへの代入後 | 本体を指す | `x`，`y`が有効 |
| `return`後 | 局所変数としての寿命は終了 | 呼び出し元の`p`から使える（所有者は `main`） |
| `main`の`free`後 | 関数はすでに終了 | 寿命が終了し，再参照しない（`main` の `p` は `NULL` にした） |

契約コメントがないと，「`new_point` という名前だから呼び出し元が解放するのだろう」「ライブラリが管理するのだろう」と推測に頼ることになります。C の型（`Point *`）は所有権を表さないので，コメントで明示します。

### 複合リテラルで初期化する

最初は次の 2 文で書き，後で複合リテラル 1 文へ置き換えました（本体は置き換え後の版）。

```c
    p->x = x;
    p->y = y;
```

2 文の版（variants の `two_statements`）を実行した結果も `x=3.0 y=4.0` で，同じ出力でした。`*p = (Point){.x = x, .y = y};` は，複合リテラルで作った `Point` の値を確保済みの本体 `*p` へ構造体ごと代入します。一時的な値のアドレスを返しているわけではありません。`NULL` 判定は複合リテラルの前に残します（`NULL` の `*p` へ代入すると未定義動作）。

値を変えた版（variants の `point_0_0`，`point_m2_5`）:

```text
> NewPoint_point_0_0   （new_point(0.0, 0.0) に書き換えた版）
x=0.0 y=0.0
> NewPoint_point_m2_5   （new_point(-2.0, 5.0) に書き換えた版）
x=-2.0 y=5.0
```

複合リテラルでは名前を挙げた両メンバに値が入ります（挙げなかったメンバがあっても 0 で初期化されます）。`Point` 内に動的なメンバがないので，`main` の `free(p)` 1 回で後始末が終わります。

左辺を `p` にした誤り（`p = (Point){.x = x, .y = y};`）はコンパイルエラーになります。

- MSVC: `error C2440: '=': 'Point' から 'Point *' に変換できません`（英語版: `cannot convert from 'Point' to 'Point *'`）
- GCC: `error: incompatible types when assigning to type 'Point *' from type 'Point'`
- Clang: `error: assigning to 'Point *' from incompatible type 'Point'; take the address with &`

### 失敗を模擬する（`NewPointFail`）

[NewPointFail/new_point.c](NewPointFail/new_point.c) は `NewPoint` のコピーで，`new_point` の前に演習ページの `point_allocate` を追加し，`malloc(sizeof *p)` だけを `point_allocate(sizeof *p)` に変えたものです（`simulate_failure = 1`）。

```text
> NewPointFail   （simulate_failure = 1）
allocation failed
（終了コード 1）
> NewPointFail_simulate_failure_0   （simulate_failure = 0 に戻した版）
x=3.0 y=4.0
（終了コード 0）
```

- `simulate_failure=1` では `point_allocate` が `NULL` を返し，`new_point` は**メンバに触れずに** `NULL` を返し，`main` は `allocation failed` を出して `return 1` します。`p->x` を読む `printf` には到達しません。
- ステップ実行での確認: `main` の `if (p == NULL)` にブレークポイントを置き，F11 で `new_point` へ入ると，`point_allocate` が `NULL` を返して `return NULL;` に進み，`*p = ...` の行が実行されないことが分かります。`main` に戻ると `p` が `0x0000000000000000` で，次に `fprintf` → `return 1` へ進み，`printf("x=...")` の行は通りません。
- `point_allocate` は `errno` を設定しません。この試験で確かめているのは「`NULL` を見て失敗を判定し，安全に終了できること」であり，本物の `malloc` のメモリ不足や OS の診断を再現したわけではありません。
- `const int simulate_failure = 1; if (simulate_failure)` は演習ページのコードどおりです。CI（MSVC 19.51，`/W4 /WX`，Debug）では C4127・C4702 とも出ませんでした（C では `const int` の変数は定数式ではないため，C4127「条件式が定数」の対象になりません）。
  Release 構成（最適化あり）では，到達しない `return malloc(...)` に C4702（到達できないコード）が出る可能性があり，`/WX` 付きならビルドが止まります。試験用の版は Debug 構成で確認します（`GrowArrayFail` の `try_resize` も同じ）。

### 戻り方を比較する

3 つの方法を 1 つのプログラム [NewPoint/versions/return_styles.c](NewPoint/versions/return_styles.c) にまとめて確認しました（置換なしの variant `return_styles` としてテスト）。

```c
// (a) 値として返す：本体は呼び出し元の変数にコピーされる。失敗はなく，解放も不要
Point make_point(double x, double y)
{
    return (Point){.x = x, .y = y};
}

// (b) 呼び出し元が用意した Point へ書き込む：領域の寿命・所有者は呼び出し元
int init_point(Point *out, double x, double y)
{
    if (out == NULL) {
        return 0;
    }
    *out = (Point){.x = x, .y = y};
    return 1;
}

// (c) malloc した Point * を返す：new_point と同じ（成功時は呼び出し元が free する．失敗なら NULL）
```

```text
a: x=3.0 y=4.0
b: x=3.0 y=4.0
c: x=3.0 y=4.0
```

| 方法 | 本体の寿命 | 失敗の可能性 | 解放責任 | 向いている場面 |
| --- | --- | --- | --- | --- |
| (a) 値として返す | 受け取った変数（例: `main` の局所変数）の寿命 | なし | なし（自動記憶域） | 小さな構造体を 1 個作るだけ |
| (b) 呼び出し元の `Point *` へ書き込む | 呼び出し元が用意した領域の寿命 | 引数の検査（`NULL`）程度 | 呼び出し元（関数は借りて書くだけ） | 領域の置き場所を呼び出し元が決めたいとき |
| (c) `malloc` した `Point *` を返す | `free` されるまで（関数や呼び出し元のブロックを越えて生きる） | 確保失敗で `NULL` | 呼び出し元（所有権が移る） | 個数や寿命が実行時に決まる，不透明型で中身を隠すとき（発展3） |

1 個の小さな `Point` を作るだけなら (a) で十分で，動的確保は必須ではありません。(c) は失敗の検査と `free` の責任が増える代わりに，寿命を自由に決められます。

### 採点のポイント・よくある誤り

- 契約コメント（成功時は初期化済みを返し呼び出し元が `free`，失敗なら `NULL`）が `new_point` の前にあるか。
- `malloc` の戻り値の検査より前に `p->x` へ代入している。`main` 側で `NULL` 検査をしていない。
- 局所変数 `Point pt;` のアドレス `&pt` を返している（寿命切れ）。
- `free` の忘れ，または `new_point` の中で `free` してから返している。
- 複合リテラルで左辺を `p` にしている（型エラー）。`sizeof(Point *)` で確保している（本体より小さい）。
- 失敗模擬で，正常版を残さずに書き換えたまま提出している／試験設定を戻していない。

---

## 課題4　コードレビュー

### 指摘

```c
int *b = a;
free(a);
a = NULL;
printf("%d\n", b[0]);
free(b);
```

1. `int *b = a;` はポインタ値のコピーで，`a` と `b` は**同じ 1 つの領域**を指す別名です。所有者が 2 人になったわけではありません。
2. `free(a);` で領域の寿命が終わります。`a = NULL;` が書き換えるのは `a` だけで，`b` には古いアドレスが残ります（ダングリングポインタ）。
3. `printf("%d\n", b[0]);` は**解放後の使用**（未定義動作）。たまたま元の値が表示されても，正しい根拠にはなりません。
4. `free(b);` は同じ領域を 2 回解放する**二重解放**（未定義動作。ヒープ管理情報の破壊や異常終了の原因）。
5. さらに，`a` が `malloc` で確保しただけなら `a[0]` に値を代入する前に読むことになり，未初期化領域の読み取りにもなります。

### 修正版

```c
int *b = a;               /* b は借用。所有者は a */
printf("%d\n", b[0]);     /* 解放する前に使う（a[0] は代入済みとする） */
b = NULL;                 /* 借用を終える */
free(a);                  /* 所有者が 1 回だけ解放する */
a = NULL;
```

別名を作らず `printf("%d\n", a[0]);` としてもよいです。要点は「使い終わってから」「所有者が 1 回だけ」解放し，解放後はどの別名からも参照しないことです。

### 追加のレビュー

| 断片 | 問題が起きる理由 | 安全な順序・書き方 |
| --- | --- | --- |
| `int *p; free(p);` | `p` は初期化されていない自動変数で，不定値（でたらめなアドレス）が入っている。確保していないアドレスを `free` に渡すのは未定義動作（異常終了やヒープ破壊） | `int *p = NULL;` と初期化しておく。確保したら `NULL` 検査→使用→`free(p); p = NULL;`。確保しなかった経路でも `free(NULL)` は何もしないので安全 |
| `int a[3]; free(a);` | `a` は自動記憶域の配列で，`malloc` 等で確保した領域ではない（確保したのはコンパイラ・実行環境）。`free` に渡すのは未定義動作 | `free` しない。ブロックの終わりで寿命が自動で終わる。`free` は `malloc`／`calloc`／`realloc` が返したポインタにだけ使う |
| `free(values + 1);` | `values + 1` は 2 番目の要素のアドレスで，確保した領域の**先頭ではない**。`free` には確保関数が返した先頭のポインタを渡す必要があり，途中のアドレスは未定義動作 | `free(values);` と先頭を渡す。走査用には添字か別のポインタ変数を使い，`values` 自身は動かさない |
| `p = malloc(3 * sizeof *p); p = NULL;` | 確保した領域を指す唯一のポインタを上書きしたため，その領域へ到達・解放する手段がなくなる（メモリリーク）。`p = NULL` は解放の代わりにならない | `p = malloc(...)`→`NULL` 検査→使用→`free(p);`→`p = NULL;` の順にする |
| `p = realloc(p, bytes);` | `realloc` が失敗すると `NULL` が返り，それを `p` に代入すると元の領域（失敗時もまだ有効）を指す手段を失う（リーク）。元のデータも使えなくなる | `int *next = realloc(p, bytes); if (next == NULL) { /* p は有効。free(p) などの後始末 */ } else { p = next; }`。事前に `bytes` が正で積があふれないことを検査する（発展1） |
| `free(buffer); free(buffer->data);` | 本体を先に解放したので，`buffer->data` を読むのは**解放後の使用**。読めたとしても正しい値の保証はなく，`data` の配列もリークしうる | 内側から外側へ: `free(buffer->data); free(buffer); buffer = NULL;`（講義 7.1 の解放順） |
| `malloc(n * sizeof p)` | `sizeof p` は**ポインタ変数 `p` 自身**の大きさ（x64 で 8，x86 で 4）で，要素の大きさではない。`int *p` なら 2 倍の過大確保で誤りが隠れ，`Point *p`（16 バイト）や x86 の `double *p` では必要量より小さくなり範囲外アクセスになる | `n > SIZE_MAX / sizeof *p` を検査してから `malloc(n * sizeof *p)` |

### 所有者を図にする

**(1) `main` が確保し，表示関数が借りて表示し，`main` が解放する（借用）**

```text
main:   values = malloc(n * sizeof *values) ──→ [ 1 ][ 2 ][ 3 ]   所有者: main
          │
          │ print_array(values, n)          （アドレスと個数を「貸す」）
          ▼
print_array(const int *p, size_t n): p ┈┈借用（読むだけ）┈┈→ 同じ領域
          │ return（p の寿命は終わるが，領域はそのまま。free しない）
          ▼
main:   free(values); values = NULL;  ──→ 領域の寿命が終わる
```

**(2) 生成関数が確保し，`main` へ所有権を渡す（所有権の移動）**

```text
new_point:  p = malloc(sizeof *p) ──→ [ x | y ]   （初期化までは new_point が責任を持つ）
              │
              │ return p   ……契約「成功時は呼び出し元が free する」により所有権が移る
              ▼
main:       p ─────────────────────→ [ x | y ]   所有者: main
              │ 使用（p->x，p->y）
              ▼
main:       free(p); p = NULL;  ──→ 寿命が終わる
```

**説明**: どちらの場合も，関数との間でやり取りしているのは同じ「アドレスの値」です。C の型（`int *`，`Point *`）には「借用」か「所有権の移動」かの区別がないので，ポインタを関数に渡した（返した）だけで解放責任が自動で移ることはありません。
どちらにするかは関数の仕様（契約コメント・関数名）で決め，表示関数のように借りるだけの関数は `free` せず，生成関数から受け取った側は必ず `free` します。
(1) で表示関数が勝手に `free` すると，`main` の後の使用が解放後の使用に，`main` の `free` が二重解放になります。

### 採点のポイント・よくある誤り

- 最初のコードで「`a = NULL` にしたので安全」と答えている（`b` は `NULL` にならない）。解放後の使用と二重解放の**両方**を指摘しているか。
- `int a[3]; free(a);` を「解放し忘れないので良い」としている。`free(values + 1)` の問題を「1 要素ずれるだけ」としている。
- `p = NULL` を解放と混同している。`realloc` の直接代入の危険を「失敗しにくいので問題ない」としている。
- 修正版の順序（内側から外側，使ってから解放，成功してから持ち替え）を具体的に書いているか。
- 図で所有者が常に 1 つに決まっているか。「関数に渡したから関数が解放する」と書いていないか。

---

## 発展1　`calloc`と`realloc`で配列を拡張する（`GrowArray`）

### 要点

`calloc` は 0 で初期化された配列を確保し，`realloc` は大きさを変えます。`realloc` の結果は**別の変数で受け取り，成功してから持ち替え**，増えた部分は読む前に初期化します。失敗時は元の領域を解放して終了します。

### 解答コード

[GrowArray/grow_array.c](GrowArray/grow_array.c)。演習ページどおり，`main` の先頭に個数を書きます。

```c
    size_t old_n = 3;   // 元の個数（境界の表の値に書き換えて試す）
    size_t new_n = 5;   // 変更後の個数
```

処理の順序:

1. `old_n` が 1〜1000 か → 違えば**最初の確保前に**終了。
2. `calloc(old_n, sizeof *p)` と `NULL` 検査。全要素が 0 であることを表示して確認し，1〜`old_n` を代入。
3. `realloc` の前に `new_n` が 1〜1000 か，`new_n * sizeof *p` が `size_t` で表せるかを検査 → 違えば**確保済みの領域を解放して**終了。
4. `int *next = realloc(p, new_n * sizeof *p);` → `NULL` なら `p` を解放して終了。成功なら `p = next;`。
5. 増えた部分 `p[old_n]`〜`p[new_n-1]` だけに `old_n+1`〜`new_n` を代入（縮小・同じ個数ならループは 0 回）。表示して `free`。

上限 1000 は `#define MAX_COUNT 1000` の 1 か所で決め，検査とメッセージ（`"old_n must be 1..%d\n", MAX_COUNT`）の両方に使っているので，上限を変えても表示がずれません。個数は `size_t` なので負にはならず，「1 未満」は `old_n == 0` で調べます。値は今は定数ですが，書き換えて試す前提なので検査を省略しません（境界の表の (3, 0)，(0, 5)，(3, 1001) の行はこの検査の確認です）。

```c
    // 結果は別の変数で受け取り，成功するまで p を上書きしない
    int *next = realloc(p, new_n * sizeof *p);
    if (next == NULL) {
        fprintf(stderr, "reallocation failed\n");
        free(p);                        // 失敗時も元の領域は有効なので解放する
        return 1;
    }
    p = next;                           // 成功後は返されたポインタだけを使う
    next = NULL;

    // 増えた部分 p[old_n]〜p[new_n-1] は未初期化なので，読む前に代入する（縮小時は 0 回）
    for (size_t i = old_n; i < new_n; ++i) {
        p[i] = (int)i + 1;
    }
```

### 実行結果と境界の表

本体（3→5）と，`old_n`・`new_n` を書き換えた版（variants。実行ファイル名は `GrowArray_<ケース名>`）の実行結果です。

```text
> GrowArray   （old_n = 3，new_n = 5）
calloc: 0 0 0
before: 1 2 3
after: 1 2 3 4 5
（終了コード 0）
> GrowArray_same_3_to_3   （old_n = 3，new_n = 3）
calloc: 0 0 0
before: 1 2 3
after: 1 2 3
（終了コード 0）
> GrowArray_shrink_3_to_1   （old_n = 3，new_n = 1）
calloc: 0 0 0
before: 1 2 3
after: 1
（終了コード 0）
> GrowArray_grow_1_to_4   （old_n = 1，new_n = 4）
calloc: 0
before: 1
after: 1 2 3 4
（終了コード 0）
> GrowArray_new_zero_3_to_0   （old_n = 3，new_n = 0）
calloc: 0 0 0
before: 1 2 3
new_n must be 1..1000
（終了コード 1）
> GrowArray_old_zero_0_to_5   （old_n = 0，new_n = 5）
old_n must be 1..1000
（終了コード 1）
> GrowArray_new_over_3_to_1001   （old_n = 3，new_n = 1001）
calloc: 0 0 0
before: 1 2 3
new_n must be 1..1000
（終了コード 1）
```

| `old_n` | `new_n` | 確認すること | 結果 |
| --- | --- | --- | --- |
| 3 | 5 | 先頭3要素を保持し，2要素を初期化 | `after: 1 2 3 4 5`。1，2，3 は `realloc` で保持され，`p[3]`，`p[4]` に 4，5 を代入 |
| 3 | 3 | 同じ個数でも成功後は返されたポインタを使用 | `after: 1 2 3`。初期化ループは 0 回。`p = next;` で持ち替えてから使う |
| 3 | 1 | 先頭の1だけが有効 | `after: 1`。有効な添字は 0 だけ |
| 1 | 4 | 1を保持し，2，3，4を追加 | `after: 1 2 3 4` |
| 3 | 0 | 確保済み領域を解放してエラー終了 | `new_n must be 1..1000`，終了コード 1。`realloc` は呼ばず `free(p)` |
| 0 | 5 | 最初の確保前にエラー終了 | `old_n must be 1..1000`，終了コード 1。何も表示・確保しない |
| 3 | 1001 | 上限違反で，元の領域を解放して終了 | `new_n must be 1..1000`，終了コード 1。`free(p)` してから終了 |

テストにはこのほか `old_n = 1，new_n = 1000`（上限まで拡張）と `old_n = 1001，new_n = 5`（確保前に終了）も入れています。
解放を忘れると LeakSanitizer がリークを報告してテストが失敗するので，`new_n = 0` と `new_n = 1001` の経路で `free(p)` していることもテストで確認できます。

**`realloc` 後の `p[3]` の違い**

- 拡張（3→5）: `p[3]` は新しい領域の正しい要素です。ただし `realloc` は増えた部分を初期化しないので，代入（4）するまでは不定値で，読んではいけません。
- 縮小（3→1）: 新しい領域は 1 要素だけなので，`p[3]`（`p[1]`，`p[2]` も）は確保した範囲の外です。物理的には以前の値が残っていることもありますが，読み書きは範囲外アクセス（未定義動作）です。だから `new_n=1` で `p[3]` を読んで確かめてはいけません。

`calloc` の 0: `calloc` は全ビットを 0 にします。`int` では全ビット 0 が値 0 なので，`calloc: 0 0 0` と表示して確認するのは正しい読み取りです（`malloc` の領域では同じことをしてはいけません）。

### `realloc`の失敗を模擬する（`GrowArrayFail`）

[GrowArrayFail/grow_array.c](GrowArrayFail/grow_array.c) は `GrowArray` のコピーで，`main` の前に演習ページの `try_resize`（`simulate_failure = 1`）を追加し，`realloc` の呼び出しを `try_resize` に置き換えました。`NULL` 分岐では，`free` の直前に `p[0]` を表示します。

```c
    int *next = try_resize(p, new_n * sizeof *p);
    if (next == NULL) {
        // 再確保が失敗した経路だけで元の領域を読む：p はまだ有効で，p[0] は 1 のまま
        fprintf(stderr, "reallocation failed\n");
        printf("p[0]=%d\n", p[0]);     // free する直前に表示する
        free(p);
        return 1;
    }
```

```text
> GrowArrayFail   （simulate_failure = 1，old_n = 3，new_n = 5）
calloc: 0 0 0
before: 1 2 3
reallocation failed
p[0]=1
（終了コード 1）
> GrowArrayFail_simulate_failure_0   （simulate_failure = 0 に戻した版）
calloc: 0 0 0
before: 1 2 3
after: 1 2 3 4 5
（終了コード 0）
```

- 課題3の `point_allocate` は「最初から何も確保できない」失敗でしたが，`realloc` の失敗では**元の領域が残っています**。`p` を上書きしていないので，`p[0]` は 1 のまま読め，`free(p)` で解放できます。
- 縮小（`new_n = 1`）の再確保が失敗する版（variants の `shrink_fail_3_to_1`）でも同じく `p[0]=1` を表示して終了します。
- valgrind でも確認しました（`GrowArrayFail`）: `total heap usage: 2 allocs, 2 frees`（`calloc` と標準出力のバッファ），`All heap blocks were freed -- no leaks are possible`。
- もし `p = realloc(p, ...)` と書いていたら，失敗時に `p` が `NULL` になり，元の 3 要素はリークし，`p[0]` を読むと `NULL` の参照になります。
- `p[0]` を読むのは再確保が**失敗した経路だけ**です。成功した経路で古いポインタ（ここでは `next` に持ち替える前の値）を使うのは誤りです。
- 試験後は元の `realloc` の呼び出しへ戻します（正常版は `GrowArray`）。

### 採点のポイント・よくある誤り

- `p = realloc(p, ...)` と直接代入している（失敗時のリーク）。
- `new_n` の検査を `realloc` の後にしている，`new_n = 0` を `realloc` に渡している（C17 でも扱いが複雑。講義では使わない）。
- `new_n = 0`／`1001` の経路で `free(p)` せずに終了している（LeakSanitizer で検出される）。
- 増えた部分を初期化せずに表示している（`malloc` 同様に不定値）。縮小後も古い個数でループしている（範囲外）。
- 成功後に古いポインタや古い要素へのポインタを使っている。`next` と `p` のアドレスを比べて「移動したか」で処理を分けている（不要）。
- `calloc` の結果を検査していない。`calloc` で 0 になることを `double` やポインタにも一般化している（全ビット 0 が意味上の 0 や `NULL` とは限らない）。

---

## 発展2　`static`変数の寿命を確かめる（`StorageCount`，`SharedCount`）

### 要点

関数内の `static` は**記憶期間**（値をいつまで持つか）を，関数やファイルスコープの変数の前の `static` は**リンケージ**（どこから名前を使えるか）を決めます。ヒープを使わずに値を保持でき，`free` は不要です。

### 解答コード・実行結果

[StorageCount/count.c](StorageCount/count.c)（演習ページのコードにコメントを付けたもの）

```text
> StorageCount
1
2
3
```

### 3種類を比較する（記入例）

| `next_count`内の書き方 | 予測する出力（＝実行結果） | 理由 |
| --- | --- | --- |
| `static int count = 0;` | `1`，`2`，`3` | 静的記憶期間。プログラム開始前に 1 度だけ 0 に初期化され，呼び出しの間も値が残る |
| `int count = 0;` | `1`，`1`，`1` | 自動記憶域。呼ぶたびに新しく作られ 0 で初期化，関数から戻ると寿命が終わる |
| `static int count;`の後に文として`count = 0;` | `1`，`1`，`1` | 値は保持されるが，`count = 0;` は**文（代入）**なので呼ぶたびに実行され，毎回 0 に戻る |

2 行目は `static` を外した版（variants の `auto_count`），3 行目は次のように書き換えた版（variants の `static_assign`）としてテストしました。

```c
static int next_count(void)
{
    static int count;
    count = 0;
    ++count;
    return count;
}
```

```text
> StorageCount_auto_count   （int count = 0; に書き換えた版）
1
1
1
> StorageCount_static_assign   （static int count; の後に count = 0; を書いた版）
1
1
1
```

**`static` の 2 つの役割**

- `static int next_count(void)` の `static` は**内部リンケージ**: `next_count` という名前をこの `.c`（翻訳単位）の中だけで使えるようにします。値の寿命とは関係ありません（関数に寿命はない）。
- 関数内の `static int count = 0;` の `static` は**静的記憶期間**: 名前は関数のブロック内だけで使えます（リンケージなし）が，オブジェクトはプログラム全体の実行中存在します。
  初期化子 `= 0` は**関数を呼ぶたびの代入ではなく**，プログラム開始前に 1 度だけ行われます（C の規則。C++ の「初めて通ったときに初期化」と混同しない）。初期化子がなくても静的記憶期間の整数は 0 になります。

**`count` へ `free` を使わない理由**: `count` は `malloc` などで確保した動的な領域ではなく，静的記憶域にあり，寿命はプログラムの開始から終了までと決まっています。`free` に渡せるのは動的確保で得たポインタだけで，`free(&count)` は未定義動作です。
`malloc` の領域は「確保成功から `free` まで」と寿命を自分で決められる（決めなければならない）のに対し，`static` は寿命が固定で管理不要ですが，個数や大きさを実行時に変えられず，関数を呼ぶ全員で 1 つの値を共有します。

### 第12回との接続：共有変数の宣言（`SharedCount`）

[counter.h](SharedCount/counter.h)，[counter.c](SharedCount/counter.c) は演習ページのとおり，[main.c](SharedCount/main.c) は `counter.h` と `stdio.h` を取り込み，`add_count` を 2 回呼んでから `total` を表示します。

```c
int main(void)
{
    add_count();
    add_count();
    printf("total=%d\n", total);
    return 0;
}
```

```text
> SharedCount
total=2
```

`counter.h` の `extern int total;` は「どこかに定義がある `int total` を参照する」という**宣言**で，実体（定義）は `counter.c` の `int total = 0;` の 1 つだけです。`total` はファイルスコープの変数なので静的記憶期間を持ち，外部リンケージによって両方の `.c` から同じオブジェクトを指します。

**変更 1: `counter.c` の `int total = 0;` だけを外す**（[_SharedCountNoDef](_SharedCountNoDef/)）

各 `.c` は `extern` 宣言があるので**コンパイルは成功**しますが，`total` の実体がどの翻訳単位にもないため**リンクで失敗**します。

- MSVC: `error LNK2019: 未解決の外部シンボル total が関数 add_count で参照されました`（環境によって `LNK2001: 未解決の外部シンボル total`）と `fatal error LNK1120: 1 件の未解決の外部参照`
- GCC（実際の出力の抜粋）:
  ```text
  /usr/bin/ld: ... in function `add_count':
  counter.c:(.text+0xa): undefined reference to `total'
  /usr/bin/ld: ... in function `main':
  main.c:(.text+0x14): undefined reference to `total'
  collect2: error: ld returned 1 exit status
  ```

**変更 2: 定義を戻し，さらに `main` 側にも `int total = 0;` を書く**（[_SharedCountDupDef](_SharedCountDupDef/)）

外部リンケージを持つ `total` の定義が 2 つの翻訳単位にあるので，**リンクで多重定義**になります（コンパイルは各ファイルとも成功）。

- MSVC: `error LNK2005: total は既に counter.obj で定義されています`（どちらの `.obj` 名になるかはリンク順による） と `fatal error LNK1169: 1 つ以上の複数回定義されているシンボルが見つかりました`
- GCC（実際の出力の抜粋）:
  ```text
  /usr/bin/ld: ...:(.bss+0x0): multiple definition of `total'; ...:(.bss+0x0): first defined here
  collect2: error: ld returned 1 exit status
  ```

どちらも試した後は正常な状態（`SharedCount`）へ戻します。インクルードガードは同じ翻訳単位での重複取り込みを防ぐだけで，別々の `.c` の定義の重複は防げません。

### 採点のポイント・よくある誤り

- `static int count = 0;` を「呼ぶたびに 0 にする」と説明している（初期化と代入の混同）。3 行目の版を 1 2 3 と予測している。
- 関数の前の `static` を「関数の値が保持される」と説明している（リンケージの話）。
- `count` を `free` しようとしている，`malloc` との違いを「速い／遅い」だけで説明している。
- 変更 1 を「コンパイルエラー」と書いている（リンクエラー。`extern` 宣言があるのでコンパイルは通る）。変更 2 の対処として `main` 側を `extern` に戻すことを説明できているか。
- ヘッダに `int total = 0;`（定義）を書いている。

---

## 発展3　不透明な`Vector`の生成と解放（`DynamicVector`）

### 要点

構造体の中身を `vector.c` に隠し，生成（`vector_create`／`vector_axpy`）・取得（`vector_get`）・解放（`vector_destroy`）の関数で扱います。複数の所有ポインタを最初に `NULL` にし，どこで失敗しても `cleanup` の 1 か所で後始末します。

### 解答コード

[vector.h](DynamicVector/vector.h)，[vector.c](DynamicVector/vector.c) は講義の 3 ファイル（コメントを日本語にした）で，[vector_main.c](DynamicVector/vector_main.c) には「添字と保存先の検査」の断片を追加しました。
講義の例題と同じく，`goto` で飛び越える変数を作らないように `out` と `ok` も先頭で宣言しています。

```c
    double first, second;
    double out = 99.0;
    int ok;
    ...
    printf("result=%.1f %.1f\n", first, second);

    // 添字と保存先の検査：有効な添字は 0 と 1。2 は範囲外なので 0 が返り，out は初期値のまま
    ok = vector_get(result, 2, &out);
    printf("ok=%d out=%.1f\n", ok, out);
    status = 0;
```

### 実行結果

```text
> DynamicVector
result=5.0 8.0
ok=0 out=99.0
（終了コード 0）
```

### 正常時の流れ

1. **`header` にメンバがないこと**: `vector.h` には `typedef struct vector Vector;`（不完全型の宣言）と関数の宣言しかありません。`struct vector { double v[2]; };` は `vector.c` にだけあります。そのため `vector_main.c` では `Vector *` は宣言できても，`Vector v;` や `sizeof(Vector)`，`x->v[0]` は書けません（コンパイルエラー）。
2. **`2x+y` の手計算**: `x = (1, 2)`，`y = (3, 4)` なので `2x + y = (2×1+3, 2×2+4) = (5, 8)`。予測どおり `result=5.0 8.0` と表示されました。
3. **生成した関数と解放した場所の対応**

   | 変数 | 生成した関数（実際に `malloc` する場所） | 解放した場所 |
   | --- | --- | --- |
   | `x` | `main` の `vector_create(1.0, 2.0)`（1 回目の確保） | `cleanup` の `vector_destroy(&x)`（3 番目） |
   | `y` | `main` の `vector_create(3.0, 4.0)`（2 回目の確保） | `cleanup` の `vector_destroy(&y)`（2 番目） |
   | `result` | `main` の `vector_axpy(2.0, x, y)`。その中の `vector_create` が 3 回目の確保をする | `cleanup` の `vector_destroy(&result)`（1 番目） |

   3 つとも成功時に所有権が `main` へ移り，`main` が `vector_destroy` で解放します。`vector_axpy` の引数 `x`，`y` は**借りるだけ**で，`vector_axpy` は解放しません。
4. **`&x` を渡す理由**: `vector_destroy(Vector **p)` は呼び出し元の**ポインタ変数 `x` 自身のアドレス**を受け取り，`free(*p)` の後 `*p = NULL;` で `x` を `NULL` に書き換えます。
   `void vector_destroy(Vector *p)` のように `x` の値を渡すと，関数の中の `p` は `x` のコピーなので，`p = NULL;` としても呼び出し元の `x` は古いアドレスのまま残ります。
5. **解放後に `NULL` になること**: Visual Studio では `return status;` にブレークポイントを置き，ウォッチで `x`，`y`，`result` がすべて `0x0000000000000000` になっていることを確認します（`x->v` などメンバの参照はしない）。
   リポジトリでは，`return status;` の前に `vector_destroy(&x);` をもう一度呼ぶ文と，3 つのポインタが `NULL` かを表示する `printf` を差し込んだ版（variants の `destroy_again`）でテストしています。
   ```text
   > DynamicVector_destroy_again
   result=5.0 8.0
   ok=0 out=99.0
   x=NULL y=NULL result=NULL
   ```

### 途中で失敗した場合（`DynamicVectorFail`）

[DynamicVectorFail/vector.c](DynamicVectorFail/vector.c) は `vector.c` のコピーで，`vector_create` より前に演習ページの `vector_allocate` を追加し，`vector_create` の `malloc` だけを置き換えました。
`fail_on_call = 2`（演習ページの値）の版が `DynamicVectorFail` で，0，1，3 は `softprac_add_variant` で値を書き換えた版です。どれも新しく起動するので，`static int calls` は 0 から数え直します。

```text
> DynamicVectorFail_fail_on_call_0   （fail_on_call = 0）
result=5.0 8.0
ok=0 out=99.0
（終了コード 0）
> DynamicVectorFail_fail_on_call_1   （fail_on_call = 1）
allocation failed
（終了コード 1）
> DynamicVectorFail   （fail_on_call = 2）
allocation failed
（終了コード 1）
> DynamicVectorFail_fail_on_call_3   （fail_on_call = 3）
allocation failed
（終了コード 1）
```

| `fail_on_call` | 確保できる領域 | 後始末の予測（＝確認結果） |
| --- | --- | --- |
| 0 | `x`，`y`，`result` の 3 つ（3 回の呼び出しで失敗しない） | 正常に表示し `status = 0`。`cleanup` で `result`，`y`，`x` の 3 つを解放 |
| 1 | なし（1 回目の `x` の確保で失敗） | `allocation failed` を出して `cleanup` へ。3 つとも `NULL` なので `vector_destroy` は `free(NULL)` で何もしない。終了コード 1 |
| 2 | `x` だけ（2 回目の `y` の確保で失敗） | `cleanup` で `result`，`y` は `NULL` なので何もせず，`x` を解放。終了コード 1 |
| 3 | `x` と `y`（3 回目，`vector_axpy` 内の `vector_create` で失敗） | `vector_axpy` が `NULL` を返し `cleanup` へ。`result` は `NULL`，`y` と `x` を解放。終了コード 1 |

確認方法: どの版も AddressSanitizer／LeakSanitizer 付きのテストでリーク・二重解放の報告がないことを確かめました。さらに valgrind で確保と解放の回数を数えると予測どおりでした。

| `fail_on_call` | valgrind の `total heap usage` | 内訳 |
| --- | --- | --- |
| 0 | 4 allocs, 4 frees | `Vector` 3 つ（16 バイト × 3）と標準出力のバッファ |
| 1 | 0 allocs, 0 frees | 何も確保していない（エラーは stderr なのでバッファも作られない） |
| 2 | 1 allocs, 1 frees | `x` だけ |
| 3 | 2 allocs, 2 frees | `x` と `y` |

すべて `All heap blocks were freed -- no leaks are possible` でした（Linux x64，Clang でビルドした版を valgrind で実行）。

`goto cleanup;` は複数の失敗箇所から後始末へ進む用途に限っています。所有ポインタを最初に `NULL` にしてあり，`free(NULL)` は安全なので，「どこまで作れたか」で分岐しなくても同じ後始末で済みます。

### 添字と保存先の検査

- 予測: 添字 2 は範囲外（有効なのは 0 と 1）なので `vector_get` は 0 を返し，`*out` を書き換えない。表示は `ok=0 out=99.0`。
- 結果: `ok=0 out=99.0`（上の実行結果の 2 行目）。
- 理由: `vector_get` は `index >= 2` を最初に検査して `return 0;` し，`*out = p->v[index];` に到達しません（契約「失敗時は保存先を変更しない」）。だから `out` の初期値 99.0 が保たれます。添字 0，1 なら 1 を返して 5.0，8.0 を保存します（`first`，`second` の取得で確認済み）。
  保存先を初期化しておかないと，失敗時に不定値を表示してしまうので，呼び出し側は戻り値を確認してから `out` を使います。

### 二重ポインタの意味

すべての後始末の後に `vector_destroy(&x);` をもう一度呼んでも，`x` はすでに `NULL` なので `free(NULL)` となり何も起きません（上の `destroy_again` の版で実際に 2 回目を呼んでおり，AddressSanitizer 付きのテストで二重解放の報告がないことを確認しています）。
しかし，このAPIは**すべての二重解放を防ぐ魔法ではありません**。

```c
Vector *x = vector_create(1.0, 2.0);
Vector *alias = x;          /* 解放前にコピーした別名 */
vector_destroy(&x);         /* x は NULL になる */
vector_destroy(&alias);     /* alias は古いアドレスのまま → 二重解放（未定義動作） */
```

`vector_destroy` が `NULL` にできるのは，渡された 1 つのポインタ変数だけです。別名 `alias` は自動では `NULL` にならないので，`alias` で参照すれば解放後の使用，`vector_destroy(&alias)` は二重解放です。
また，`NULL` の検査では「解放済みのアドレス」や「無関係なアドレス」を見分けられません。所有者を 1 つに決め，別名は借用として扱い，解放後はどの別名からも使わない，という規則を呼び出し側が守る必要があります（講義 8.1）。

### さらに考える：動的なメンバ

`struct vector { size_t n; double *v; };` のように配列を別に確保する場合，次を追加する必要があります。

```c
Vector *vector_create_n(size_t n)
{
    if (n == 0 || n > SIZE_MAX / sizeof(double)) {
        return NULL;
    }
    Vector *p = malloc(sizeof *p);          /* 1. 本体 */
    if (p == NULL) {
        return NULL;
    }
    p->n = n;
    p->v = malloc(n * sizeof *p->v);        /* 2. 配列 */
    if (p->v == NULL) {
        free(p);                            /* 配列の確保に失敗したら，先に成功した本体を解放する */
        return NULL;
    }
    for (size_t i = 0; i < n; ++i) {
        p->v[i] = 0.0;                      /* 読む前に double として初期化する */
    }
    return p;
}

void vector_destroy(Vector **p)
{
    if (p != NULL && *p != NULL) {
        free((*p)->v);                      /* 内側（配列）から */
        free(*p);                           /* 外側（本体）へ */
        *p = NULL;
    }
}
```

- **生成の途中失敗**: 本体の確保に成功した後で配列の確保に失敗したら，本体を解放してから `NULL` を返す（関数の中で後始末を完結させ，呼び出し元に半端なオブジェクトを渡さない）。
- **解放順**: 配列 → 本体。本体を先に `free` すると `(*p)->v` を読むことが解放後の使用になり，配列もリークします。`vector_destroy` で `*p` が `NULL` のときに `(*p)->v` を読まないよう検査も必要です。
- 構造体を代入でコピーすると `v` のアドレスだけがコピーされ，2 つの `Vector` が同じ配列を指すので，両方を `vector_destroy` すると二重解放になります。不透明型にして，コピーが必要なら配列も複製する関数を用意します。

### 採点のポイント・よくある誤り

- `vector_destroy(x)` と書いている（`Vector *` を `Vector **` に渡す型の誤り。MSVC は C4047，GCC・Clang は incompatible pointer types の警告を出す。警告を無視しない。`&x` の意味を説明できているか）。
- 失敗時に `return 1;` で直接抜けて，先に作った `x` などを解放していない（`fail_on_call=2,3` でリーク）。
- 所有ポインタを `NULL` で初期化せずに `cleanup` で `vector_destroy` している（未初期化ポインタの `free`）。
- `vector_axpy` の中で `a` や `b` を解放している（借用の誤解）。
- `fail_on_call=1` の後始末を「何も解放しないので `cleanup` は不要」としている（3 つとも `NULL` を渡すだけで安全，と説明できればよい）。
- 「`vector_destroy` があれば二重解放は起きない」と書いている。
- 試験用の `vector_allocate` を残したまま正常版として提出している。

---

## 確認問題

1. **ポインタ変数が局所変数なら，指す領域も必ずスタックにあるか。**
   → **いいえ。** ポインタ変数 `p` 自身の寿命（自動記憶域）と，`p` が指す領域の寿命は別です。`int *p = malloc(...);` なら `p` は局所変数でも指す先は動的に確保した領域（通常はヒープ）で，関数から戻っても `free` まで生きています（課題3の `new_point`）。静的記憶域の変数を指すこともあります。

2. **`calloc`した整数配列と`malloc`した整数配列を，代入前に同じように表示してよいか。**
   → **いいえ。** `calloc` は全ビットを 0 にし，整数型では全ビット 0 が値 0 なので，代入前に読んでも 0 が表示されます（発展1の `calloc: 0 0 0`）。`malloc` の領域は初期化されておらず値が不定なので，代入前に読んではいけません。なお `calloc` の全ビット 0 が `double` の 0.0 やポインタの `NULL` を表すとは限らない点も区別します。

3. **`free`の後に`p=NULL`としたら，`q=p`で以前に作った別名も`NULL`になるか。**
   → **いいえ。** `p = NULL;` は変数 `p` だけを書き換えます。`q` には解放前のアドレスが残り，`q` を参照すれば解放後の使用，`free(q)` は二重解放です（課題4，発展3の `alias`）。別名も含めて使わないようにします。

4. **`realloc`失敗後の元の配列と，成功後の古い要素ポインタは同じ扱いか。**
   → **いいえ。** 正のサイズへの `realloc` が失敗したとき，元の配列は**有効なまま**で，引き続き使ったり `free` したりできます（`GrowArrayFail` で `p[0]=1`）。成功したときは，古いポインタや古い要素を指すポインタは**無効**で，返されたポインタから参照を作り直す必要があります（`next == p` で同じアドレスに見えても，古いポインタは無効として扱い，`p = next;` の後の `p` から参照を作り直す）。

5. **動的な配列を含む構造体の本体だけを`free`すれば，配列も自動で解放されるか。**
   → **いいえ。** `free` は渡された 1 つの領域だけを解放し，中のポインタメンバの指す先までは解放しません。配列を先に `free` してから本体を `free` します（課題4の `buffer`，発展3「動的なメンバ」）。本体を先に解放するとメンバを読めなくなり，配列がリークします。

6. **エラー処理があることを確認するのに，実際にメモリを使い切る必要があるか。**
   → **いいえ。** 確保を担当する関数を試験用に差し替え，`NULL` を返させれば失敗経路を確実に再現できます（`point_allocate`，`try_resize`，`vector_allocate`）。確かめたいのは OS のメモリ不足の様子ではなく，「`NULL` を見て安全に終了し，確保済みの領域を残さないこと」です。実際に使い切る実験は他の作業に影響し，再現性もありません。

## チェックリスト

| 項目 | どこで確認できるか |
| --- | --- |
| 正常な値だけでなく，課題に示された境界の値でも確認した | 課題1の検証表（1，1000，0，-1，1001，`abc`，`3x`，`""`，`ERANGE`，引数の不足・過剰）と `Dynamic/tests/`，課題2の 1・2・5，発展1の境界の表と `GrowArray/tests/`（`old_n`・`new_n` の 7 組と上限の組） |
| 警告を確認し，原因を説明・修正した | 全プロジェクトを GCC・Clang の `-Wall -Wextra -Wpedantic -Werror` と MSVC `/W4 /WX`（CI）でビルド。`(double)sum / (double)n` の明示的な変換，`(size_t)count` の範囲確認後の変換，`%zu`。複合リテラルの左辺の誤り（C2440）は課題3 |
| 自分の言葉で，処理の流れと使った型を説明できる | 課題1の 6 つの役割のコメントと追跡表（`size_t`，`long`，`long long`，`int *`），課題3の寿命の表，発展3の生成・解放の対応表 |
| 確保した各領域の所有者を1つに決め，途中失敗の経路でも解放した | 課題4の所有者の図，`DynamicCopy` の `copy` 確保失敗時の `free(values)`（variants の `copy_alloc_fail`），`GrowArray` の `new_n = 0`／`1001`，`GrowArrayFail` の再確保失敗，`DynamicVectorFail` の `fail_on_call` 表。いずれもテストで LeakSanitizer がリークを報告しないことを確認し，`fail_on_call` と `GrowArrayFail` は valgrind でも確保・解放の回数が一致した |
| ポインタの`sizeof`と要素の`sizeof`を区別し，積を計算する前に検査した | 課題1「確保量を説明する」（`sizeof *values=4`，`sizeof values=8`），`n > SIZE_MAX / sizeof *values`，発展1の `new_n > SIZE_MAX / sizeof *p`，課題4の `malloc(n * sizeof p)` |
| `realloc`成功後には古い参照を使わず，追加部分を初期化した | 発展1の `p = next;` と `for (i = old_n; i < new_n; ++i)`，`p[3]` の説明，確認問題4 |
| 未初期化領域の読み取り，解放後の使用，巨大な確保実験を行っていない | `malloc` の領域は代入してから読む（課題1の (5)），`calloc` の 0 だけを表示，`free` 後は `NULL` を代入。失敗は試験用関数で模擬し，巨大な確保はしていない。ASan のテストで解放後の使用・範囲外アクセスがないことを確認 |
| 試験用の失敗設定を戻し，最後に正常版のビルド・実行を確認した | 正常版 `NewPoint`・`GrowArray`・`DynamicVector` は試験用関数を含まない。模擬する版は `NewPointFail`・`GrowArrayFail`・`DynamicVectorFail` として分け，正常版のテストもすべて成功 |

## 検証の方法（TA 向け）

```sh
B=/tmp/build-week13
cmake -S . -B $B -G Ninja -DSOFTPRAC_WEEKS=week13 -DSOFTPRAC_WERROR=ON -DSOFTPRAC_SANITIZE=ON
cmake --build $B && ctest --test-dir $B --output-on-failure
```

- `-DSOFTPRAC_SANITIZE=ON` で AddressSanitizer・UBSan が有効になり，Linux では LeakSanitizer も終了時にリークを検査します。`free` を 1 か所消すと `ERROR: LeakSanitizer: detected memory leaks` で該当テストが失敗します（`NewPoint` の `free(p)` を消して確認済み）。
- 書き換えた版の実行ファイルは `$B/variants/week13/`（例: `DynamicVectorFail_fail_on_call_3`，`StorageCount_auto_count`）にできます。
- 空文字列の引数 `""` はテスト `empty_arg`（`.args` が空行 1 行）で確かめています。空白 1 文字の引数（`blank_space`）も数字がないので同じく拒否されます。
