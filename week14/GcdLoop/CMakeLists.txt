# 第14回 課題3 GcdLoop
# 本体（48, 18）に加えて，main の a と b を書き換えた版（演習ページの表の組と (0, 0)）と，
# 「余りを保存する前に a を b で上書きする」誤りの版をビルドしてテストする
softprac_add_program(GcdLoop gcd_loop.c)

softprac_add_variant(GcdLoop gcd_loop.c a18_b48
  "unsigned int a = 48;" "unsigned int a = 18;" "unsigned int b = 18;" "unsigned int b = 48;")
softprac_add_variant(GcdLoop gcd_loop.c a7_b0
  "unsigned int a = 48;" "unsigned int a = 7;" "unsigned int b = 18;" "unsigned int b = 0;")
softprac_add_variant(GcdLoop gcd_loop.c a0_b7
  "unsigned int a = 48;" "unsigned int a = 0;" "unsigned int b = 18;" "unsigned int b = 7;")
softprac_add_variant(GcdLoop gcd_loop.c a7_b7
  "unsigned int a = 48;" "unsigned int a = 7;" "unsigned int b = 18;" "unsigned int b = 7;")
softprac_add_variant(GcdLoop gcd_loop.c a13_b8
  "unsigned int a = 48;" "unsigned int a = 13;" "unsigned int b = 18;" "unsigned int b = 8;")
softprac_add_variant(GcdLoop gcd_loop.c a100_b25
  "unsigned int a = 48;" "unsigned int a = 100;" "unsigned int b = 18;" "unsigned int b = 25;")
# (0, 0) は main で拒否する
softprac_add_variant(GcdLoop gcd_loop.c a0_b0
  "unsigned int a = 48;" "unsigned int a = 0;" "unsigned int b = 18;" "unsigned int b = 0;")

# (48, 18) について，各ループで計算した remainder と，そのときの a・b を表示する
softprac_add_variant(GcdLoop gcd_loop.c trace_48_18
  [=[ * a と b は main の初期値を書き換えて変える（演習ページの表の 7 組と (0, 0)）。]=]
  [=[ * gcd_loop の各ループで a・b・remainder を表示する版（「更新順序を追う」）。]=]
  [=[        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */
]=]
  [=[        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */
        printf("loop: a=%u b=%u remainder=%u\n", a, b, remainder); /* 各ループの値を表示する */
]=])

# a = b を先に行ってから余りを求める誤りの版（元の a を失い，常に b % b = 0 になる）。
# (48, 18)，(13, 8)，(7, 0) で試す（(7, 0) はループに入らないので偶然正しい）
softprac_add_variant(GcdLoop gcd_loop.c overwrite_first
  [=[ * a と b は main の初期値を書き換えて変える（演習ページの表の 7 組と (0, 0)）。]=]
  [=[ * gcd_loop の更新順序を誤った版（余りを保存する前に a を上書きする）。]=]
  "/* 反復版。再帰の引数 (a, b) の変化を，状態変数 a と b の更新で表す */"
  "/* 誤った反復版: 余りを保存する前に a を上書きする */"
  [=[        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */
        a = b;
        b = remainder;]=]
  [=[        a = b;          /* 誤り: 余りを保存する前に a を上書き */
        b = a % b;]=])
softprac_add_variant(GcdLoop gcd_loop.c overwrite_first_a13_b8
  [=[ * a と b は main の初期値を書き換えて変える（演習ページの表の 7 組と (0, 0)）。]=]
  [=[ * gcd_loop の更新順序を誤った版（余りを保存する前に a を上書きする）。]=]
  "/* 反復版。再帰の引数 (a, b) の変化を，状態変数 a と b の更新で表す */"
  "/* 誤った反復版: 余りを保存する前に a を上書きする */"
  [=[        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */
        a = b;
        b = remainder;]=]
  [=[        a = b;          /* 誤り: 余りを保存する前に a を上書き */
        b = a % b;]=]
  "unsigned int a = 48;" "unsigned int a = 13;" "unsigned int b = 18;" "unsigned int b = 8;")
softprac_add_variant(GcdLoop gcd_loop.c overwrite_first_a7_b0
  [=[ * a と b は main の初期値を書き換えて変える（演習ページの表の 7 組と (0, 0)）。]=]
  [=[ * gcd_loop の更新順序を誤った版（余りを保存する前に a を上書きする）。]=]
  "/* 反復版。再帰の引数 (a, b) の変化を，状態変数 a と b の更新で表す */"
  "/* 誤った反復版: 余りを保存する前に a を上書きする */"
  [=[        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */
        a = b;
        b = remainder;]=]
  [=[        a = b;          /* 誤り: 余りを保存する前に a を上書き */
        b = a % b;]=]
  "unsigned int a = 48;" "unsigned int a = 7;" "unsigned int b = 18;" "unsigned int b = 0;")
