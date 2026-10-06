# 第4回 課題3（Table）: 本体（3 行 3 列）と，列の上限と列間の判定を 4 にした版（3 行 4 列）をビルドしてテストする
softprac_add_program(Table table.c)

include("${CMAKE_CURRENT_SOURCE_DIR}/../_cmake/variants.cmake")
week04_add_variant(cols_4 table.c variants/cols_4 "col <= 3" "col <= 4" "col < 3" "col < 4")
