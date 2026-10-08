# 第1回 課題1 Welcome
# 本体（printf を 2 回使う）に加えて，次の 2 つの版をビルドしてテストする
# （各版は先頭コメントの 2 行目も版の説明に置き換える）
# - one_printf: printf 1 回で 2 行を表示する版（出力は本体と同じ）
# - missing_newline: 1 行目の末尾の \n を忘れた誤りの例（2 行が 1 行につながる。警告は出ない）
softprac_add_program(Welcome welcome.c)

softprac_add_variant(Welcome welcome.c one_printf
  [=[// 2 行を表示する。行の区切りは文字列中の \n で表す。]=]
  [=[// printf 1 回で 2 行を表示する版（出力は本体と同じ）。行の区切りは文字列中の \n で表す。]=]
  [=[    printf("Welcome to Programming Languages 1.\n");
    printf("I can build and run a C program.\n");]=]
  [=[    printf("Welcome to Programming Languages 1.\nI can build and run a C program.\n");]=])

softprac_add_variant(Welcome welcome.c missing_newline
  [=[// 2 行を表示する。行の区切りは文字列中の \n で表す。]=]
  [=[// 誤りの例: 1 行目の末尾の \n を忘れた版（2 行が 1 行につながる。ビルドは成功し，警告も出ない）。]=]
  [=[    printf("Welcome to Programming Languages 1.\n");]=]
  [=[    printf("Welcome to Programming Languages 1.");      // 誤り: 末尾の \n を忘れた]=])
