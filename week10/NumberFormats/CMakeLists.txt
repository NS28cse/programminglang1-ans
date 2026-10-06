# 第10回 発展1 NumberFormats
# 本体（フォルダのソース）は data[0] を 0.125，最後の 2 行の表示を %.3f にした最終版。
# 変更前（0.50 1.25 -2.00 を %.2f で表示する，演習ページの表示例の版）も basic としてビルドしてテストする
softprac_add_program(NumberFormats number_formats.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/Week10Variant.cmake")
set(data_final [[{0.125, 1.25, -2.0}]])
set(data_basic [[{0.5, 1.25, -2.0}]])
set(text_final [["text=%.3f %.3f %.3f\n"]])
set(text_basic [["text=%.2f %.2f %.2f\n"]])
set(binary_final [["binary=%.3f %.3f %.3f\n"]])
set(binary_basic [["binary=%.2f %.2f %.2f\n"]])
week10_add_variant(NumberFormats number_formats.c basic
  data_final data_basic text_final text_basic binary_final binary_basic)
