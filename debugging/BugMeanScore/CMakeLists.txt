# デバッグ題材 BugMeanScore（第5回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugMeanScore mean_score.c)

softprac_add_variant(BugMeanScore mean_score.c fixed
  "// デバッグ題材: 点数の平均（第5回）"
  "// デバッグ題材: 点数の平均（第5回）を直した版。割る前に合計を double に変換する。"
  "    double mean = sum / n;"
  "    double mean = (double)sum / n;")
