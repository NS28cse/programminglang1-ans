# 第4回 課題2 EvenSum
# 本体（for 版，n = 10）に加えて，n を変えた版と，比較用の while 版・2 ずつ増やす版（versions/）を
# 演習ページの n（0, 1, 2, 10, 100）でビルドしてテストする。n = 4 は「値を追跡する」の表の確認
# （n = 10 の版は "n = 10" を同じ文字列に置き換えて，そのままビルドしている）
softprac_add_program(EvenSum even_sum.c)

foreach(n 0 1 2 4 100)
  softprac_add_variant(EvenSum even_sum.c for_n_${n} "n = 10" "n = ${n}")
endforeach()
foreach(n 0 1 2 10 100)
  softprac_add_variant(EvenSum versions/even_sum_while.c while_n_${n} "n = 10" "n = ${n}")
  softprac_add_variant(EvenSum versions/even_sum_step2.c step2_n_${n} "n = 10" "n = ${n}")
endforeach()
