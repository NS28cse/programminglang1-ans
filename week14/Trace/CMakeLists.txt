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
  "    printf(\"enter %d\\n\", n);           /* 呼び出し時: 再帰より前なので 3,2,1,0 の順 */\n" ""
  "    int result = n + sum_to(n - 1);"
  "    printf(\"enter %d\\n\", n);\n    int result = n + sum_to(n - 1);")
softprac_add_variant(Trace trace.c enter_after_check_n0
  "    printf(\"enter %d\\n\", n);           /* 呼び出し時: 再帰より前なので 3,2,1,0 の順 */\n" ""
  "    int result = n + sum_to(n - 1);"
  "    printf(\"enter %d\\n\", n);\n    int result = n + sum_to(n - 1);"
  "int n = 3;" "int n = 0;")
# (2) leave の表示を再帰呼び出しより前へ移し，未完成の result ではなく n だけを表示する
softprac_add_variant(Trace trace.c leave_before_call
  "    int result = n + sum_to(n - 1);"
  "    printf(\"leave %d\\n\", n);\n    int result = n + sum_to(n - 1);"
  "    printf(\"leave %d: %d\\n\", n, result); /* 復帰時: 0,1,2,3 の順 */\n" "")
