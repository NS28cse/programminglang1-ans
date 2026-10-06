# 第8回 発展 Decompose
# 本体に加えて，演習ページのプログラムの入力 3.14 を検証表の値へ書き換えた版をテストする
softprac_add_program(Decompose decompose.c)

softprac_add_variant(Decompose decompose.c minus_3_14 "decompose(3.14," "decompose(-3.14,")
softprac_add_variant(Decompose decompose.c zero "decompose(3.14," "decompose(0.0,")
softprac_add_variant(Decompose decompose.c five "decompose(3.14," "decompose(5.0,")
