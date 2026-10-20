# デバッグ題材 BugAnswerCheck（第6回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugAnswerCheck answer_check.c)

softprac_add_variant(BugAnswerCheck answer_check.c fixed
  "// デバッグ題材: 答え合わせ（第6回）"
  "// デバッグ題材: 答え合わせ（第6回）を直した版。strcmp は等しいとき 0 を返すので，== 0 で比べる。"
  "if (strcmp(answer, guess)) {"
  "if (strcmp(answer, guess) == 0) {")
