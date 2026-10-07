# 第9回 課題1 FindMax
# フォルダのソースは講義の例題 double_pointer.c（期待する表示は max=12, a[1]=99, blue, green, red）。
# 演習ページの書き換えは，例題の一部を置き換えた版としてビルドしてテストする
#   n1 / n0 / n_m1   … find_max へ渡す n を 1，0，-1 にした版（検索範囲の表）
#   tie / tie_ge     … 配列を {12, 12, 4} にして first= を表示する版と，さらに比較を >= にした版
#   out_first        … *out = best; を *out = &a[0]; にした版（説明すること）
#   stale            … answer を &a[1] で初期化して n=0 で呼ぶ版（失敗時に古い結果を残さない）
#   trace            … 二重ポインタの断片を main 内に追加した版
softprac_add_program(FindMax double_pointer.c)

set(call "find_max(a, 3, &answer)")
set(print_max [=[        printf("max=%d\n", *answer);]=])

softprac_add_variant(FindMax double_pointer.c n1   "${call}" "find_max(a, 1, &answer)")
softprac_add_variant(FindMax double_pointer.c n0   "${call}" "find_max(a, 0, &answer)")
softprac_add_variant(FindMax double_pointer.c n_m1 "${call}" "find_max(a, -1, &answer)")
softprac_add_variant(FindMax double_pointer.c tie "{7, 12, 4}" "{12, 12, 4}" "${print_max}" [=[        printf("max=%d\n", *answer);
        printf("first=%d\n", answer == &a[0]);]=])
softprac_add_variant(FindMax double_pointer.c tie_ge "{7, 12, 4}" "{12, 12, 4}" "${print_max}" [=[        printf("max=%d\n", *answer);
        printf("first=%d\n", answer == &a[0]);]=] "a[i] > *best" "a[i] >= *best")
softprac_add_variant(FindMax double_pointer.c out_first "*out = best;" "*out = &a[0];")
softprac_add_variant(FindMax double_pointer.c stale "int *answer = NULL;" "int *answer = &a[1];" "${call}" "find_max(a, 0, &answer)"
  [=[    printf("a[1]=%d\n", a[1]);]=] [=[    printf("answer==NULL: %d\n", answer == NULL);
    printf("a[1]=%d\n", a[1]);]=])
softprac_add_variant(FindMax double_pointer.c trace [=[    for (int i = 0; i < 3; ++i) { printf("%s\n", names[i]); }
]=] [=[    for (int i = 0; i < 3; ++i) { printf("%s\n", names[i]); }
    int x = 10, y = 30;
    int *p = &x;
    int **pp = &p;
    **pp = 20;
    printf("%d %d %d\n", x, y, p == &x);
    *pp = &y;
    **pp = 40;
    printf("%d %d %d\n", x, y, p == &y);
]=])
