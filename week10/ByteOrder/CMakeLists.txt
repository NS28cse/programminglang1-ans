# 第10回 課題3「バイト順を調べる」ByteOrder（演習ページの「別の main」。プロジェクト名は解答で付けた）
# 本体（フォルダのソース）は value を 0x1234 へ変更した最終版。変更前（value = 1）も value_1 としてテストする
softprac_add_program(ByteOrder byte_order.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/Week10Variant.cmake")
set(value_1234 [[unsigned short value = 0x1234;]])
set(value_1 [[unsigned short value = 1;]])
week10_add_variant(ByteOrder byte_order.c value_1 value_1234 value_1)
