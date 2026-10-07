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

# 回数の確認: 条件判定（test）と本体（body）の回数を数えて最後に表示する版（3 つの版 × 表の limit）
# （確認用。判定のたびに数えるため，継続条件の前にコンマ演算子で ++test を入れている）
set(count_print [=[    printf("\n");
    printf("test=%d body=%d\n", test, body);]=])
foreach(limit 1 2 64 65 100)
  set(decl "int limit = ${limit};\n    int test = 0;\n    int body = 0;")
  softprac_add_variant(Powers powers.c count_for_limit_${limit}
    "int limit = 100;" "${decl}"
    "for (int power = 1; power < limit; power *= 2) {"
    "for (int power = 1; ++test, power < limit; power *= 2) {\n        ++body;"
    [=[    printf("\n");       // 改行はループの後で 1 回だけ]=] "${count_print}")
  softprac_add_variant(Powers versions/powers_while.c count_while_limit_${limit}
    "int limit = 100;" "${decl}"
    "while (power < limit) {" "while (++test, power < limit) {\n        ++body;"
    [=[    printf("\n");]=] "${count_print}")
  softprac_add_variant(Powers versions/powers_do_while.c count_do_while_limit_${limit}
    "int limit = 100;" "${decl}"
    "    do {" "    do {\n        ++body;"
    "} while (power < limit);" "} while (++test, power < limit);"
    [=[    printf("\n");]=] "${count_print}")
endforeach()
