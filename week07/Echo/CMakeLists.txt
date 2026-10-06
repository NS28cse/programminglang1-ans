# 第7回 課題1 Echo
# 本体（講義の echo.c）に加えて，演習ページの 2 つの書き換えをした版をテストする
#   slash  : putchar(ch) の前に putchar('/') とその戻り値の確認を加えた版
#   visible: putchar とその失敗処理を，改行を見える形で表示する printf に置き換えた版
# 期待値は variants/tests/<版>--<入力の名前>.*
softprac_add_program(Echo echo.c)

softprac_add_variant(Echo echo.c slash
  [=[        if (putchar(ch) == EOF) {]=]
  [=[        if (putchar('/') == EOF) {
            fprintf(stderr, "output error\n");
            return 1;
        }
        if (putchar(ch) == EOF) {]=])

softprac_add_variant(Echo echo.c visible
  [=[        if (putchar(ch) == EOF) {
            fprintf(stderr, "output error\n");
            return 1;
        }]=]
  [=[        if (ch == '\n') {
            printf("new line\n");
        } else {
            printf("character=%c\n", ch);
        }]=])
