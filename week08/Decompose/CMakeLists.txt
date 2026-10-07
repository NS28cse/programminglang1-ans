# 第8回 発展 Decompose
# フォルダのソースは演習ページのプログラム（decompose(3.14, ...)）に min_pointer の定義を加えた最終版。
# 各確認は一部を書き換えた版としてテストする
#   minus_3_14 / zero / five           … 検証表の入力 −3.14，0.0，5.0
#   minus_100 / plus_100 / x_99_99 / minus_0_5 … 範囲の両端，小数部が大きい値，0 方向への切り捨て
#   value_args                         … 仮引数を値引数 long whole, double fraction にした版（呼び出し元は 0 のまま）
#   min_pointer_9_3 / _3_9 / _5_5      … main で演習の min_pointer の実験を行う（初期値を逆・同じにした版も）
softprac_add_program(Decompose decompose.c)

softprac_add_variant(Decompose decompose.c minus_3_14 "decompose(3.14," "decompose(-3.14,")
softprac_add_variant(Decompose decompose.c zero "decompose(3.14," "decompose(0.0,")
softprac_add_variant(Decompose decompose.c five "decompose(3.14," "decompose(5.0,")
softprac_add_variant(Decompose decompose.c minus_100 "decompose(3.14," "decompose(-100.0,")
softprac_add_variant(Decompose decompose.c plus_100 "decompose(3.14," "decompose(100.0,")
softprac_add_variant(Decompose decompose.c x_99_99 "decompose(3.14," "decompose(99.99,")
softprac_add_variant(Decompose decompose.c minus_0_5 "decompose(3.14," "decompose(-0.5,")

# 値引数の版．代入した値を関数内で表示する（表示しないと -Wunused-but-set-parameter の警告になる）
softprac_add_variant(Decompose decompose.c value_args
  "void decompose(double x, long *whole, double *fraction)"
  "void decompose(double x, long whole, double fraction)"
  [=[    *whole = (long)x;          /* 0 方向への切り捨て（四捨五入でも床関数でもない） */
    *fraction = x - *whole;]=]
  [=[    whole = (long)x;           /* 変わるのは関数内のコピーだけ */
    fraction = x - whole;
    printf("in function: whole=%ld fraction=%.2f\n", whole, fraction);]=]
  "&whole, &fraction" "whole, fraction")

set(decompose_main [=[    long whole = 0;
    double fraction = 0.0;
    decompose(3.14, &whole, &fraction);
    printf("whole=%ld fraction=%.2f\n", whole, fraction);]=])
foreach(pair "9_3;9;3" "3_9;3;9" "5_5;5;5")
  list(GET pair 0 tag)
  list(GET pair 1 xv)
  list(GET pair 2 yv)
  softprac_add_variant(Decompose decompose.c min_pointer_${tag} "${decompose_main}"
    "    int x = ${xv};
    int y = ${yv};
    int *result = min_pointer(&x, &y);
    printf(\"minimum=%d points_to_y=%d\\n\", *result, result == &y);
    *result = 0;
    printf(\"x=%d y=%d\\n\", x, y);")
endforeach()
