# 第2回 演習 解答・解説（変数）

演習ページ: <https://t-yokoga.github.io/softprac1/ex02.html>（講義: <https://t-yokoga.github.io/softprac1/lec02.html>）

この回は**キーボード入力・条件分岐・繰り返しを使わない**回です。解答も `printf` と変数の宣言・初期化・代入・`sizeof`・`&` だけで書いています。
値を変えて試す小問は，演習ページの指示どおり「ソースの 1 か所を書き換えた版」をテストにしています（後述の「テストの構成」）。

## プロジェクト一覧

| 課題 | 内容 | プロジェクト | ソース | テスト数 |
| --- | --- | --- | --- | ---: |
| 1 | 長方形の面積と再計算 | `Rectangle` | [rectangle.c](Rectangle/rectangle.c) | 3（本体 1 + 書き換え版 2） |
| 2 | 型と表示の対応 | `Profile` | [profile.c](Profile/profile.c) | 4（本体 1 + 書き換え版 3） |
| 3 | 値のコピーと交換 | `Exchange` | [exchange.c](Exchange/exchange.c) | 3（本体 1 + 書き換え版 2） |
| 4 | 値・サイズ・場所の観察 | `Observe` | [observe.c](Observe/observe.c) | 0（型のサイズは環境ごと（`sizeof(long)` が Windows で 4，Linux で 8），アドレスは実行ごとに変わるため。実行例を下に掲載） |
| 5 | 発展：小数を使った計算 | `Temperature` | [temperature.c](Temperature/temperature.c) | 4（本体 1 + 書き換え版 3） |

合計 14 テスト。GCC 13（`-Wall -Wextra -Wpedantic -Werror`，AddressSanitizer/UBSan）と Clang 18 で警告 0・全テスト成功を確認済み。

### テストの構成（書き換え版）

- `<プロジェクト>/tests/basic.out` … フォルダのソース（最終版）の期待する出力。
- `<プロジェクト>/variants/tests/<ケース>.out` … 「値を変えて確かめる」の書き換え版の期待する出力。
  各プロジェクトの `CMakeLists.txt` で `softprac_add_variant(...)`（[cmake/SoftpracVariant.cmake](../cmake/SoftpracVariant.cmake)）を呼び，
  ソースの文字列（例: `width = 6`）を 1 か所だけ置き換えた版をビルドしてテストします。置き換え前の文字列がソースにちょうど 1 回現れないと構成の段階でエラーになるので，ソースを直したときに気付けます。
  書き換え版の実行ファイルは `bin/` ではなくビルドフォルダの `variants/week02/` にでき，Visual Studio の起動構成（`.vs/launch.vs.json`）には現れません。

### 準備：講義の `variables.c`

演習の前に講義の `Variables` プロジェクト（`docs/sample/02/variables.c`）をビルド・実行できることを確認します（解答リポジトリには含めていません）。Linux x64（GCC 13）での実行結果:

```text
height=10 width=5 area=50
height=12 area=50
price=120.50 grade=A
sizeof(int)=4 sizeof(double)=8
CHAR_BIT=8 INT_MIN=-2147483648 INT_MAX=2147483647
height address=0x7ffcdab1e5e4
```

最後の行のアドレスは環境・実行ごとに異なります（Windows の MSVC では `000000xxxxxxxxxx` のような 16 桁の 16 進数で，`0x` は付きません）。

### 全課題に共通の採点ポイント

- **予測と結果を記録しているか**: 演習ページは実行前の予測と，結果・理由を `memo.txt` などに記録するよう求めている。課題ごとに「予測 → 実行結果 → 違った場合の理由」が書かれているか（特に課題1の 3 行，課題3の 2 文だけの版，課題4のどの項目が変わるか）を確認する。結果だけを書き写して予測がない提出は指導対象。
- **1 課題 1 プロジェクト**: `Variables` の `variables.c` を入れたまま別の `.c` を追加すると `main` が重複してリンクエラー（MSVC `LNK2005`，GCC `multiple definition of 'main'`）になる。
- 警告が出たまま提出していないか（書式と型の不一致は実行結果が正しく見えても誤り）。

---

## 課題1　長方形の面積と再計算（`Rectangle`）

**要点**: 変数に保存されるのは「式」ではなく「その時点で計算した値」。元の変数（`width`）を変えても `area` は自動で更新されないので，必要なら計算し直す。宣言（`int area = ...;`）と代入（`area = ...;`）の区別も確認する。

