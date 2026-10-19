# デバッグ題材 BugUpper（第7回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugUpper upper.c)

softprac_add_variant(BugUpper upper.c fixed
  "// デバッグ題材: 大文字にして写す（第7回）"
  "// デバッグ題材: 大文字にして写す（第7回）を直した版。1 回の繰り返しで getchar を 1 回だけ呼ぶ。"
  [=[
    while (getchar() != EOF) {
        ch = getchar();
]=]
  [=[
    while ((ch = getchar()) != EOF) {
]=])
