# デバッグ題材 BugAverage（第6回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugAverage average.c)

softprac_add_variant(BugAverage average.c fixed
  "// デバッグ題材: 平均点（第6回）"
  "// デバッグ題材: 平均点（第6回）を直した版。割る前に double へ変換する。"
  "double mean = total / COUNT;"
  "double mean = (double)total / COUNT;")
