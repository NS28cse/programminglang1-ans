# 第11回 発展2 RectContains
# 本体（2 点 (1, 4)，(3, 1)，点 (2, 2)）に加えて，正規化の表・包含判定の表の各行，幅 0 の長方形，
# 名前の保持，2 点を一括で交換するだけの誤った版，上限を含める（<=）版をテストする
softprac_add_program(RectContains rect_contains.c)

set(lower ".lower = {.x = 1.0, .y = 4.0}")
set(upper ".upper = {.x = 3.0, .y = 1.0}")
set(point "Point p = {2.0, 2.0};")

# 正規化: 入力の 2 点の順序（(1, 4)，(3, 1) は本体の basic で確認）
softprac_add_variant(RectContains rect_contains.c order_1_1_3_4
  "${lower}" ".lower = {.x = 1.0, .y = 1.0}" "${upper}" ".upper = {.x = 3.0, .y = 4.0}")
softprac_add_variant(RectContains rect_contains.c order_3_4_1_1
  "${lower}" ".lower = {.x = 3.0, .y = 4.0}" "${upper}" ".upper = {.x = 1.0, .y = 1.0}")
softprac_add_variant(RectContains rect_contains.c order_3_1_1_4
  "${lower}" ".lower = {.x = 3.0, .y = 1.0}" "${upper}" ".upper = {.x = 1.0, .y = 4.0}")

# 包含判定: lower=(1, 1)，upper=(3, 4) に対する点（(2, 2) は本体の basic で確認）
softprac_add_variant(RectContains rect_contains.c point_1_1 "${point}" "Point p = {1.0, 1.0};")
softprac_add_variant(RectContains rect_contains.c point_1_3 "${point}" "Point p = {1.0, 3.0};")
softprac_add_variant(RectContains rect_contains.c point_3_2 "${point}" "Point p = {3.0, 2.0};")
softprac_add_variant(RectContains rect_contains.c point_2_4 "${point}" "Point p = {2.0, 4.0};")
softprac_add_variant(RectContains rect_contains.c point_0_2 "${point}" "Point p = {0.0, 2.0};")
softprac_add_variant(RectContains rect_contains.c point_2_5 "${point}" "Point p = {2.0, 5.0};")

# 幅 0 の長方形 lower=(1, 1)，upper=(1, 4) と p=(1, 2)
softprac_add_variant(RectContains rect_contains.c zero_width
  "${lower}" ".lower = {.x = 1.0, .y = 1.0}" "${upper}" ".upper = {.x = 1.0, .y = 4.0}"
  "${point}" "Point p = {1.0, 2.0};")

# 名前が normalized の戻り値へ引き継がれること
softprac_add_variant(RectContains rect_contains.c name_test_rect
  [=[.name = "sample"]=] [=[.name = "test_rect"]=])

# 誤り: x だけを比べて 2 点を丸ごと交換する（y の判定を削除）
softprac_add_variant(RectContains rect_contains.c swap_only_1_4_3_1
  "result.lower.x = r.upper.x;" "result.lower = r.upper;"
  "result.upper.x = r.lower.x;" "result.upper = r.lower;"
  [=[    if (r.lower.y > r.upper.y) {
        result.lower.y = r.upper.y;
        result.upper.y = r.lower.y;
    }
]=] "")
softprac_add_variant(RectContains rect_contains.c swap_only_3_1_1_4
  "result.lower.x = r.upper.x;" "result.lower = r.upper;"
  "result.upper.x = r.lower.x;" "result.upper = r.lower;"
  [=[    if (r.lower.y > r.upper.y) {
        result.lower.y = r.upper.y;
        result.upper.y = r.lower.y;
    }
]=] ""
  "${lower}" ".lower = {.x = 3.0, .y = 1.0}" "${upper}" ".upper = {.x = 1.0, .y = 4.0}")
softprac_add_variant(RectContains rect_contains.c swap_only_3_4_1_1
  "result.lower.x = r.upper.x;" "result.lower = r.upper;"
  "result.upper.x = r.lower.x;" "result.upper = r.lower;"
  [=[    if (r.lower.y > r.upper.y) {
        result.lower.y = r.upper.y;
        result.upper.y = r.lower.y;
    }
]=] ""
  "${lower}" ".lower = {.x = 3.0, .y = 4.0}" "${upper}" ".upper = {.x = 1.0, .y = 1.0}")

# 仕様を「上限も含む」に変えた版では (3, 2) も 1 になる
softprac_add_variant(RectContains rect_contains.c closed_3_2
  "p.x < r.upper.x" "p.x <= r.upper.x" "p.y < r.upper.y" "p.y <= r.upper.y"
  "${point}" "Point p = {3.0, 2.0};")
