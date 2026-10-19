# デバッグ題材 BugRowSum（第5回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugRowSum row_sum.c)

softprac_add_variant(BugRowSum row_sum.c fixed
  "// デバッグ題材: 行ごとの合計（第5回）"
  "// デバッグ題材: 行ごとの合計（第5回）を直した版。sum を行ごとに 0 から数え直す。"
  [=[
    int sum = 0;

    for (int row = 0; row < ROWS; ++row) {
]=]
  [=[

    for (int row = 0; row < ROWS; ++row) {
        int sum = 0;
]=])
