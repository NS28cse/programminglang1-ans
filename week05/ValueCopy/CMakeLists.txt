# 第5回 課題3 ValueCopy
# 本体は演習ページのプログラム（10 11 を表示）。演習ページの各実験は main の一部を書き換えた版としてビルドしてテストする
#   x_0 / x_m1    … 初期値を 0，-1 に変えた版
#   call_discard / call_assign / assign_twice … 3 つの呼び出し方の表と，x = increment(x); を 2 回続ける実験
#   add_z         … 最初の呼び出しの後に int z = increment(x); を追加し，x y z を表示する版
#   scope_blocks  … スコープの読解の 2 つのブロックを main 内に書いた版
softprac_add_program(ValueCopy valuecopy.c)

set(body [=[    int y = increment(x);
    printf("%d %d\n", x, y);]=])

softprac_add_variant(ValueCopy valuecopy.c x_0  "int x = 10;" "int x = 0;")
softprac_add_variant(ValueCopy valuecopy.c x_m1 "int x = 10;" "int x = -1;")
softprac_add_variant(ValueCopy valuecopy.c call_discard "${body}" [=[    increment(x);
    printf("%d\n", x);]=])
softprac_add_variant(ValueCopy valuecopy.c call_assign "${body}" [=[    x = increment(x);
    printf("%d\n", x);]=])
softprac_add_variant(ValueCopy valuecopy.c assign_twice "${body}" [=[    x = increment(x);
    x = increment(x);
    printf("%d\n", x);]=])
softprac_add_variant(ValueCopy valuecopy.c add_z "${body}" [=[    int y = increment(x);
    int z = increment(x);  // x は 10 のままなので，z も 11
    printf("%d %d %d\n", x, y, z);]=])
softprac_add_variant(ValueCopy valuecopy.c scope_blocks "    int x = 10;
${body}" [=[    {
        int a = 123;
        printf("%d\n", a);
    }
    {
        int a = 345;
        printf("%d\n", a);
    }]=])