解答: [Rectangle/rectangle.c](Rectangle/rectangle.c)

```c
    int height = 7;
    int width = 4;
    int area = height * width;      // この時点の積 28 を保存する

    printf("first=%d\n", area);

    width = 6;                      // width だけが変わり，area は 28 のまま
    printf("before recalculation=%d\n", area);

    area = height * width;          // 既にある area へ代入し直す（int は付けない）
    printf("after recalculation=%d\n", area);
```

### 実行結果

```text
first=28
before recalculation=28
after recalculation=42
```

各段階の値（講義の表と同じ形式）:

| 実行した処理 | `height` | `width` | `area` | 表示 |
| --- | ---: | ---: | ---: | --- |
| 3 つの変数を初期化 | 7 | 4 | 28 | `first=28` |
| `width = 6;` | 7 | 6 | 28 | `before recalculation=28` |
| `area = height * width;` | 7 | 6 | 42 | `after recalculation=42` |

### 値を変えて確かめる（`width = 6;` の 6 を 0，1 に変える）

最初の `int width = 4;` は変えないので，1・2 行目は常に 28 です。変わるのは 3 行目だけです（テスト `variant_width_0`・`variant_width_1` で確認）。

| 途中の代入 | 1 行目 | 2 行目 | 3 行目 |
| --- | --- | --- | --- |
| `width = 6;`（本体） | `first=28` | `before recalculation=28` | `after recalculation=42` |
| `width = 0;` | `first=28` | `before recalculation=28` | `after recalculation=0` |
| `width = 1;` | `first=28` | `before recalculation=28` | `after recalculation=7` |

`width = 0;` の実行結果:

```text
first=28
before recalculation=28
after recalculation=0
```

`width = 1;` の実行結果:

```text
first=28
before recalculation=28
after recalculation=7
```

### 説明すること：`area` に保存しているのは計算式そのものか，その時点の計算結果か

**その時点の計算結果（値）です。** `int area = height * width;` は，右辺の `height * width` をその行を実行した時点の値（7 と 4）で計算し，結果の 28 を `area` の領域に保存します。
`area` と `height`・`width` の間に「連動する関係」は残らないので，後で `width` へ 6 や 0 を代入しても `area` は 28 のままです（2 行目）。
新しい面積が必要なら `area = height * width;` をもう一度実行して上書きします（3 行目）。表計算ソフトのセルの数式とは違います。

### 採点のポイント・よくある誤り

- **再計算で `int` を付ける**: `int area = height * width;` をもう一度書くと再定義でビルドエラー（MSVC: `error C2374: 'area': redefinition; multiple initialization`，GCC: `error: redefinition of 'area'`。MSVC の表示は英語版の例，日本語版では同じ番号で日本語の文）。2 回目は代入なので `int` を付けない。
- **表示を直接書く**: `printf("first=28\n");` のように計算済みの数を文字列に書いたものは不可。`%d` と `area` を渡しているか見る。
- **順序の誤り**: `width = 6;` の直後に再計算してしまい，2 行目が 42 になっている。2 行目は「再計算する前」の `area`。
- **小問で最初の `width = 4` を変えている**: 演習ページは途中の `width = 6;` だけを変える指示。最初を変えると 1・2 行目まで変わる。
- 表示の 1 文字違い（`before recalculation` の空白，`=` の前後に空白を入れる，最後の改行がない）も確認する。

---

## 課題2　型と表示の対応（`Profile`）

**要点**: 整数は `int` と `%d`，小数は `double` と `%f`，1 文字は `char`（`'B'`）と `%c` を対応させる。`%.2f` は**表示の桁数**の指定であって，変数の値は変えない。

解答: [Profile/profile.c](Profile/profile.c)

```c
    int count = 3;
    double price = 125.5;
    char grade = 'B';               // 1 文字はシングルクォートで囲む
    double total = count * price;   // int と double の積は double になる

    // %.2f は表示する桁数の指定であり，変数の値は変えない
    printf("count=%d price=%.2f grade=%c\n", count, price, grade);
    printf("total=%.2f\n", total);
```

### 実行結果

```text
count=3 price=125.50 grade=B
total=376.50
```

`count * price` は `int` と `double` の積なので `double` で計算され（3 × 125.5 = 376.5），`total` に保存されます。

### 表示方法を変えてみる

