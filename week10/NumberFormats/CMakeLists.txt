# 第10回 発展1 NumberFormats
# 本体（フォルダのソース）は data[0] を 0.125，最後の 2 行の表示を %.3f にした最終版。
# 変更前（0.50 1.25 -2.00 を %.2f で表示する，演習ページの表示例の版）も basic としてビルドしてテストする
#   期待値: variants/tests/basic.*
softprac_add_program(NumberFormats number_formats.c)

softprac_add_variant(NumberFormats number_formats.c basic
  "{0.125, 1.25, -2.0}" "{0.5, 1.25, -2.0}"
  [["text=%.3f %.3f %.3f\n"]] [["text=%.2f %.2f %.2f\n"]]
  [["binary=%.3f %.3f %.3f\n"]] [["binary=%.2f %.2f %.2f\n"]])
