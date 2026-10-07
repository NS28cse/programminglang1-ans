# 第4回 課題4 Powers
# 本体（for 版，limit = 100）に加えて，演習ページの表の limit（1, 2, 64, 65, 100）に変えた版を，
# for 版・while 版・do-while 版（versions/）でビルドしてテストする。le_limit_64 は < を <= にした版
softprac_add_program(Powers powers.c)

foreach(limit 1 2 64 65)
  softprac_add_variant(Powers powers.c for_limit_${limit} "limit = 100" "limit = ${limit}")
endforeach()
softprac_add_variant(Powers versions/powers_while.c while_limit_100)
softprac_add_variant(Powers versions/powers_do_while.c do_while_limit_100)
foreach(limit 1 2 64 65)
  softprac_add_variant(Powers versions/powers_while.c while_limit_${limit} "limit = 100" "limit = ${limit}")
  softprac_add_variant(Powers versions/powers_do_while.c do_while_limit_${limit} "limit = 100" "limit = ${limit}")
endforeach()
softprac_add_variant(Powers powers.c le_limit_64 "power < limit" "power <= limit" "limit = 100" "limit = 64")
