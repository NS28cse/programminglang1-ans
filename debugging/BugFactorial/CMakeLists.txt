# デバッグ題材 BugFactorial（第14回）
# バグ入りの版は factorial(0) から再帰が止まらず異常終了するので実行しない。テストは直した版だけ
softprac_add_program(BugFactorial factorial.c)

softprac_add_variant(BugFactorial factorial.c fixed
  "// デバッグ題材: 階乗の表（第14回）"
  "// デバッグ題材: 階乗の表（第14回）を直した版。基底条件を範囲の最小値 n == 0 にする。"
  "if (n == 1) {"
  "if (n == 0) {")
