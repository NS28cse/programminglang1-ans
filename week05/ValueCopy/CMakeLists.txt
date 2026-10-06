# 第5回 課題3 ValueCopy
# フォルダのソースは z を追加した最終版。演習ページの各実験は main の一部を書き換えた版としてビルドしてテストする
#   original      … 演習ページのプログラムそのもの（z の行を除き，x と y を表示）
#   original_x_0 / original_x_m1 … 元のプログラムの初期値を 0，-1 に変えた版
#   call_discard / call_assign / assign_twice … 3 つの呼び出し方の表と，x = increment(x); を 2 回続ける実験
#   x_0 / x_m1    … 最終版（z あり）の初期値を変えた版
#   scope_blocks  … スコープの読解の 2 つのブロックを main 内に書いた版
softprac_add_program(ValueCopy valuecopy.c)

set(z_line [=[    int z = increment(x);  // x は 10 のままなので，z も 11
]=])
set(print_xyz [=[    printf("%d %d %d\n", x, y, z);]=])
set(print_xy [=[    printf("%d %d\n", x, y);]=])
set(body [=[    int y = increment(x);
    int z = increment(x);  // x は 10 のままなので，z も 11
    printf("%d %d %d\n", x, y, z);]=])

softprac_add_variant(ValueCopy valuecopy.c original      "${z_line}" "" "${print_xyz}" "${print_xy}")
softprac_add_variant(ValueCopy valuecopy.c original_x_0  "${z_line}" "" "${print_xyz}" "${print_xy}" "int x = 10;" "int x = 0;")
softprac_add_variant(ValueCopy valuecopy.c original_x_m1 "${z_line}" "" "${print_xyz}" "${print_xy}" "int x = 10;" "int x = -1;")
softprac_add_variant(ValueCopy valuecopy.c call_discard "${body}" [=[    increment(x);
    printf("%d\n", x);]=])
softprac_add_variant(ValueCopy valuecopy.c call_assign "${body}" [=[    x = increment(x);
    printf("%d\n", x);]=])
softprac_add_variant(ValueCopy valuecopy.c assign_twice "${body}" [=[    x = increment(x);
    x = increment(x);
    printf("%d\n", x);]=])
softprac_add_variant(ValueCopy valuecopy.c x_0  "int x = 10;" "int x = 0;")
softprac_add_variant(ValueCopy valuecopy.c x_m1 "int x = 10;" "int x = -1;")
softprac_add_variant(ValueCopy valuecopy.c scope_blocks "    int x = 10;
${body}" [=[    {
        int a = 123;
        printf("%d\n", a);
    }
    {
        int a = 345;
        printf("%d\n", a);
    }]=])
