# 第4回 課題2 EvenSum
# 本体（for 版，n = 10）に加えて，n を変えた版と，比較用の while 版・2 ずつ増やす版（versions/）を
# 演習ページの n（0, 1, 2, 10, 100）でビルドしてテストする。n = 4 は「値を追跡する」の表の確認
softprac_add_program(EvenSum even_sum.c)

foreach(n 0 1 2 4 100)
  softprac_add_variant(EvenSum even_sum.c for_n_${n} "n = 10" "n = ${n}")
endforeach()
softprac_add_variant(EvenSum versions/even_sum_while.c while_n_10)
softprac_add_variant(EvenSum versions/even_sum_step2.c step2_n_10)
foreach(n 0 1 2 100)
  softprac_add_variant(EvenSum versions/even_sum_while.c while_n_${n} "n = 10" "n = ${n}")
  softprac_add_variant(EvenSum versions/even_sum_step2.c step2_n_${n} "n = 10" "n = ${n}")
endforeach()

# 誤りの例: sum = 0 を本体の中へ移した版（最後の反復で加えた分しか残らない）
foreach(n 4 9 10)
  softprac_add_variant(EvenSum even_sum.c reset_in_body_n_${n}
    [=[        if (i % 2 == 0) {               // 偶数のときだけ加算する]=]
    [=[        sum = 0;
        if (i % 2 == 0) {]=]
    "n = 10" "n = ${n}")
endforeach()

# 誤りの例: while 版で更新 ++i を本体の先頭に置いた版（i = 2〜n + 1 を調べてしまう）
foreach(n 1 9 10)
  softprac_add_variant(EvenSum versions/even_sum_while.c early_increment_n_${n}
    [=[        if (i % 2 == 0) {
            sum += i;
        }
        ++i;                    // for の更新（本体の最後）
]=]
    [=[        ++i;
        if (i % 2 == 0) {
            sum += i;
        }
]=]
    "n = 10" "n = ${n}")
endforeach()
