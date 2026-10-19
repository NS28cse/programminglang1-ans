# デバッグ題材 BugFactorialOverflow（第14回）
# バグ入りの版は 13! で int の範囲を超える（符号付き整数の桁あふれは未定義動作）ので実行しない。テストは直した版だけ
softprac_add_program(BugFactorialOverflow factorial.c)

softprac_add_variant(BugFactorialOverflow factorial.c fixed
  "// デバッグ題材: 大きな階乗（第14回）"
  "// デバッグ題材: 大きな階乗（第14回）を直した版。15! まで表せる long long で計算する。"
  "int factorial(int n)"
  "long long factorial(int n)"
  [=[printf("%2d! = %d\n", n, factorial(n));]=]
  [=[printf("%2d! = %lld\n", n, factorial(n));]=])