| 手順 | 書き換え | 実行結果 | テスト |
| --- | --- | --- | --- |
| 1・2 | `price` の `%.2f` だけを `%f` へ | `count=3 price=125.500000 grade=B`<br>`total=376.50` | `variant_price_f` |
| 3 | 続けて `count` を 0 へ（`%f` のまま） | `count=0 price=125.500000 grade=B`<br>`total=0.00` | `variant_price_f_count_0` |
| （参考） | 書式は元のまま `count` だけ 0 へ | `count=0 price=125.50 grade=B`<br>`total=0.00` | `variant_count_0` |
| 4 | 最初の設定へ戻す | `count=3 price=125.50 grade=B`<br>`total=376.50` | `basic` |

手順 1 の実行結果（`%f` は小数点以下 6 桁）:

```text
count=3 price=125.500000 grade=B
total=376.50
```

手順 3 の実行結果（`total` は 0 × 125.5 = 0 を `%.2f` で表示）:

```text
count=0 price=125.500000 grade=B
total=0.00
```

### 説明すること：`%.2f` を `%f` へ変えると，`price` に保存された値も変わるか

**変わりません。** `%.2f`・`%f` は `printf` が「どう表示するか（小数点以下何桁まで文字にするか）」の指定で，`price` に保存されている値 125.5 には何もしません。
実際，`%f` に変えても 2 行目の `total` は同じ 376.50 です（`total` は `price` の値から計算しているので，`price` が変わっていればここも変わるはずです）。
逆に `%.1f` などで桁を減らしても，丸められるのは表示だけで，変数の値の精度は増えも減りもしません。

### 型と違う書式で試さない（演習ページの注意について）

`printf` は書式に合わせて値を変換してくれる関数ではありません。`price` を `%d`，`count` を `%f` に対応させると未定義動作になります（実行して結果を調べない）。ビルド時の診断の例:

- MSVC（`/W4`）: `warning C4477: 'printf' : format string '%d' requires an argument of type 'int', but variadic argument 2 has type 'double'`（英語版の表示。日本語版も番号は同じ）
- GCC 13: `warning: format '%d' expects argument of type 'int', but argument 3 has type 'double' [-Wformat=]`

### 採点のポイント・よくある誤り

- **`grade` を `"B"` で初期化**: `"B"` は文字列（第6回）で `char` 1 文字ではない。MSVC は `warning C4047: 'initializing': 'char' differs in levels of indirection from 'char [2]'`，GCC 13 は `warning: initialization of 'char' from 'char *' makes integer from pointer without a cast [-Wint-conversion]`，Clang 18 はエラー。`'B'` が正しい。
- **`total` を `int` にする**: `int total = count * price;` は 376 に切り捨てられ（MSVC `/W4` では `warning C4244: 'initializing': conversion from 'double' to 'int', possible loss of data`），`%d` で `total=376` と表示される。GCC の `-Wall -Wextra` では警告が出ないので，GCC で確認した学生は気付きにくい。
- **計算済みの文字列を書く**: `printf("total=376.50\n");` は不可（課題文で禁止）。
- `price` に `%f` のまま提出（`price=125.500000`），`%c` ではなく `%s` や `%d` で `grade` を表示，などの書式の誤り。
- 手順 4（元に戻す）を忘れて `%f` や `count = 0` のまま提出していないか。

---

## 課題3　値のコピーと交換（`Exchange`）

**要点**: 代入は左辺の古い値を上書きして失う。交換するときは，上書きされる前の値を一時変数 `temp` へ保存しておく。

解答: [Exchange/exchange.c](Exchange/exchange.c)

```c
    int a = 10;
    int b = 20;

    printf("before: a=%d b=%d\n", a, b);

    int temp = a;                   // 上書きされる前の a の値を保存する
    a = b;
    b = temp;

    printf("after: a=%d b=%d\n", a, b);
```

### 実行結果

```text
before: a=10 b=20
after: a=20 b=10
```

### 2 文だけの交換（紙に書く問い）

| 実行した文 | `a` | `b` |
| --- | ---: | ---: |
| 初期化 | 10 | 20 |
| `a = b;` | 20 | 20 |
| `b = a;` | 20 | 20 |

`a = b;` の時点で `a` の 10 は失われ，`b = a;` は 20 を 20 で上書きするだけです。`temp` を使った版の値の変化:

