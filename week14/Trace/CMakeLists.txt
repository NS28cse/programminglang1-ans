# 第14回 課題2 Trace
# 本体（n = 3）に加えて，main の n を書き換えた版と，「出力位置を変える」の版をビルドしてテストする
softprac_add_program(Trace trace.c)

# n を 0，1，2，100，-1，101 に変える（-1 と 101 は main で拒否され，enter が出ない）
softprac_add_variant(Trace trace.c n_0 "int n = 3;" "int n = 0;")
softprac_add_variant(Trace trace.c n_1 "int n = 3;" "int n = 1;")
softprac_add_variant(Trace trace.c n_2 "int n = 3;" "int n = 2;")
softprac_add_variant(Trace trace.c n_100 "int n = 3;" "int n = 100;")
softprac_add_variant(Trace trace.c n_minus1 "int n = 3;" "int n = -1;")
softprac_add_variant(Trace trace.c n_101 "int n = 3;" "int n = 101;")

# (1) enter の表示だけを n==0 の判定の後へ移す（sum_to(0) では enter が出ない）。n = 3 と n = 0 で試す
softprac_add_variant(Trace trace.c enter_after_check
  [=[ * 講義の trace.c。n は main の初期値を書き換えて変える（0，1，2，3，100，-1，101）。]=]
  [=[ * 書き換え版: 講義の trace.c の enter の表示を n==0 の判定の後へ移した版（「出力位置を変える」）。]=]
  [=[    printf("enter %d\n", n);           /* 呼び出し時: 再帰より前なので 3,2,1,0 の順 */
]=]
  ""
  [=[    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */]=]
  [=[    printf("enter %d\n", n);           /* 書き換え版: enter を n==0 の判定の後へ移した（sum_to(0) では出ない） */
    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */]=])
softprac_add_variant(Trace trace.c enter_after_check_n0
  [=[ * 講義の trace.c。n は main の初期値を書き換えて変える（0，1，2，3，100，-1，101）。]=]
  [=[ * 書き換え版: 講義の trace.c の enter の表示を n==0 の判定の後へ移した版（「出力位置を変える」）。]=]
  [=[    printf("enter %d\n", n);           /* 呼び出し時: 再帰より前なので 3,2,1,0 の順 */
]=]
  ""
  [=[    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */]=]
  [=[    printf("enter %d\n", n);           /* 書き換え版: enter を n==0 の判定の後へ移した（sum_to(0) では出ない） */
    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */]=]
  "int n = 3;" "int n = 0;")
# (2) leave の表示を再帰呼び出しより前へ移し，未完成の result ではなく n だけを表示する
softprac_add_variant(Trace trace.c leave_before_call
  [=[ * 講義の trace.c。n は main の初期値を書き換えて変える（0，1，2，3，100，-1，101）。]=]
  [=[ * 書き換え版: leave の表示を再帰呼び出しより前へ移し，n だけを表示する版（「出力位置を変える」）。]=]
  [=[    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */]=]
  [=[    printf("leave %d\n", n);           /* 書き換え版: 再帰より前へ移したので n だけ表示する */
    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */]=]
  [=[    printf("leave %d: %d\n", n, result); /* 復帰時: 0,1,2,3 の順 */
]=] "")
