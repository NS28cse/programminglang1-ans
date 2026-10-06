# 第11回 課題1 PointMove
# 本体（講義の structs.c）に加えて，移動量を変えた版・b.x を変更する版・3 つの呼び出し方の版をビルドしてテストする
softprac_add_program(PointMove structs.c)

# 移動量を変える（moved と move_in_place の 2 か所を同じ値にする）
softprac_add_variant(PointMove structs.c move_0_0
  "moved(a, 3.0, -1.0)" "moved(a, 0.0, 0.0)"
  "move_in_place(&a, 3.0, -1.0)" "move_in_place(&a, 0.0, 0.0)")
softprac_add_variant(PointMove structs.c move_m1_m2
  "moved(a, 3.0, -1.0)" "moved(a, -1.0, -2.0)"
  "move_in_place(&a, 3.0, -1.0)" "move_in_place(&a, -1.0, -2.0)")
softprac_add_variant(PointMove structs.c move_2_3
  "moved(a, 3.0, -1.0)" "moved(a, 2.0, 3.0)"
  "move_in_place(&a, 3.0, -1.0)" "move_in_place(&a, 2.0, 3.0)")

# 最後に b.x = 100.0; を追加して a と b を表示する（変わるのは b だけ）
softprac_add_variant(PointMove structs.c b_x_100
  [=[printf("a=(%.1f, %.1f)\n", a.x, a.y);]=]
  [=[printf("a=(%.1f, %.1f)\n", a.x, a.y);
    b.x = 100.0;
    printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);]=])

# 3 つの呼び出し方をそれぞれ独立に試す（b の宣言と表示は削除）
softprac_add_variant(PointMove structs.c call_discard
  "Point b = moved(a, 3.0, -1.0);" "moved(a, 3.0, -1.0);"
  [=[printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);]=] ""
  "move_in_place(&a, 3.0, -1.0);" "")
softprac_add_variant(PointMove structs.c call_assign
  "Point b = moved(a, 3.0, -1.0);" "a = moved(a, 3.0, -1.0);"
  [=[printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);]=] ""
  "move_in_place(&a, 3.0, -1.0);" "")
softprac_add_variant(PointMove structs.c call_in_place
  "Point b = moved(a, 3.0, -1.0);" ""
  [=[printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);]=] "")
