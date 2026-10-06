# 第4回 課題4（Powers）: 本体（for 版）と，limit を変えた版・while 版・do-while 版・<= にした版をビルドしてテストする
softprac_add_program(Powers powers.c)

include("${CMAKE_CURRENT_SOURCE_DIR}/../_cmake/variants.cmake")
foreach(limit 1 2 64 65)
  week04_add_variant(for_limit_${limit} powers.c variants/limit_${limit} "limit = 100" "limit = ${limit}")
endforeach()
foreach(limit 1 2 64 65 100)
  week04_add_variant(while_limit_${limit} versions/powers_while.c variants/limit_${limit}
                     "limit = 100" "limit = ${limit}")
endforeach()
# do-while は limit = 1 のときだけ while と結果が違う
week04_add_variant(do_while_limit_1 versions/powers_do_while.c variants/do_while_limit_1 "limit = 100" "limit = 1")
foreach(limit 2 64 65 100)
  week04_add_variant(do_while_limit_${limit} versions/powers_do_while.c variants/limit_${limit}
                     "limit = 100" "limit = ${limit}")
endforeach()
# 継続条件の < を <= にすると，limit = 64 で 64 も表示される
week04_add_variant(le_limit_64 powers.c variants/le_limit_64 "power < limit" "power <= limit" "limit = 100" "limit = 64")
