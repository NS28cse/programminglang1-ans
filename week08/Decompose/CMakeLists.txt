# 第8回 発展 Decompose
# 本体は演習ページのプログラム（decompose(3.14, ...)）に min_pointer の定義だけを加えた版。
# 各確認は一部を書き換えた版としてテストする（生成ソースの先頭コメントも版に合わせる）
#   minus_3_14 / zero / five           … 検証表の入力 −3.14，0.0，5.0
#   minus_100 / plus_100 / x_99_99 / minus_0_5 … 範囲の両端，小数部が大きい値，0 方向への切り捨て
#   value_args                         … 仮引数を値引数 long whole, double fraction にした版（呼び出し元は 0 のまま）
#   min_pointer_9_3 / _3_9 / _5_5      … main で演習の min_pointer の実験を行う（初期値を逆・同じにした版も）
softprac_add_program(Decompose decompose.c)

# 本体の先頭コメントの 5〜6 行目。書き換え版ではこれを版の説明に置き換える
set(head [=[ * main は演習ページのプログラムどおり．入力を変えた版・値引数の版・min_pointer の実験は
 * CMakeLists.txt で書き換えた版としてテストする．]=])

foreach(spec "minus_3_14;-3.14;検証表" "zero;0.0;検証表" "five;5.0;検証表"
             "minus_100;-100.0;範囲の下端" "plus_100;100.0;範囲の上端"
             "x_99_99;99.99;小数部が大きい値" "minus_0_5;-0.5;0 方向への切り捨ての確認")
  list(GET spec 0 tag)
  list(GET spec 1 value)
  list(GET spec 2 why)
  softprac_add_variant(Decompose decompose.c ${tag}
    "${head}" " * 書き換え版 ${tag}: 演習ページのプログラムの入力を ${value} に変えた版（${why}）．"
    "decompose(3.14," "decompose(${value},")
endforeach()

# 値引数の版．代入した値を関数内で表示する（表示しないと -Wunused-but-set-parameter の警告になる）
softprac_add_variant(Decompose decompose.c value_args
  "整数部（long）と小数部（double）の 2 つの出力先へ書き込む"
  "仮引数を値引数にした誤りの例（呼び出し元へは書き込めない）"
  "${head}" [=[ * 書き換え版 value_args: decompose の仮引数を値引数 long whole, double fraction にした版．
 * 関数内のコピーだけが変わり，main の whole と fraction は 0 のまま．]=]
  "/* x は −100〜100 の有限な値．whole と fraction は有効な long と double を指す */"
  "/* 値引数にした版：whole と fraction は呼び出し元の値のコピー（呼び出し元は変わらない） */"
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
  softprac_add_variant(Decompose decompose.c min_pointer_${tag}
    "${head}" " * 書き換え版 min_pointer_${tag}: main を min_pointer の実験（x=${xv}, y=${yv}）に書き換えた版．
 * 返された場所（呼び出し元の x か y）へ 0 を書く．"
    "${decompose_main}"
    "    int x = ${xv};
    int y = ${yv};
    int *result = min_pointer(&x, &y);
    printf(\"minimum=%d points_to_y=%d\\n\", *result, result == &y);
    *result = 0;
    printf(\"x=%d y=%d\\n\", x, y);")
endforeach()
