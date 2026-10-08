# 第10回 発展1 NumberFormats
# 本体は演習ページの表示例（text=0.50 1.25 -2.00 / binary=0.50 1.25 -2.00）を出す版。
# data[0] を 0.125 にし，最後の 2 行の表示書式だけ %.3f へ変えた版を precision_0125 としてテストする
#   （保存の書式 %.2f は変えない。期待値: variants/tests/precision_0125.*）
# 置換前の文字列は行末のコメントまで含めた行全体にする
softprac_add_program(NumberFormats number_formats.c)

softprac_add_variant(NumberFormats number_formats.c precision_0125
  [[/* 第10回 発展1 NumberFormats: 3 つの double をテキスト（numbers.txt）とバイナリ（numbers.bin）で保存して読み戻す */]]
  [[/* 第10回 発展1 NumberFormats: 3 つの double をテキスト（numbers.txt）とバイナリ（numbers.bin）で保存して読み戻す（data[0] を 0.125 にし，最後の 2 行の表示だけ %.3f にした版。保存の書式は %.2f のまま） */]]
  "    const double data[COUNT] = {0.5, 1.25, -2.0};"
  "    const double data[COUNT] = {0.125, 1.25, -2.0};"
  [[    printf("text=%.2f %.2f %.2f\n", text_values[0], text_values[1], text_values[2]);]]
  [[    printf("text=%.3f %.3f %.3f\n", text_values[0], text_values[1], text_values[2]);]]
  [[    printf("binary=%.2f %.2f %.2f\n", binary_values[0], binary_values[1], binary_values[2]);]]
  [[    printf("binary=%.3f %.3f %.3f\n", binary_values[0], binary_values[1], binary_values[2]);]])
