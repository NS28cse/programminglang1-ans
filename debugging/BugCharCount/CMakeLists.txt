# デバッグ題材 BugCharCount（第10回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugCharCount char_count.c)

softprac_add_variant(BugCharCount char_count.c fixed
  "// デバッグ題材: ファイルの文字数と行数（第10回）"
  "// デバッグ題材: ファイルの文字数と行数（第10回）を直した版。fgetc の戻り値が EOF かでループを終える。"
  [=[
    while (!feof(fp)) {
        int ch = fgetc(fp);
]=]
  [=[
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
]=])
