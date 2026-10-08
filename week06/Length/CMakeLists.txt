# 第6回 課題1 Length
# 本体に加えて，text を演習ページの {'a', 'b', 'c', '\0', 'd', 'e'} に変えた版（最初の終端で止まることの確認）をテストする
softprac_add_program(Length length.c)

softprac_add_variant(Length length.c mixed
                     [[char text[10] = "abc";]] [[char text[] = {'a', 'b', 'c', '\0', 'd', 'e'};]]
                     [[（Length / length.c）]]
                     [[（Length / length.c）。text を {'a', 'b', 'c', '\0', 'd', 'e'} に変えた版]])
