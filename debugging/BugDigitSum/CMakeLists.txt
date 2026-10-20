# デバッグ題材 BugDigitSum（第6回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugDigitSum digit_sum.c)

softprac_add_variant(BugDigitSum digit_sum.c fixed
  "// デバッグ題材: 各桁の和（第6回）"
  "// デバッグ題材: 各桁の和（第6回）を直した版。文字コードから '0' の文字コードを引いて数にする。"
  "sum += digits[i];"
  "sum += digits[i] - '0';")
