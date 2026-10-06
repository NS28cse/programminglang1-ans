# 第6回 課題3 Average
# 本体に加えて，i を 100 に変えた版（どの形でも 10000 が int の範囲内）をビルドしてテストする。
# キャストを外した i * i の版は範囲外の計算になるので作らない（演習ページの指示どおり読解だけ）
softprac_add_program(Average average.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/variants.cmake")
week06_add_variant(Average average.c i_100 "int i = 50000" "int i = 100")
