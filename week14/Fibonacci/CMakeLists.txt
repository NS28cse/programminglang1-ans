# 第14回 発展1 Fibonacci
# 本体に加えて，「計測結果の読み方」2（stats を初期化せずに再び fib を呼ぶ）の版をビルドしてテストする
softprac_add_program(Fibonacci fibonacci.c)

# 同じ stats で fib(n) を 2 回続けて呼ぶ（calls は 2 倍に積み上がり，max_depth は変わらない）
softprac_add_variant(Fibonacci fibonacci.c no_reset
  "unsigned long long result = fib(n, 1, &stats)"
  "unsigned long long result = (fib(n, 1, &stats), fib(n, 1, &stats))")
