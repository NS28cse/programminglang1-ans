# 第14回 課題1 Factorial
# 本体に加えて，小問1「基底値を 0 にしたら」の版をビルドしてテストする
softprac_add_program(Factorial recursion.c)

# 基底条件で 0 を返す（すべての n で階乗が 0 になり，反復版とは一致しなくなる）。
# 引数なし（n=5）と，--n0（n=0），--n20（n=20）で試す
softprac_add_variant(Factorial recursion.c base_0 "if (n == 0) { return 1; }" "if (n == 0) { return 0; }")
