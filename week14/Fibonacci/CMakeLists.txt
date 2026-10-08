# 第14回 発展1 Fibonacci
# 本体（input = 4）に加えて，main の input を書き換えた版（表の値と -1，21）と，
# 「計測結果の読み方」2（stats を初期化せずに再び fib を呼ぶ）の版をビルドしてテストする
softprac_add_program(Fibonacci fibonacci.c)

softprac_add_variant(Fibonacci fibonacci.c n_0 "int input = 4;" "int input = 0;")
softprac_add_variant(Fibonacci fibonacci.c n_1 "int input = 4;" "int input = 1;")
softprac_add_variant(Fibonacci fibonacci.c n_2 "int input = 4;" "int input = 2;")
softprac_add_variant(Fibonacci fibonacci.c n_3 "int input = 4;" "int input = 3;")
softprac_add_variant(Fibonacci fibonacci.c n_5 "int input = 4;" "int input = 5;")
softprac_add_variant(Fibonacci fibonacci.c n_10 "int input = 4;" "int input = 10;")
softprac_add_variant(Fibonacci fibonacci.c n_20 "int input = 4;" "int input = 20;")
softprac_add_variant(Fibonacci fibonacci.c n_minus1 "int input = 4;" "int input = -1;")
softprac_add_variant(Fibonacci fibonacci.c n_21 "int input = 4;" "int input = 21;")

# 同じ stats のまま fib(n) をもう一度呼ぶ（calls は 2 倍に積み上がり，max_depth は変わらない）
softprac_add_variant(Fibonacci fibonacci.c no_reset
  [=[ * input は main の初期値を書き換えて変える（0〜5，10，20，-1，21）。]=]
  [=[ * 書き換え版: stats を初期化し直さずに fib をもう一度呼ぶ版（「計測結果の読み方」2）。]=]
  [=[    Stats stats = {0, 0};              /* 測定ごとに {0, 0} から始める */]=]
  [=[    Stats stats = {0, 0};              /* 最初の 1 回だけ {0, 0} から始める（書き換え版） */]=]
  [=[    unsigned long long result = fib(n, 1, &stats);]=]
  [=[    unsigned long long result = fib(n, 1, &stats);
    result = fib(n, 1, &stats);        /* 書き換え版: stats を初期化し直さずに再び呼ぶ */]=])
