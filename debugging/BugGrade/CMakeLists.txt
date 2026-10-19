# デバッグ題材 BugGrade（第5回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugGrade grade.c)

softprac_add_variant(BugGrade grade.c fixed
  "// デバッグ題材: 点数から評価を決める（第5回）"
  "// デバッグ題材: 点数から評価を決める（第5回）を直した版。厳しい条件（大きい下限）から順に調べる。"
  [=[
    if (score >= 60) {
        return 'C';
    } else if (score >= 70) {
        return 'B';
    } else if (score >= 80) {
        return 'A';
    }]=]
  [=[
    if (score >= 80) {
        return 'A';
    } else if (score >= 70) {
        return 'B';
    } else if (score >= 60) {
        return 'C';
    }]=])
