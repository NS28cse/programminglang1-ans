# 第11回 課題3 Rect
# 本体に加えて，面積の境界の表の各行，前提（upper >= lower）を守らない座標，名前の容量の境界の版をテストする。
# 各版は先頭コメントを版の説明に置き換え，書き換えた行のコメントも書き換え後のコードに合わせる。
# 置換前の文字列は行末のコメントまで含めた行全体にする
softprac_add_program(Rect rect.c)

set(header "// 第11回 課題3: Point を 2 つ持つ Rect（入れ子の構造体）の面積とメンバ参照")
set(range "    // 座標は -1000〜1000 で，upper の x・y はそれぞれ lower 以上にする")
set(lower "        .lower = {1.0, 2.0},")
set(upper "        .upper = {5.0, 5.0},")
set(rename [=[    if (!set_name(&r, "other")) {]=])

# 面積の境界の表: 幅 0，高さ 0，負の座標
softprac_add_variant(Rect rect.c zero_width
  "${header}"
  "// 第11回 課題3: upper を (1, 5) に書き換えた版（lower=(1, 2) と x が同じで幅 0，面積 0.0）"
  "${upper}" "        .upper = {1.0, 5.0}, // 幅 0（x が lower と同じ）")
softprac_add_variant(Rect rect.c zero_height
  "${header}"
  "// 第11回 課題3: upper を (5, 2) に書き換えた版（lower=(1, 2) と y が同じで高さ 0，面積 0.0）"
  "${upper}" "        .upper = {5.0, 2.0}, // 高さ 0（y が lower と同じ）")
softprac_add_variant(Rect rect.c negative_coords
  "${header}"
  "// 第11回 課題3: lower を (-2, -1)，upper を (1, 3) に書き換えた版（座標が負でも差が 0 以上なので面積 12.0）"
  "${lower}" "        .lower = {-2.0, -1.0}, // 負の座標"
  "${upper}" "        .upper = {1.0, 3.0},")

# 前提を守らない例: 両方逆なら面積が正になり，片方だけ逆なら負になる
softprac_add_variant(Rect rect.c reversed_both
  "${header}"
  "// 第11回 課題3 誤りの例: lower と upper を x・y とも逆にした版（前提を守らないが，差が両方負なので面積は正の 12.0）"
  "${range}" "    // 誤り: 前提（upper >= lower）を x・y とも守らない座標"
  "${lower}" "        .lower = {5.0, 5.0},"
  "${upper}" "        .upper = {1.0, 2.0},")
softprac_add_variant(Rect rect.c reversed_y
  "${header}"
  "// 第11回 課題3 誤りの例: y だけ lower と upper を逆にした版（前提を守らないので面積が負の -12.0）"
  "${range}" "    // 誤り: 前提（upper >= lower）を y だけ守らない座標"
  "${lower}" "        .lower = {1.0, 5.0},"
  "${upper}" "        .upper = {5.0, 2.0},")

# name[21] に入る最長の 20 文字と，入らない 21 文字
softprac_add_variant(Rect rect.c name_20
  "${header}"
  "// 第11回 課題3: set_name に 20 文字（name[21] に入る最長）を渡す版。renamed=abcdefghijklmnopqrst と表示する"
  "${rename}"
  [=[    if (!set_name(&r, "abcdefghijklmnopqrst")) { // 20 文字と終端でちょうど 21 要素]=])
softprac_add_variant(Rect rect.c name_21
  "${header}"
  "// 第11回 課題3: 21 文字（終端が入らない）を渡す版。name too long を出して 1 で終わる"
  "${rename}"
  [=[    if (!set_name(&r, "abcdefghijklmnopqrstu")) { // 21 文字なので終端が入らず 0 が返る]=])
