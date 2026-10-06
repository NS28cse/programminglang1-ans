# 第6回 課題2 Lower
# 本体（"Hello C17!"）に加えて，演習ページの表の初期値に変えた版をビルドしてテストする
softprac_add_program(Lower lower.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/variants.cmake")
week06_add_variant(Lower lower.c empty "\"Hello C17!\"" "\"\"")
week06_add_variant(Lower lower.c AZaz09 "\"Hello C17!\"" "\"AZaz09\"")
week06_add_variant(Lower lower.c at_AZ_bracket "\"Hello C17!\"" "\"@AZ[\"")
week06_add_variant(Lower lower.c A_space_B "\"Hello C17!\"" "\"A B\"")
