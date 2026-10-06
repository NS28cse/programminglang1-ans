# 第5回 発展 SumMean
# 本体に加えて，演習ページの {0}・n=1 と {100, 100, 100}・n=3，範囲の最大（100 が 5 個）の版をビルドしてテストする
softprac_add_program(SumMean summean.c)

softprac_add_variant(SumMean summean.c zero_n_1    "{72, 85, 60, 93, 80}" "{0}" "int n = COUNT;" "int n = 1;")
softprac_add_variant(SumMean summean.c hundred_n_3 "{72, 85, 60, 93, 80}" "{100, 100, 100}" "int n = COUNT;" "int n = 3;")
softprac_add_variant(SumMean summean.c full_100    "{72, 85, 60, 93, 80}" "{100, 100, 100, 100, 100}")