| 実行した文 | `a` | `b` | `temp` |
| --- | ---: | ---: | ---: |
| 初期化 | 10 | 20 | （未宣言） |
| `int temp = a;` | 10 | 20 | 10 |
| `a = b;` | 20 | 20 | 10 |
| `b = temp;` | 20 | 10 | 10 |

2 文だけの版（比較用。フォルダには入れていない）:

```c
    int a = 10;
    int b = 20;

    printf("before: a=%d b=%d\n", a, b);
    a = b;
    printf("after a = b;  a=%d b=%d\n", a, b);
    b = a;
    printf("after b = a;  a=%d b=%d\n", a, b);
```

実行結果:

```text
before: a=10 b=20
after a = b;  a=20 b=20
after b = a;  a=20 b=20
```

### 別の値でも確認する

| 初期値 | `temp` を使った版（解答） | 2 文だけの版 | テスト |
| --- | --- | --- | --- |
| `a = 10`, `b = 20` | `after: a=20 b=10` | `a=20 b=20` | `basic` |
| `a = -3`, `b = 8` | `after: a=8 b=-3` | `a=8 b=8` | `variant_a_m3_b_8` |
| `a = 5`, `b = 5` | `after: a=5 b=5` | `a=5 b=5` | `variant_a_5_b_5` |

`temp` を使った版の実行結果（`a = -3`, `b = 8`）:

```text
before: a=-3 b=8
after: a=8 b=-3
```

（`a = 5`, `b = 5`）:

```text
before: a=5 b=5
after: a=5 b=5
```

2 文だけの版の実行結果（上の比較用コードの初期値を変えたもの）:

```text
before: a=-3 b=8
after a = b;  a=8 b=8
after b = a;  a=8 b=8
```

```text
before: a=5 b=5
after a = b;  a=5 b=5
after b = a;  a=5 b=5
```

### 記録すること：一時変数を使わない 2 文の結果と，`temp` を使った結果の違い

- 2 文だけ（`a = b; b = a;`）では，**`a` と `b` の両方が元の `b` の値**になる（10/20 → 20/20，−3/8 → 8/8）。`a = b;` で元の `a` の値が上書きされて失われ，2 文目でそれを取り戻せないため。
- `temp` を使うと，上書きする前に元の `a` を `temp` へコピーしてあるので，最後に `b = temp;` で元の `a` を `b` に入れられ，正しく入れ替わる（20/10，8/−3）。
- `a = 5`, `b = 5` のように**2 つの値が等しいと，どちらの方法でも同じ結果**になり，間違った 2 文の版でも正しく見える。テストに使う値は異なる値にする必要がある。

### 採点のポイント・よくある誤り

- **表示だけ入れ替える**: 交換せずに `printf("after: a=%d b=%d\n", b, a);` と引数を逆にした提出は，どの初期値でも表示が一致してしまう。出力ではなくコードで交換しているかを確認する。
- **`printf("after: a=20 b=10\n");` と直接書く**: 初期値を −3, 8 に変えると誤りが分かる。
- **代入の順序の誤り**: `temp = a; b = a; a = temp;` は交換にならない。2 文目の `b = a;` で `b` の元の値 20 を失い（`temp` に保存したのは `a` の 10），最後は a=10, b=10 になる。保存した値を戻す先（`b = temp;`）と，先に上書きする変数（`a = b;`）の順を確認する。
- **足し算・引き算による交換**（`a = a + b; b = a - b; a = a - b;`）は今回の意図（値の上書きと一時変数）から外れ，`int` の範囲を超えると未定義動作になり得るので勧めない。
- 「記録すること」で，2 文の版の結果（20/20）を実際に書けているか，等しい値（5, 5）では違いが分からないことに気付いているかを見る。

---

## 課題4　値・サイズ・場所の観察（`Observe`）

**要点**: 同じ変数について，**値**（`%d`），**サイズ**（`sizeof`，`%zu`），**アドレス**（`&value`，`(void *)` を付けて `%p`）は別の情報。代入で変わるのは値だけ。型のサイズは処理系で決まり，「64 ビットだから 8 バイト」ではない。

解答: [Observe/observe.c](Observe/observe.c)

