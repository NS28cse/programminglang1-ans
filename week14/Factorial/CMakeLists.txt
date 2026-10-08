# 第14回 課題1 Factorial
# 本体（n = 5）に加えて，main の n を書き換えた版（検証表の値）と，
# 小問1「基底値を 0 にしたら」の版をビルドしてテストする
softprac_add_program(Factorial recursion.c)

# n を 0，1，3，10，20，21 に変える（21 は main の検査で終了する）
softprac_add_variant(Factorial recursion.c n_0 "unsigned int n = 5;" "unsigned int n = 0;")
softprac_add_variant(Factorial recursion.c n_1 "unsigned int n = 5;" "unsigned int n = 1;")
softprac_add_variant(Factorial recursion.c n_3 "unsigned int n = 5;" "unsigned int n = 3;")
softprac_add_variant(Factorial recursion.c n_10 "unsigned int n = 5;" "unsigned int n = 10;")   # 表外の参考値
softprac_add_variant(Factorial recursion.c n_20 "unsigned int n = 5;" "unsigned int n = 20;")
softprac_add_variant(Factorial recursion.c n_21 "unsigned int n = 5;" "unsigned int n = 21;")

# 小問1: 基底条件で 0 を返す（すべての n で階乗が 0 になり，反復版とは一致しなくなる）
softprac_add_variant(Factorial recursion.c base_0
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */")
softprac_add_variant(Factorial recursion.c base_0_n0
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */"
  "unsigned int n = 5;" "unsigned int n = 0;")
softprac_add_variant(Factorial recursion.c base_0_n1
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */"
  "unsigned int n = 5;" "unsigned int n = 1;")
softprac_add_variant(Factorial recursion.c base_0_n2
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */"
  "unsigned int n = 5;" "unsigned int n = 2;")
softprac_add_variant(Factorial recursion.c base_0_n3
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */"
  "unsigned int n = 5;" "unsigned int n = 3;")
softprac_add_variant(Factorial recursion.c base_0_n4
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */"
  "unsigned int n = 5;" "unsigned int n = 4;")
softprac_add_variant(Factorial recursion.c base_0_n20
  [=[ * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。]=]
  [=[ * 書き換え版（小問1）: 基底条件で 0 を返す誤りの版。最後に factorial(0) の 0 を掛けるので，どの n でも 0 になる。]=]
  "if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */"
  "if (n == 0) { return 0; }          /* 小問1: 基底値を 0 にした誤りの版 */"
  "unsigned int n = 5;" "unsigned int n = 20;")

# 確認用: factorial の呼び出し回数と最大深さ（n = 0，1，5，20）と，0〜20 で反復版と一致すること
softprac_add_variant(Factorial versions/factorial_count.c count)
