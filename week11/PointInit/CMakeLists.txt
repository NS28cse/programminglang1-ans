# 第11回 発展1 PointInit
# 本体に加えて，指定初期化子を名前なしの {2.0, 10.0} に変えた版（宣言順に対応する）をテストする
softprac_add_program(PointInit point_init.c)

softprac_add_variant(PointInit point_init.c positional
  "Point a = {.y = 2.0, .x = 10.0}; // 指定した名前どおり x=10.0, y=2.0"
  "Point a = {2.0, 10.0}; // 名前を指定しないので宣言順に x=2.0, y=10.0")
