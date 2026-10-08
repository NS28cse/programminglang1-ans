# 第8回 課題1 Swap
# 本体は講義の配布コード pointers.c のまま（期待する表示 x=8 y=5 / sum=60 / c at）。
# 演習の実験は書き換えた版・versions/ の版としてビルドしてテストする（生成されるソースの先頭コメントも版ごとに書き換える）
#   trace          … 宣言・*p = 5・swap の後の状態を表示する（「代入ごとの状態を記録する」の表）
#   y_5 / both_8   … trace に加えて，y の初期値を 5 にする／x と y の初期値だけを同じ 8 にする
#   wrong_swap     … swap 内の *a = *b を a = b に変える（交換にならない）
#   copy_pointer   … versions/copy_pointer.c（ポインタのコピーを比較する。置換なし）
#   swap_double_address / swap_double_pointer / swap_double_value
#                  … versions/swap_double.c（&a[1], &a[4]）と，a + 1, a + 4 の呼び出し，値引数にした版
softprac_add_program(Swap pointers.c)

# 本体の先頭コメント（2〜4 行目）。書き換え版ではこれを版の説明に置き換える
set(head [=[ * 第8回 課題1 Swap: 講義の配布コード pointers.c（docs/sample/08/pointers.c）そのもの
 * 演習の実験（状態の記録・初期値の変更・a = b の swap・ポインタのコピー・swap_double）は
 * CMakeLists.txt の書き換え版と versions/ の版でテストする．]=])
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
set(trace_note [=[ * 指す先はアドレスではなく p == &x の比較（1 か 0）で表示する（アドレスは実行ごとに変わるため）．]=])
softprac_add_variant(Swap pointers.c trace
  "${head}" " * 第8回 課題1 Swap（書き換え版 trace）: 講義の pointers.c の各文の後に，
 * x, y, p が x を指すか, *p を表示する版（「代入ごとの状態を記録する」の表）．
${trace_note}"
  "${steps}" "${steps_traced}")
softprac_add_variant(Swap pointers.c y_5
  "${head}" " * 第8回 課題1 Swap（書き換え版 y_5）: 状態を表示する版（trace）で，y の初期値を 5 にした版．
 * swap の直前に x と y が両方 5 になる．
${trace_note}"
  "${steps}" "${steps_traced}" "int x = 3, y = 8" "int x = 3, y = 5")
softprac_add_variant(Swap pointers.c both_8
  "${head}" " * 第8回 課題1 Swap（書き換え版 both_8）: 状態を表示する版（trace）で，x と y の初期値だけを同じ 8 にした版．
 * その後の *p = 5 が x だけを変えるので，swap の直前は 5 と 8 になる．
${trace_note}"
  "${steps}" "${steps_traced}" "int x = 3, y = 8" "int x = 8, y = 8")
softprac_add_variant(Swap pointers.c wrong_swap
  "${head}" [=[ * 第8回 課題1 Swap（書き換え版 wrong_swap）: 講義の pointers.c の swap を a = b にした誤りの例（交換にならない）．
 * a = b は局所変数 a（ポインタのコピー）の矢印を変えるだけで，x には何も書かれない．]=]
  [=[    int temp = *a;
    *a = *b;]=]
  [=[    int temp = *a;
    a = b;]=])

softprac_add_variant(Swap versions/copy_pointer.c copy_pointer)

set(sd_head [=[ * 初期配列の添字 1 と 4 を 1 回だけ交換して表示する（続けて 2 回呼ぶと元に戻るので，
 * a + 1, a + 4 の呼び出し方と値引数の版は CMakeLists.txt の書き換え版で別に試す）．]=])
softprac_add_variant(Swap versions/swap_double.c swap_double_address)
softprac_add_variant(Swap versions/swap_double.c swap_double_pointer
  "${sd_head}" [=[ * 呼び出しを swap_double(a + 1, a + 4); にした版（書き換え版 swap_double_pointer）．
 * a + 1 は &a[1] と同じ場所を表す．初期配列から 1 回だけ交換する．]=]
  "swap_double(&a[1], &a[4]);" "swap_double(a + 1, a + 4);")
softprac_add_variant(Swap versions/swap_double.c swap_double_value
  "${sd_head}" [=[ * 仮引数を値引数にした誤りの例（書き換え版 swap_double_value）．
 * コピーが交換されるだけで配列は変わらない．]=]
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