```c
    int value = 10;

    printf("before: value=%d sizeof value=%zu &value=%p\n",
           value, sizeof value, (void *)&value);

    value = 99;                     // 同じ領域の中身を上書きする
    printf("after:  value=%d sizeof value=%zu &value=%p\n",
           value, sizeof value, (void *)&value);

    printf("sizeof(char)=%zu\n", sizeof(char));
    printf("sizeof(int)=%zu\n", sizeof(int));
    printf("sizeof(long)=%zu\n", sizeof(long));
    printf("sizeof(long long)=%zu\n", sizeof(long long));
    printf("sizeof(double)=%zu\n", sizeof(double));
```

表示の形式は演習ページで指定されていないので，変更前・変更後が 1 行ずつで比べやすい形にしています（学生の形式は自由。値・サイズ・アドレスと 5 つの型のサイズが表示されていればよい）。

### 実行結果

Linux x64（GCC 13）で実際に 2 回起動した結果:

```text
before: value=10 sizeof value=4 &value=0x7ffeab38c7d4
after:  value=99 sizeof value=4 &value=0x7ffeab38c7d4
sizeof(char)=1
sizeof(int)=4
sizeof(long)=8
sizeof(long long)=8
sizeof(double)=8
```

```text
before: value=10 sizeof value=4 &value=0x7ffc43e61244
after:  value=99 sizeof value=4 &value=0x7ffc43e61244
sizeof(char)=1
sizeof(int)=4
sizeof(long)=8
sizeof(long long)=8
sizeof(double)=8
```

同じ実行の中では `&value` は変わらず，起動し直すと別のアドレスになっています（アドレス空間配置のランダム化のため）。

Windows x64（Visual Studio，MSVC）では次の形になります（この環境では MSVC を実行していないため，**アドレスの数字は例**です。`%p` は `0x` なしの 16 桁の大文字 16 進数）。**`sizeof(long)` が 4** になる点が Linux と違います。

```text
before: value=10 sizeof value=4 &value=000000A3C14FF7F4
after:  value=99 sizeof value=4 &value=000000A3C14FF7F4
sizeof(char)=1
sizeof(int)=4
sizeof(long)=4
sizeof(long long)=8
sizeof(double)=8
```

### 観察表

| 項目 | 変更前 | 変更後 | 変化したか |
| --- | --- | --- | --- |
| `value`の値 | 10 | 99 | **変わった**（代入で中身を上書きした） |
| `sizeof value` | 4 | 4 | **変わらない**（`int` 型のサイズで決まる） |
| `&value`の表示 | `0x7ffeab38c7d4` | `0x7ffeab38c7d4` | **変わらない**（同じ領域を上書きしている） |

アドレスは上の Linux x64 の 1 回目の実行結果です。Windows（MSVC）では `000000A3C14FF7F4` のような `0x` なしの 16 桁の形で表示されます。
アドレスの具体的な値は学生ごと・起動ごとに異なるのが正しい。採点では「変更前と変更後が同じ」ことを見る。

### 型ごとのサイズ（バイト）

| 型 | Windows x64（MSVC） | Windows x86（MSVC，32 ビット） | Linux x64（GCC/Clang） | macOS（Apple Clang） |
| --- | ---: | ---: | ---: | ---: |
| `char` | 1 | 1 | 1 | 1 |
| `int` | 4 | 4 | 4 | 4 |
| `long` | **4** | 4 | **8** | **8** |
| `long long` | 8 | 8 | 8 | 8 |
| `double` | 8 | 8 | 8 | 8 |

Linux x64 の列はこの環境で実行した値。Windows の列は MSVC の仕様（講義の表と同じく `long` は 64 ビット用でも 4 バイト）。`sizeof(char)` は C の規格で常に 1。

### 説明すること

**1000 を保存すると `sizeof value` も変わるか** → **変わりません。** `sizeof value` は `value` の**型**（`int`）のサイズで，保存している値の大きさや十進の桁数とは無関係です。`int` の範囲（MSVC・GCC とも −2147483648〜2147483647）に入る値なら，10 でも 1000 でも同じ 4 バイトの領域に保存されます。`value = 99;` を `value = 1000;` に変えた実行結果（Linux x64）:

```text
before: value=10 sizeof value=4 &value=0x7ffeef0497c4
after:  value=1000 sizeof value=4 &value=0x7ffeef0497c4
```

