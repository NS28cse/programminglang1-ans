# 第8回 課題4 PointerWalk
# 本体に加えて，「値と終端を変えて確認する」「q を a + 1 へ変える」「set_one の仮引数を int a[] にする」
# の書き換えをした版をテストする
softprac_add_program(PointerWalk pointer_walk.c)

softprac_add_variant(PointerWalk pointer_walk.c zeros "{2, 4, 6, 3, 5}" "{0, 0, 0, 0, 0}")
softprac_add_variant(PointerWalk pointer_walk.c ascending "{2, 4, 6, 3, 5}" "{1, 2, 3, 4, 5}")
softprac_add_variant(PointerWalk pointer_walk.c q_a1 "int *q = a + 3" "int *q = a + 1")
softprac_add_variant(PointerWalk pointer_walk.c length_empty "pointer_length(\"cat\")" "pointer_length(\"\")")
softprac_add_variant(PointerWalk pointer_walk.c length_A "pointer_length(\"cat\")" "pointer_length(\"A\")")
softprac_add_variant(PointerWalk pointer_walk.c length_Hello "pointer_length(\"cat\")" "pointer_length(\"Hello\")")
softprac_add_variant(PointerWalk pointer_walk.c set_one_array_param "void set_one(int *a, int n)" "void set_one(int a[], int n)")
