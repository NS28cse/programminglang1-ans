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

# a = b を先に行ってから余りを求める（元の a を失い，常に b % b = 0 になる）
softprac_add_variant(GcdLoop gcd_loop.c overwrite_first
  "        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */\n        a = b;\n        b = remainder;"
  "        a = b;          /* 誤り: 余りを保存する前に a を上書き */\n        b = a % b;")