**「64 ビット PC ならすべての変数が 8 バイト」は正しいか** → **正しくありません。** 変数のサイズは型と処理系（コンパイラ・OS の約束）で決まり，CPU のビット数で一律に決まるわけではありません。
同じ 64 ビット PC でも `char` は 1，`int` は 4，`double` は 8 バイトです。`long` は Windows（MSVC）では 4，Linux では 8 と処理系によって異なります。8 バイトになるのは `long long`・`double` や（第8回で学ぶ）アドレスを保存する変数などです。サイズは決めつけず `sizeof` で確かめます。

### 採点のポイント・よくある誤り

- **`sizeof` を `%d` で表示**: `sizeof` の結果は `size_t` なので `%zu`。MSVC は `C4477`，GCC は `warning: format '%d' expects argument of type 'int', but argument 3 has type 'long unsigned int' [-Wformat=]`。
- **`(void *)` を付けずに `%p` に `&value` を渡す**: GCC（`-Wpedantic`）は `format '%p' expects argument of type 'void *', but argument 2 has type 'int *'`，Clang は `-Wformat-pedantic` の警告。MSVC では警告が出ないことがあるので，コードを見て確認する。アドレスを `%d`・`%x` で表示するのも誤り。
- **表の「変化したか」の誤り**: アドレスやサイズが「変わった」としている，または起動し直した別の実行の値と比べて「アドレスが変わった」と書いている（比べるのは同じ実行の中の変更前・変更後）。
- **`sizeof(long)` を 8 と決めつける**: Windows（MSVC）で実行していれば 4 が正しい。他の学生（Mac・Linux）と数字が違っても誤りではない。
- アドレスの値そのものが学生間で違うのは正常。見本と同じ数値をソースや記録に書き写していないかを見る。

---

## 課題5　発展：小数を使った計算（`Temperature`）

**要点**: 小数の計算は `double` と小数のリテラル（`9.0`，`5.0`，`32.0`）で行い，`%.1f` で小数点以下 1 桁を表示する。計算結果は計算した時点の値なので，`celsius` を後で変えたら再計算が必要（課題1と同じ）。

解答: [Temperature/temperature.c](Temperature/temperature.c)

```c
    double celsius = 25.0;
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;    // 9.0 / 5.0 で小数の計算にする

    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
```

### 実行結果

```text
Celsius=25.0 Fahrenheit=77.0
```

25.0 × 9.0 = 225.0，225.0 ÷ 5.0 = 45.0，45.0 + 32.0 = 77.0（`*` と `/` は左から順に計算し，`+` はその後）。

### 値を変えて確かめる

| `celsius` の初期値 | 実行結果 | テスト |
| --- | --- | --- |
| 25.0（本体） | `Celsius=25.0 Fahrenheit=77.0` | `basic` |
| 0.0 | `Celsius=0.0 Fahrenheit=32.0` | `variant_celsius_0` |
| 100.0 | `Celsius=100.0 Fahrenheit=212.0` | `variant_celsius_100` |
| -40.0 | `Celsius=-40.0 Fahrenheit=-40.0` | `variant_celsius_m40` |

いずれも演習ページの 32.0，212.0，−40.0 と一致します（−40 度は摂氏と華氏が等しくなる温度）。

### 計算後に `celsius` を変更した場合

`fahrenheit` は計算した時点の値を保存しているだけなので，`celsius` を変えただけでは更新されません。確認用のコード（フォルダには入れていない）:

```c
    double celsius = 25.0;
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;

    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    celsius = 100.0;
    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
```

実行結果（2 行目は再計算前なので 77.0 のまま）:

```text
Celsius=25.0 Fahrenheit=77.0
Celsius=100.0 Fahrenheit=77.0
Celsius=100.0 Fahrenheit=212.0
```

### 採点のポイント・よくある誤り

- **`fahrenheit = 77.0;` と直接書く**: 初期値を 0.0 に変えても 77.0 のままになる。式で計算しているかを見る。
- **整数の割り算**: `9 / 5 * celsius + 32` と書くと，先に `9 / 5` が整数どうしの割り算で 1 になり，25.0 で `57.0` と表示される（実際に確認済み）。課題の式の順（`celsius * 9.0 / 5.0`）なら先に `double` の掛け算になる。整数の割り算の規則は第3回，型変換は第6回で扱う。
- **書式**: `%f` のままだと `Celsius=25.000000 Fahrenheit=77.000000` になる。`%.1f` を使う。`%d` で `double` を渡すのは未定義動作（MSVC `C4477`，GCC `-Wformat`）。
- **型**: `int celsius` にすると小数を扱えない。両方 `double` で保存するよう指定されている。
- 表示の大文字小文字（`Celsius`，`Fahrenheit`）と空白 1 つを確認する。

