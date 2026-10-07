# 第4回 発展 YearGroup
# 本体（switch 版，school_year = 1）に加えて，school_year を 0〜5 に変えた版を，
# switch 版と if・else if・else 版（versions/）でビルドしてテストする
softprac_add_program(YearGroup year_group.c)

foreach(year 0 2 3 4 5)
  softprac_add_variant(YearGroup year_group.c switch_year_${year} "school_year = 1" "school_year = ${year}")
endforeach()
softprac_add_variant(YearGroup versions/year_group_if.c if_year_1)
foreach(year 0 2 3 4 5)
  softprac_add_variant(YearGroup versions/year_group_if.c if_year_${year} "school_year = 1" "school_year = ${year}")
endforeach()

# 最初の break を外した版（1・2 では lower years の後に upper years も表示する。0, 3, 4, 5 は元と同じ）
set(break_old [=[        printf("lower years\n");
        break;              // これがないと次の case の文へ続けて実行する（フォールスルー）
]=])
set(break_new [=[        printf("lower years\n");
]=])
softprac_add_variant(YearGroup year_group.c no_first_break_year_1 "${break_old}" "${break_new}")
foreach(year 0 2 3 4 5)
  softprac_add_variant(YearGroup year_group.c no_first_break_year_${year}
    "${break_old}" "${break_new}" "school_year = 1" "school_year = ${year}")
endforeach()
foreach(year 0 1 2 3 4 5)
  # わざと break を外した版なので，GCC の警告（-Wextra に含まれる -Wimplicit-fallthrough）だけを止める
  # （Clang 18 は -Wall -Wextra ではこの警告を出さない）
  target_compile_options(YearGroup_no_first_break_year_${year} PRIVATE $<$<C_COMPILER_ID:GNU>:-Wno-implicit-fallthrough>)
endforeach()
