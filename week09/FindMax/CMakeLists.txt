# 第9回 課題1 FindMax: 本体は講義の例題 double_pointer.c（max=12, a[1]=99, blue, green, red）。
# 演習ページの書き換えを，例題の一部を置き換えた版としてビルドしてテストする
#   n1 / n0 / n_m1   … find_max へ渡す n を 1，0，-1 にした版（検索範囲の表。n1 は a[0] も表示する）
#   tie / tie_ge     … 配列を {12, 12, 4} にして first= を表示する版と，さらに比較を >= にした版
#   out_first        … *out = best; を *out = &a[0]; にした版（説明すること）
#   stale            … answer を &a[1] で初期化して n=0 で呼ぶ版（失敗時に古い結果を残さない）
#   trace            … 二重ポインタの断片を main 内に追加した版
# 各版は先頭コメントの 2 行目を版の説明に置き換え，書き換えた行のコメントも合わせる（置換前の文字列は行全体）
softprac_add_program(FindMax double_pointer.c)

set(desc [=[// 講義の例題。find_max は最大要素の場所を二重ポインタ out で呼び出し元の answer へ書き，戻り値で成功・失敗を返す。]=])
set(call [=[    if (find_max(a, 3, &answer)) {  // *answer を使うのは成功したときだけ]=])
set(init "    int a[] = {7, 12, 4};")
set(init_tie "    int a[] = {12, 12, 4};  // 同点: a[0] と a[1] が最大")
set(print_max [=[        printf("max=%d\n", *answer);]=])
set(print_first [=[        printf("max=%d\n", *answer);
        printf("first=%d\n", answer == &a[0]);  // 1 なら最初の要素 a[0] を選んだ]=])
set(print_a1 [=[    printf("a[1]=%d\n", a[1]);]=])

# 検索範囲の表: n を 1，0，-1 にする
softprac_add_variant(FindMax double_pointer.c n1
  "${desc}"
  "// find_max へ渡す n を 1 にし，a[0] も表示する版。\n// 検索範囲は a[0] だけなので max=7 になり，99 は a[0] に書かれる（a[1] は 12 のまま）。"
  "${call}"
  [=[    if (find_max(a, 1, &answer)) {  // n=1: a[0] だけを調べて成功する]=]
  "${print_a1}"
  [=[    printf("a[0]=%d\n", a[0]);  // n=1 では最大要素は a[0] なので 99 になる
    printf("a[1]=%d\n", a[1]);]=])
softprac_add_variant(FindMax double_pointer.c n0
  "${desc}"
  "// find_max へ渡す n を 0 にした版。\n// 調べる要素がないので 0 が返り，max= は表示せず a[1] も 12 のまま。"
  "${call}"
  [=[    if (find_max(a, 0, &answer)) {  // n=0 なので失敗して 0 が返る（*answer は使わない）]=])
softprac_add_variant(FindMax double_pointer.c n_m1
  "${desc}"
  "// find_max へ渡す n を -1 にした版。\n// n<=0 は失敗として 0 が返り，max= は表示せず a[1] も 12 のまま。"
  "${call}"
  [=[    if (find_max(a, -1, &answer)) {  // n=-1 なので失敗して 0 が返る（*answer は使わない）]=])

# 同点: {12, 12, 4} で first=（a[0] を選んだか）を表示する。tie_ge はさらに比較を >= にする
softprac_add_variant(FindMax double_pointer.c tie
  "${desc}"
  "// 配列を同点の {12, 12, 4} にし，first= を表示する版。\n// 比較が > なので最初の要素 a[0] を選び first=1。99 は a[0] に書かれる（a[1] は 12 のまま）。"
  "${init}" "${init_tie}"
  "${print_max}" "${print_first}")
softprac_add_variant(FindMax double_pointer.c tie_ge
  "${desc}"
  "// 同点の {12, 12, 4} で，find_max の比較を > から >= にした版。\n// 同点なら後の要素に更新するので a[1] を選び first=0。99 は a[1] に書かれる。"
  "${init}" "${init_tie}"
  "${print_max}" "${print_first}"
  "        if (a[i] > *best) { best = &a[i]; }  // > なので，同点なら最初の要素のまま"
  "        if (a[i] >= *best) { best = &a[i]; }  // >= なので，同点なら後の要素に更新する（誤りではなく仕様の違い）")

# 説明すること: *out = best; を *out = &a[0]; にする（コンパイルは通るが常に a[0] になる）
softprac_add_variant(FindMax double_pointer.c out_first
  "${desc}"
  "// 誤りの例: find_max の *out = best; を *out = &a[0]; にした版。\n// 型は合うのでコンパイルは通るが，最大要素ではなく常に a[0] の場所を返すので max=7 になる。"
  "// 最大要素の場所を *out へ書き，成功なら1，n<=0 なら0を返す。"
  "// 誤りの例: best を使わず常に a[0] の場所を *out へ書く（成功なら1，n<=0 なら0を返すのは本体と同じ）。"
  "    *out = best;"
  "    *out = &a[0];  // 誤りの例: 探した best ではなく先頭要素の場所を書く")

# 失敗時に古い結果を残さない: answer を &a[1] で初期化して n=0 で呼ぶ
softprac_add_variant(FindMax double_pointer.c stale
  "${desc}"
  "// answer を &a[1] で初期化してから n=0 で呼ぶ版。\n// find_max は失敗時にも *out を NULL にするので，古い場所 &a[1] は残らない（answer==NULL: 1）。"
  "    int *answer = NULL;"
  "    int *answer = &a[1];  // 以前の結果が入っている状態を作る"
  "${call}"
  [=[    if (find_max(a, 0, &answer)) {  // n=0 なので失敗して 0 が返る]=]
  "${print_a1}"
  [=[    printf("answer==NULL: %d\n", answer == NULL);  // 失敗時に NULL へ戻されたか
    printf("a[1]=%d\n", a[1]);]=])

# 二重ポインタの断片（**pp と *pp への代入）を main の最後に追加する
softprac_add_variant(FindMax double_pointer.c trace
  "${desc}"
  "// 講義の例題の main の最後に，二重ポインタの断片（**pp と *pp への代入）を追加した版。"
  [=[    for (int i = 0; i < 3; ++i) { printf("%s\n", names[i]); }]=]
  [=[    for (int i = 0; i < 3; ++i) { printf("%s\n", names[i]); }
    int x = 10, y = 30;
    int *p = &x;
    int **pp = &p;
    **pp = 20;  // p が指す x を変える
    printf("%d %d %d\n", x, y, p == &x);
    *pp = &y;   // p 自身を変え，y を指すようにする
    **pp = 40;  // 今度は y が変わる（x は 20 のまま）
    printf("%d %d %d\n", x, y, p == &y);]=])