---

## 確認問題

1. **`int count = 3;` が宣言と初期化を行う。** 型 `int` を付けて新しい変数 `count` を作り（宣言），同時に最初の値 3 を与えている（初期化）。`count = 5;` は既にある `count` に 5 を保存する**代入**で，宣言はしていない（課題1の `area = height * width;` も代入）。
2. **`b` は 10 のまま。** `int b = a;` で `b` に保存されたのはその時点の `a` の値 10 のコピーで，`a` と `b` は別の領域の独立した変数。`a = 20;` は `a` の領域だけを書き換える（講義の例では `20 10` と表示される）。
3. **自動では更新されない。** `area` には計算した時点の積が保存されているだけで，式は覚えていない。`height` を変えたら `area = height * width;` を再び実行する必要がある（課題1の 2 行目 28 と 3 行目 42）。
4. **整数に変換して表示されることはない（誤り）。** `printf` の書式は型変換の指示ではなく，型と書式が合わないと未定義動作になり，でたらめな数が表示されることもある。MSVC は `C4477`，GCC は `-Wformat` の警告を出す。整数として表示したいなら値を `int` に変換してから渡す（型変換は第6回）。
5. **`'A'`。** シングルクォートの `'A'` は 1 文字（`char` に入る文字の値）。ダブルクォートの `"A"` は文字列で，`char` 1 個の初期値にはならない（MSVC `C4047`，GCC 13 `-Wint-conversion` の警告，Clang 18 ではエラー）。
6. **サイズ。** `sizeof` は型または変数が使う領域のバイト数（`size_t` 型，`%zu` で表示）を求める。値は変数名（`%d` など），アドレスは `&`（`%p`）で得る。
7. **考えてはいけない。** 初期化していない局所変数の値は定まっておらず，その値を使うのは誤り（未定義動作になり得る）。たまたま 0 に見えても，ビルド設定・コンパイラ・実行のたびに変わり得る（MSVC の Debug ビルドでは未初期化の領域が 0xCC で埋められ，`int` なら -858993460 と見えることが多い）。MSVC は `C4700: uninitialized local variable 'x' used`（SDL チェック `/sdl` が有効なプロジェクトではエラー），GCC は `warning: 'x' is used uninitialized [-Wuninitialized]` を出す。読む前に必ず初期化か代入をする。
8. **値だけが変わり，サイズとアドレスは変わらない。** サイズは型（`int`）で決まり，代入は同じ場所の中身を上書きするだけ（課題4の観察表で `sizeof value` は 4 のまま，`&value` も変更前と同じ）。ただし起動し直したときのアドレスは前回と同じとは限らない。

## チェックリスト

| 項目 | 確認できる課題・内容 |
| --- | --- |
| 課題1〜4のプロジェクトとソースを保存した | 表の 4 プロジェクト（`Rectangle/rectangle.c`，`Profile/profile.c`，`Exchange/exchange.c`，`Observe/observe.c`）が 1 課題 1 プロジェクトで，それぞれ `main` を 1 つ持つ。発展の `Temperature/temperature.c` も同様 |
| 警告・エラーを確認し，型と`printf`の書式を合わせた | 全プロジェクトが MSVC `/W4`・GCC/Clang `-Wall -Wextra -Wpedantic` で警告 0。`int`→`%d`，`double`→`%f`/`%.2f`/`%.1f`，`char`→`%c`，`sizeof`→`%zu`，アドレス→`(void *)` と `%p`（課題2・4・5） |
| 課題1の再計算前と再計算後の違いを説明できる | 課題1の値の表と「説明すること」（`area` は計算時点の値なので 28 → 再計算で 42） |
| 課題2の書式を変えた結果と，変数の値そのものを区別できる | 課題2の「表示方法を変えてみる」（`%f` で 125.500000 になっても `total` は 376.50 のまま）と「説明すること」 |
| 課題3で，なぜ元の値を一時変数へ保存するのか説明できる | 課題3の 2 つの値の表と「記録すること」（`a = b;` で元の `a` が失われる） |
| 課題4の観察表を埋め，値・サイズ・場所を区別できる | 課題4の観察表・型ごとのサイズの表・「説明すること」（値だけが変わる。`long` は処理系で 4 または 8） |
