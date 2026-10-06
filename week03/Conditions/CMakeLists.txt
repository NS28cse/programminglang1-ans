# 第3回 課題3 Conditions
# 本体に加えて，「条件の境界を試す」版（1 項目ずつ変える）をビルドしてテストする
softprac_add_program(Conditions conditions.c)

# score を -1，0，100，101 に変える（d は 0 のまま）
softprac_add_variant(Conditions conditions.c score_minus1 "score = 75" "score = -1")
softprac_add_variant(Conditions conditions.c score_0 "score = 75" "score = 0")
softprac_add_variant(Conditions conditions.c score_100 "score = 75" "score = 100")
softprac_add_variant(Conditions conditions.c score_101 "score = 75" "score = 101")
# score を 75 に戻して，d を 3，6 に変える
softprac_add_variant(Conditions conditions.c d_3 "int d = 0" "int d = 3")
softprac_add_variant(Conditions conditions.c d_6 "int d = 0" "int d = 6")
