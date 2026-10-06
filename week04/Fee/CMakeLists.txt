# 第4回 課題1 Fee
# 本体（age = 17）に加えて，演習ページの表の age（-1, 0, 5, 6, 18）に変えた版をビルドしてテストする
softprac_add_program(Fee fee.c)

softprac_add_variant(Fee fee.c age_m1 "age = 17" "age = -1")
softprac_add_variant(Fee fee.c age_0  "age = 17" "age = 0")
softprac_add_variant(Fee fee.c age_5  "age = 17" "age = 5")
softprac_add_variant(Fee fee.c age_6  "age = 17" "age = 6")
softprac_add_variant(Fee fee.c age_18 "age = 17" "age = 18")
