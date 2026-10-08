# 第11回 発展2 RectContains
# 本体（2 点 (1, 4)，(3, 1)，点 (2, 2)）に加えて，正規化の表・包含判定の表の各行，幅 0 の長方形，
# 名前の保持，2 点を一括で交換するだけの誤った版，上限を含める（<=）版をテストする。
# 各版は先頭コメントを版の説明に置き換え，書き換えた行のコメントも書き換え後のコードに合わせる。
# 置換前の文字列は行末のコメントまで含めた行全体にする
softprac_add_program(RectContains rect_contains.c)

set(header "// 第11回 発展2: 2 点を軸ごとに下限・上限へそろえる normalized と，半開区間で判定する contains")
set(lower "        .lower = {.x = 1.0, .y = 4.0},")
set(upper "        .upper = {.x = 3.0, .y = 1.0},")
set(point "    Point p = {2.0, 2.0};")
set(name [=[        .name = "sample"]=])

# 正規化: 入力の 2 点の順序（(1, 4)，(3, 1) は本体の basic で確認）
softprac_add_variant(RectContains rect_contains.c order_1_1_3_4
  "${header}"
  "// 第11回 発展2: 入力の 2 点を (1, 1)，(3, 4)（既にそろった順序）に書き換えた版。正規化後も lower=(1, 1)，upper=(3, 4)"
  "${lower}" "        .lower = {.x = 1.0, .y = 1.0},"
  "${upper}" "        .upper = {.x = 3.0, .y = 4.0},")
softprac_add_variant(RectContains rect_contains.c order_3_4_1_1
  "${header}"
  "// 第11回 発展2: 入力の 2 点を (3, 4)，(1, 1)（x・y とも逆順）に書き換えた版。正規化後は lower=(1, 1)，upper=(3, 4)"
  "${lower}" "        .lower = {.x = 3.0, .y = 4.0},"
  "${upper}" "        .upper = {.x = 1.0, .y = 1.0},")
softprac_add_variant(RectContains rect_contains.c order_3_1_1_4
  "${header}"
  "// 第11回 発展2: 入力の 2 点を (3, 1)，(1, 4)（x だけ逆順）に書き換えた版。正規化後は lower=(1, 1)，upper=(3, 4)"
  "${lower}" "        .lower = {.x = 3.0, .y = 1.0},"
  "${upper}" "        .upper = {.x = 1.0, .y = 4.0},")

# 包含判定: lower=(1, 1)，upper=(3, 4) に対する点（(2, 2) は本体の basic で確認）
softprac_add_variant(RectContains rect_contains.c point_1_1
  "${header}"
  "// 第11回 発展2: 点 p を (1, 1) に書き換えた版。下限を含むので inside=1"
  "${point}" "    Point p = {1.0, 1.0}; // 下限の角")
softprac_add_variant(RectContains rect_contains.c point_1_3
  "${header}"
  "// 第11回 発展2: 点 p を (1, 3) に書き換えた版。x が下限でも y が範囲内なので inside=1"
  "${point}" "    Point p = {1.0, 3.0}; // x が下限")
softprac_add_variant(RectContains rect_contains.c point_3_2
  "${header}"
  "// 第11回 発展2: 点 p を (3, 2) に書き換えた版。x の上限を含まないので inside=0"
  "${point}" "    Point p = {3.0, 2.0}; // x が上限")
softprac_add_variant(RectContains rect_contains.c point_2_4
  "${header}"
  "// 第11回 発展2: 点 p を (2, 4) に書き換えた版。y の上限を含まないので inside=0"
  "${point}" "    Point p = {2.0, 4.0}; // y が上限")
softprac_add_variant(RectContains rect_contains.c point_0_2
  "${header}"
  "// 第11回 発展2: 点 p を (0, 2) に書き換えた版。x が下限より小さいので inside=0"
  "${point}" "    Point p = {0.0, 2.0}; // x が下限より小さい")
softprac_add_variant(RectContains rect_contains.c point_2_5
  "${header}"
  "// 第11回 発展2: 点 p を (2, 5) に書き換えた版。y が上限より大きいので inside=0"
  "${point}" "    Point p = {2.0, 5.0}; // y が上限より大きい")

