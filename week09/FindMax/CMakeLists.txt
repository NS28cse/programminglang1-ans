# 第9回 課題1 FindMax
# 本体に加えて，演習ページの書き換え（比較を >= にする，*out = &a[0] にする）の版をビルドしてテストする
softprac_add_program(FindMax double_pointer.c)

softprac_add_variant(FindMax double_pointer.c tie_ge "if (a[i] > *best)" "if (a[i] >= *best)")
softprac_add_variant(FindMax double_pointer.c out_first "*out = best" "*out = &a[0]")
