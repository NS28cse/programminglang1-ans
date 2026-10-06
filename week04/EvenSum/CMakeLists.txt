# 第4回 課題2（EvenSum）: 本体（for 版）と，n を変えた版・while 版・2 ずつ増やす版をビルドしてテストする
softprac_add_program(EvenSum even_sum.c)

include("${CMAKE_CURRENT_SOURCE_DIR}/../_cmake/variants.cmake")
foreach(n 0 1 2 4 100)
  week04_add_variant(for_n_${n} even_sum.c variants/n_${n} "n = 10" "n = ${n}")
endforeach()
foreach(n 0 1 2 10 100)
  week04_add_variant(while_n_${n} versions/even_sum_while.c variants/n_${n} "n = 10" "n = ${n}")
  week04_add_variant(step2_n_${n} versions/even_sum_step2.c variants/n_${n} "n = 10" "n = ${n}")
endforeach()
