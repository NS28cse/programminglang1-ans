# 第2回 課題1 Rectangle
# 本体に加えて，「値を変えて確かめる」（width = 6 を 0，1 に変える）版をビルドしてテストする
softprac_add_program(Rectangle rectangle.c)

softprac_add_variant(Rectangle rectangle.c width_0 "width = 6" "width = 0")
softprac_add_variant(Rectangle rectangle.c width_1 "width = 6" "width = 1")
