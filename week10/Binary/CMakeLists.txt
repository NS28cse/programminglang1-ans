# 第10回 課題3 Binary
# 本体（フォルダのソース）は data を UTF-8 の「あ」と LF へ置き換えた最終版。
# 置き換える前の講義の binary.c（41 00 42 0A）も sample としてビルドしてテストする
softprac_add_program(Binary binary.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/Week10Variant.cmake")
set(utf8_data [[{0xE3, 0x81, 0x82, 0x0A}]])
set(sample_data [[{0x41, 0x00, 0x42, 0x0A}]])
week10_add_variant(Binary binary.c sample utf8_data sample_data)
