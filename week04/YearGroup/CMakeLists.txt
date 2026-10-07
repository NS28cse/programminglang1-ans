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

# 最初の break を外した版（school_year = 2 で lower years の後に upper years も表示する）
foreach(year 1 2)
  softprac_add_variant(YearGroup year_group.c no_first_break_year_${year}
    [=[        printf("lower years\n");
        break;              // これがないと次の case の文へ続けて実行する（フォールスルー）
]=]
    [=[        printf("lower years\n");
]=]
    "school_year = 1" "school_year = ${year}")
  # わざと break を外した版なので，GCC の警告（-Wimplicit-fallthrough，-Wextra に含まれる）だけを止める
  target_compile_options(YearGroup_no_first_break_year_${year} PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wno-implicit-fallthrough>)
endforeach()
