# 第8回 課題1 Swap
# フォルダのソースは講義の配布コード pointers.c のまま（期待する表示 x=8 y=5 / sum=60 / c at）。
# 演習の実験は書き換えた版・versions/ の版としてビルドしてテストする
#   trace          … 宣言・*p = 5・swap の後の状態を表示する（「代入ごとの状態を記録する」の表）
#   y_5 / both_8   … trace に加えて，y の初期値を 5 にする／x と y の初期値だけを同じ 8 にする
#   wrong_swap     … swap 内の *a = *b を a = b に変える（交換にならない）
#   copy_pointer   … versions/copy_pointer.c（ポインタのコピーを比較する。置換なし）
#   swap_double_address / swap_double_pointer / swap_double_value
#                  … versions/swap_double.c（&a[1], &a[4]）と，a + 1, a + 4 の呼び出し，値引数にした版
softprac_add_program(Swap pointers.c)

set(steps [=[    int *p = &x;
    *p = 5;
    swap(&x, &y);
]=])
set(steps_traced [=[    int *p = &x;
    printf("init:   x=%d y=%d p_is_x=%d *p=%d\n", x, y, p == &x, *p);
    *p = 5;
    printf("*p = 5: x=%d y=%d p_is_x=%d *p=%d\n", x, y, p == &x, *p);
    swap(&x, &y);
    printf("swap:   x=%d y=%d p_is_x=%d *p=%d\n", x, y, p == &x, *p);
]=])
softprac_add_variant(Swap pointers.c trace "${steps}" "${steps_traced}")
softprac_add_variant(Swap pointers.c y_5 "${steps}" "${steps_traced}" "int x = 3, y = 8" "int x = 3, y = 5")
softprac_add_variant(Swap pointers.c both_8 "${steps}" "${steps_traced}" "int x = 3, y = 8" "int x = 8, y = 8")
softprac_add_variant(Swap pointers.c wrong_swap
  [=[    int temp = *a;
    *a = *b;]=]
  [=[    int temp = *a;
    a = b;]=])

softprac_add_variant(Swap versions/copy_pointer.c copy_pointer)

softprac_add_variant(Swap versions/swap_double.c swap_double_address)
softprac_add_variant(Swap versions/swap_double.c swap_double_pointer
  "swap_double(&a[1], &a[4]);" "swap_double(a + 1, a + 4);")
softprac_add_variant(Swap versions/swap_double.c swap_double_value
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
  "swap_double(&a[1], &a[4]);" "swap_double(a[1], a[4]);")
