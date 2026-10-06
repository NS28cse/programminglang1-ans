# 第4回 発展（YearGroup）: 本体（switch 版）と，school_year を 0〜5 に変えた版・if 版をビルドしてテストする
softprac_add_program(YearGroup year_group.c)

include("${CMAKE_CURRENT_SOURCE_DIR}/../_cmake/variants.cmake")
foreach(year 0 2 3 4 5)
  week04_add_variant(switch_year_${year} year_group.c variants/year_${year}
                     "school_year = 1" "school_year = ${year}")
endforeach()
foreach(year 0 1 2 3 4 5)
  week04_add_variant(if_year_${year} versions/year_group_if.c variants/year_${year}
                     "school_year = 1" "school_year = ${year}")
endforeach()
