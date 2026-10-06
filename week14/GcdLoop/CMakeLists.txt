# 第14回 課題3 GcdLoop
# 本体に加えて，「余りを保存する前に a を b で上書きする」誤りの版をビルドしてテストする
softprac_add_program(GcdLoop gcd_loop.c)

# a = b を先に行ってから余りを求める（元の a を失い，常に b % b = 0 になる）
softprac_add_variant(GcdLoop gcd_loop.c overwrite_first
  "unsigned int remainder = a % b" "unsigned int remainder = (a = b, a % b)")
