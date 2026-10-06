# 第8回 課題1 Swap
# 本体に加えて，例題の初期値を変える版（y を 5 にする／x と y の初期値だけを同じ 8 にする）をテストする
softprac_add_program(Swap pointers.c)

softprac_add_variant(Swap pointers.c y_5 "int x = 3, y = 8" "int x = 3, y = 5")
softprac_add_variant(Swap pointers.c both_8 "int x = 3, y = 8" "int x = 8, y = 8")
