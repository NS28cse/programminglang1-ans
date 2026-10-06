# 第14回 課題2 Trace
# 本体に加えて，「出力位置を変える」の 2 つの版をビルドしてテストする。
# 置換の文字列に ; を書けないので，文を移す代わりにコンマ演算子で同じ位置・同じ順序の表示にしている
# （README に学生が書く形のコードを載せている）
softprac_add_program(Trace trace.c)

# (1) enter の表示を n==0 の判定の後へ移す（sum_to(0) では enter が出ない）
softprac_add_variant(Trace trace.c enter_after_check
  "printf(\"enter %d\\n\", n)" "(void)0"
  "int result = n + sum_to(n - 1)" "int result = (printf(\"enter %d\\n\", n), n + sum_to(n - 1))")
# (2) leave の表示を再帰呼び出しより前へ移し，n だけを表示する
softprac_add_variant(Trace trace.c leave_before_call
  "int result = n + sum_to(n - 1)" "int result = (printf(\"leave %d\\n\", n), n + sum_to(n - 1))"
  "printf(\"leave %d: %d\\n\", n, result)" "(void)0")
# (1) の版を n=0 で実行する（leave 0: 0 と sum=0 だけになる）
softprac_add_variant(Trace trace.c enter_after_check_0
  "printf(\"enter %d\\n\", n)" "(void)0"
  "int result = n + sum_to(n - 1)" "int result = (printf(\"enter %d\\n\", n), n + sum_to(n - 1))"
  "long input = 3" "long input = 0")
