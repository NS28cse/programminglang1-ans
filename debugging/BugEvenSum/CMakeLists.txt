# デバッグ題材 BugEvenSum（第4回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugEvenSum even_sum.c)

softprac_add_variant(BugEvenSum even_sum.c fixed
  "// デバッグ題材: 偶数の合計（第4回）"
  "// デバッグ題材: 偶数の合計（第4回）を直した版。n 自身も調べるよう，条件を i <= n にする。"
  "for (int i = 1; i < n; ++i) {"
  "for (int i = 1; i <= n; ++i) {")
