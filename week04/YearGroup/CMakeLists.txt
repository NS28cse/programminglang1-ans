# 第4回 発展 YearGroup
# 本体（switch 版，school_year = 1）に加えて，school_year を 0〜5 に変えた版を，
# switch 版と if・else if・else 版（versions/）でビルドしてテストする
# （if 版の school_year = 1 は "school_year = 1" を同じ文字列に置き換えて，そのままビルドしている）
softprac_add_program(YearGroup year_group.c)

foreach(year 0 2 3 4 5)
  softprac_add_variant(YearGroup year_group.c switch_year_${year} "school_year = 1" "school_year = ${year}")
endforeach()
foreach(year 0 1 2 3 4 5)
  softprac_add_variant(YearGroup versions/year_group_if.c if_year_${year} "school_year = 1" "school_year = ${year}")
endforeach()
