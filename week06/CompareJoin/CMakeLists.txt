# 第6回 課題4 CompareJoin
# 本体（容量10，suffix "fuga"）に加えて，演習ページの「容量の境界」の表（9，8）と
# 「比較の条件を変える」（suffix を "hoge"，"z"，""）の版，容量の下限5の版をビルドしてテストする
softprac_add_program(CompareJoin compare_join.c)

softprac_add_variant(CompareJoin compare_join.c capacity_9 "char text[10]" "char text[9]")
softprac_add_variant(CompareJoin compare_join.c capacity_8 "char text[10]" "char text[8]")
softprac_add_variant(CompareJoin compare_join.c capacity_5 "char text[10]" "char text[5]")
softprac_add_variant(CompareJoin compare_join.c capacity_5_suffix_empty
                     "char text[10]" "char text[5]" "suffix[] = \"fuga\"" "suffix[] = \"\"")
softprac_add_variant(CompareJoin compare_join.c suffix_hoge "suffix[] = \"fuga\"" "suffix[] = \"hoge\"")
softprac_add_variant(CompareJoin compare_join.c suffix_z "suffix[] = \"fuga\"" "suffix[] = \"z\"")
softprac_add_variant(CompareJoin compare_join.c suffix_empty "suffix[] = \"fuga\"" "suffix[] = \"\"")
