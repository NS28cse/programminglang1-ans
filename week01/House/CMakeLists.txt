# 第1回 課題5 House
# 本体に加えて，表示する \ に対してソースで \ を 1 つしか書かなかった誤りの例をビルドしてテストする
# （1 行目は \\n になり改行されない，3 行目は \n だけになり \ が消える。どちらも警告は出ない）
softprac_add_program(House house.c)

softprac_add_variant(House house.c single_backslash
  [[printf("  /\\\n");]] [[printf("  /\\n");]]
  [[printf("/____\\\n");]] [[printf("/____\n");]])
