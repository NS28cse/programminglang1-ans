# 第1回 課題1 Welcome
# 本体（printf を 2 回使う）に加えて，printf 1 回で 2 行を表示する版をビルドしてテストする（出力は同じ）
softprac_add_program(Welcome welcome.c)

softprac_add_variant(Welcome welcome.c one_printf
  [[printf("Welcome to Programming Languages 1.\n");
    printf("I can build and run a C program.\n");]]
  [[printf("Welcome to Programming Languages 1.\nI can build and run a C program.\n");]])
