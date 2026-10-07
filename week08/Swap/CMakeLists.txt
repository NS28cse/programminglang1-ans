# 第8回 課題1 Swap
# フォルダのソースは演習の指示をすべて加えた最終版。演習ページの各確認は一部を書き換えた版としてテストする
#   y_5               … 例題の y の初期値を 5 にする（swap 直前に x と y が両方 5）
#   both_8            … x と y の初期値だけを同じ 8 にする（*p = 5 が片方を変える）
#   wrong_swap        … swap 内の *a = *b を a = b に変える（交換にならない）
#   swap_double_value … swap_double を値引数にし，swap_double(a[1], a[4]) と呼ぶ（コピーだけが交換される）
softprac_add_program(Swap pointers.c)

softprac_add_variant(Swap pointers.c y_5 "int x = 3, y = 8" "int x = 3, y = 5")
softprac_add_variant(Swap pointers.c both_8 "int x = 3, y = 8" "int x = 8, y = 8")
softprac_add_variant(Swap pointers.c wrong_swap
  [=[    int temp = *a;
    *a = *b;]=]
  [=[    int temp = *a;
    a = b;]=])
softprac_add_variant(Swap pointers.c swap_double_value
  [=[void swap_double(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}]=]
  [=[void swap_double(double a, double b)
{
    double temp = a;
    a = b;
    b = temp;
    printf("in function: a=%.1f b=%.1f\n", a, b);
}]=]
  "swap_double(&a[1], &a[4]);" "swap_double(a[1], a[4]);"
  "swap_double(a + 1, a + 4);" "swap_double(a[1], a[4]);"
  [=["&a[1], &a[4]"]=] [=["a[1], a[4] (1st)"]=]
  [=["a + 1, a + 4"]=] [=["a[1], a[4] (2nd)"]=])
