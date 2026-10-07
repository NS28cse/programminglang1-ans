# 第11回 課題3 Rect
# 本体に加えて，面積の境界の表の各行，前提（upper >= lower）を守らない座標，名前の容量の境界の版をテストする
softprac_add_program(Rect rect.c)

softprac_add_variant(Rect rect.c zero_width ".upper = {5.0, 5.0}" ".upper = {1.0, 5.0}")
softprac_add_variant(Rect rect.c zero_height ".upper = {5.0, 5.0}" ".upper = {5.0, 2.0}")
softprac_add_variant(Rect rect.c negative_coords
  ".lower = {1.0, 2.0}" ".lower = {-2.0, -1.0}"
  ".upper = {5.0, 5.0}" ".upper = {1.0, 3.0}")

# 前提を守らない例: 両方逆なら面積が正になり，片方だけ逆なら負になる
softprac_add_variant(Rect rect.c reversed_both
  "// 座標は -1000〜1000 で，upper の x・y はそれぞれ lower 以上にする" "// 誤り: 前提（upper >= lower）を x・y とも守らない座標"
  ".lower = {1.0, 2.0}" ".lower = {5.0, 5.0}"
  ".upper = {5.0, 5.0}" ".upper = {1.0, 2.0}")
softprac_add_variant(Rect rect.c reversed_y
  "// 座標は -1000〜1000 で，upper の x・y はそれぞれ lower 以上にする" "// 誤り: 前提（upper >= lower）を y だけ守らない座標"
  ".lower = {1.0, 2.0}" ".lower = {1.0, 5.0}"
  ".upper = {5.0, 5.0}" ".upper = {5.0, 2.0}")

# name[21] に入る最長の 20 文字と，入らない 21 文字
softprac_add_variant(Rect rect.c name_20
  [=[set_name(&r, "other")]=] [=[set_name(&r, "abcdefghijklmnopqrst")]=])
softprac_add_variant(Rect rect.c name_21
  [=[set_name(&r, "other")]=] [=[set_name(&r, "abcdefghijklmnopqrstu")]=])
