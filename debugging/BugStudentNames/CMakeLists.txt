# デバッグ題材 BugStudentNames（第11回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugStudentNames students.c)

softprac_add_variant(BugStudentNames students.c fixed
  "// デバッグ題材: 名簿を読む（第11回）"
  "// デバッグ題材: 名簿を読む（第11回）を直した版。名前を各要素の配列メンバへコピーする。"
  "    char *name;"
  "    char name[MAX_NAME + 1];"
  "students[count].name = line;"
  "strcpy(students[count].name, line);")
