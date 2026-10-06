# 第14回 課題2 Trace
# 本体に加えて，「出力位置を変える」の 2 つの版をビルドしてテストする
softprac_add_program(Trace trace.c)

# (1) enter の表示だけを n==0 の判定の後へ移す（sum_to(0) では enter が出ない）。
#     引数なし（n=3）と，--n0（n=0。leave 0: 0 と sum=0 だけになる）で試す
softprac_add_variant(Trace trace.c enter_after_check
  "    printf(\"enter %d\\n\", n);           /* 呼び出し時: 再帰より前なので 3,2,1,0 の順 */\n" ""
  "    int result = n + sum_to(n - 1);"
  "    printf(\"enter %d\\n\", n);\n    int result = n + sum_to(n - 1);")
# (2) leave の表示を再帰呼び出しより前へ移し，未完成の result ではなく n だけを表示する
softprac_add_variant(Trace trace.c leave_before_call
  "    int result = n + sum_to(n - 1);"
  "    printf(\"leave %d\\n\", n);\n    int result = n + sum_to(n - 1);"
  "    printf(\"leave %d: %d\\n\", n, result); /* 復帰時: 0,1,2,3 の順 */\n" "")
