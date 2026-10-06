# 第6回 ウォームアップ CharCode
# 本体に加えて，c を '0'，'9'，'A' に変えた版をビルドしてテストする（'A' では digit の行を出さない）
softprac_add_program(CharCode char_code.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/variants.cmake")
week06_add_variant(CharCode char_code.c c_0 "char c = '3'" "char c = '0'")
week06_add_variant(CharCode char_code.c c_9 "char c = '3'" "char c = '9'")
week06_add_variant(CharCode char_code.c c_A "char c = '3'" "char c = 'A'")
