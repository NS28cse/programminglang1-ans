# 第14回 課題4 CheckedFactorial
# 本体（n = 5）に加えて，main の n を書き換えた版（表の値）と，out に NULL を渡す版をビルドしてテストする
softprac_add_program(CheckedFactorial checked_factorial.c)

softprac_add_variant(CheckedFactorial checked_factorial.c n_0 "int n = 5;" "int n = 0;")
softprac_add_variant(CheckedFactorial checked_factorial.c n_1 "int n = 5;" "int n = 1;")
softprac_add_variant(CheckedFactorial checked_factorial.c n_20 "int n = 5;" "int n = 20;")
softprac_add_variant(CheckedFactorial checked_factorial.c n_minus1 "int n = 5;" "int n = -1;")
softprac_add_variant(CheckedFactorial checked_factorial.c n_21 "int n = 5;" "int n = 21;")

# out に NULL を渡す（n = 5 でも 0 を返し，result は 99 のまま）
softprac_add_variant(CheckedFactorial checked_factorial.c null_out
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，-1，21）。]=]
  [=[ * 書き換え版: out に NULL を渡す版（n = 5 でも ok=0 になり，result は 99 のまま）。]=]
  [=[    int ok = factorial_checked(n, &result);]=]
  [=[    int ok = factorial_checked(n, NULL);   /* 書き換え版: out に NULL を渡す */]=])
