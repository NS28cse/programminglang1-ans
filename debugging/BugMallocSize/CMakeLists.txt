# デバッグ題材 BugMallocSize（第13回）
# バグ入りの版は確保した領域の外へ書く（未定義動作）ので実行しない。テストは直した版だけ
softprac_add_program(BugMallocSize dynamic.c)

softprac_add_variant(BugMallocSize dynamic.c fixed
  "// デバッグ題材: 動的配列（第13回）"
  "// デバッグ題材: 動的配列（第13回）を直した版。malloc には要素数ではなくバイト数を渡す。"
  "int *values = malloc(n);"
  "int *values = malloc(n * sizeof *values);")