# 幅 0 の長方形 lower=(1, 1)，upper=(1, 4) と p=(1, 2)
softprac_add_variant(RectContains rect_contains.c zero_width
  "${header}"
  "// 第11回 発展2: 2 点を (1, 1)，(1, 4)（幅 0），点 p を (1, 2) に書き換えた版。x >= 1 と x < 1 を同時に満たせないので inside=0"
  "${lower}" "        .lower = {.x = 1.0, .y = 1.0},"
  "${upper}" "        .upper = {.x = 1.0, .y = 4.0}, // x が同じなので幅 0"
  "${point}" "    Point p = {1.0, 2.0};")

# 名前が normalized の戻り値へ引き継がれること
softprac_add_variant(RectContains rect_contains.c name_test_rect
  "${header}"
  "// 第11回 発展2: 名前を \"test_rect\" に書き換えた版。normalized の戻り値へ名前が引き継がれることを確かめる"
  "${name}" [=[        .name = "test_rect"]=])

# 誤り: x だけを比べて 2 点を丸ごと交換する（y の判定を削除）
set(rule "// x と y を独立に比べ，小さい方を lower，大きい方を upper に置く")
set(rule_swap_only "// 誤り: x だけを比べて 2 点を丸ごと交換する（y は見ない）")
set(swap_x [=[        result.lower.x = r.upper.x;
        result.upper.x = r.lower.x;]=])
set(swap_whole [=[        result.lower = r.upper; // 誤り: y も一緒に入れ替わる
        result.upper = r.lower;]=])
set(swap_y [=[    if (r.lower.y > r.upper.y) {
        result.lower.y = r.upper.y;
        result.upper.y = r.lower.y;
    }
]=])
softprac_add_variant(RectContains rect_contains.c swap_only_1_4_3_1
  "${header}"
  "// 第11回 発展2 誤りの例: x だけを比べて 2 点を丸ごと交換する normalized（入力 (1, 4)，(3, 1)）。x が既に順序どおりなので交換せず，y が逆のまま残る"
  "${rule}" "${rule_swap_only}" "${swap_x}" "${swap_whole}" "${swap_y}" "")
softprac_add_variant(RectContains rect_contains.c swap_only_3_1_1_4
  "${header}"
  "// 第11回 発展2 誤りの例: x だけを比べて 2 点を丸ごと交換する normalized（入力 (3, 1)，(1, 4)）。交換で y が逆向きになる"
  "${rule}" "${rule_swap_only}" "${swap_x}" "${swap_whole}" "${swap_y}" ""
  "${lower}" "        .lower = {.x = 3.0, .y = 1.0},"
  "${upper}" "        .upper = {.x = 1.0, .y = 4.0},")
softprac_add_variant(RectContains rect_contains.c swap_only_3_4_1_1
  "${header}"
  "// 第11回 発展2 誤りの例: x だけを比べて 2 点を丸ごと交換する normalized（入力 (3, 4)，(1, 1)）。x・y とも逆なので偶然正しくなる"
  "${rule}" "${rule_swap_only}" "${swap_x}" "${swap_whole}" "${swap_y}" ""
  "${lower}" "        .lower = {.x = 3.0, .y = 4.0},"
  "${upper}" "        .upper = {.x = 1.0, .y = 1.0},")

# 仕様を「上限も含む」に変えた版では (3, 2) も 1 になる
softprac_add_variant(RectContains rect_contains.c closed_3_2
  "${header}"
  "// 第11回 発展2: contains を上限も含む（<=）閉区間に変えた版（この課題の仕様とは違う）。点 (3, 2) が inside=1 になる"
  "// 下限を含み上限を含まない（半開区間）。r は正規化済みであることが前提"
  "// 上限も含む（閉区間）に変えた版。この課題の仕様とは違う"
  "    return p.x >= r.lower.x && p.x < r.upper.x &&"
  "    return p.x >= r.lower.x && p.x <= r.upper.x &&"
  "           p.y >= r.lower.y && p.y < r.upper.y;"
  "           p.y >= r.lower.y && p.y <= r.upper.y;"
  "${point}" "    Point p = {3.0, 2.0}; // x が上限")
