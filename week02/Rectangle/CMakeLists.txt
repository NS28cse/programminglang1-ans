# 第2回 課題1 Rectangle
# 本体に加えて，「値を変えて確かめる」（width = 6 を 0，1 に変える）版をビルドしてテストする。
# 各版は先頭コメントの 2 行目も版の説明に置き換える（説明に width = 6 を含むので，値の置換を先に行う）
softprac_add_program(Rectangle rectangle.c)

set(rectangle_desc "// area に保存されるのは式ではなく，計算した時点の値であることを確かめる")

softprac_add_variant(Rectangle rectangle.c width_0
  "width = 6" "width = 0"
  "${rectangle_desc}"
  "// 途中の width = 6; を width = 0; に書き換えた版（3 行目だけが 0 になる）")
softprac_add_variant(Rectangle rectangle.c width_1
  "width = 6" "width = 1"
  "${rectangle_desc}"
  "// 途中の width = 6; を width = 1; に書き換えた版（3 行目だけが 7 になる）")
