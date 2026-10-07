# 第10回 発展1 NumberFormats
# 本体は演習ページの表示例（text=0.50 1.25 -2.00 / binary=0.50 1.25 -2.00）を出す版。
# data[0] を 0.125 にし，最後の 2 行の表示書式だけ %.3f へ変えた版を precision_0125 としてテストする
#   （保存の書式 %.2f は変えない。期待値: variants/tests/precision_0125.*）
softprac_add_program(NumberFormats number_formats.c)

softprac_add_variant(NumberFormats number_formats.c precision_0125
  "{0.5, 1.25, -2.0}" "{0.125, 1.25, -2.0}"
  [["text=%.2f %.2f %.2f\n"]] [["text=%.3f %.3f %.3f\n"]]
  [["binary=%.2f %.2f %.2f\n"]] [["binary=%.3f %.3f %.3f\n"]])
