# 第4回 課題4 Powers
# 本体（for 版，limit = 100）に加えて，演習ページの表の limit（1, 2, 64, 65, 100）に変えた版を，
# for 版・while 版・do-while 版（versions/）でビルドしてテストする。le_limit_64 は < を <= にした版。
# 各版は先頭コメントの 2 行目を版の説明に置き換える
softprac_add_program(Powers powers.c)

set(for_head "// 回数ではなく値で継続を決める．power は 1 から始めて 2 倍ずつ更新し，limit 未満の間だけ表示する．")
set(while_head "// for の初期化をループの前へ，更新を本体の最後へ移した．")
set(do_while_head "// 条件を本体の後で調べるため，limit が 1 でも本体を 1 回実行する．")

foreach(limit 1 2 64 65)
  softprac_add_variant(Powers powers.c for_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${for_head}" "// limit を ${limit} に書き換えた版．power は 1 から始めて 2 倍ずつ更新し，limit 未満の間だけ表示する．")
endforeach()
softprac_add_variant(Powers versions/powers_while.c while_limit_100)
softprac_add_variant(Powers versions/powers_do_while.c do_while_limit_100)
foreach(limit 1 2 64 65)
  softprac_add_variant(Powers versions/powers_while.c while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${while_head}" "// limit を ${limit} に書き換えた版．for の初期化をループの前へ，更新を本体の最後へ移した．")
  softprac_add_variant(Powers versions/powers_do_while.c do_while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${do_while_head}" "// limit を ${limit} に書き換えた版．条件を本体の後で調べるため，limit が 1 でも本体を 1 回実行する．")
endforeach()
softprac_add_variant(Powers powers.c le_limit_64
  "${for_head}" "// 継続条件の < を <= に変えた版（limit 以下の間表示するので，limit = 64 では 64 も表示する）．limit = 64．"
  "power < limit" "power <= limit" "limit = 100" "limit = 64")

# 回数の確認: 条件判定（test）と本体（body）の回数を数えて最後に表示する版（3 つの版 × 表の limit）
# （確認用。判定のたびに数えるため，継続条件の前にコンマ演算子で ++test を入れている）
set(count_decl [=[    int test = 0;       // 条件判定の回数
    int body = 0;       // 本体の回数
]=])
set(count_print [=[    printf("test=%d body=%d\n", test, body);]=])
set(for_newline [=[    printf("\n");       // 改行はループの後で 1 回だけ]=])
set(newline [=[    printf("\n");]=])
foreach(limit 1 2 64 65 100)
  set(head "の条件判定（test）と本体（body）の回数を数えて最後に表示する版（確認用）．limit = ${limit}．")
  softprac_add_variant(Powers powers.c count_for_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${for_head}" "// for 版${head}"
    "    for (int power = 1; power < limit; power *= 2) {\n"
    "${count_decl}    for (int power = 1; ++test, power < limit; power *= 2) {\n        ++body;\n"
    "${for_newline}" "${for_newline}\n${count_print}")
  softprac_add_variant(Powers versions/powers_while.c count_while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${while_head}" "// while 版${head}"
    "    while (power < limit) {\n"
    "${count_decl}    while (++test, power < limit) {\n        ++body;\n"
    "${newline}" "${newline}\n${count_print}")
  softprac_add_variant(Powers versions/powers_do_while.c count_do_while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${do_while_head}" "// do-while 版${head}"
    "    do {\n" "${count_decl}    do {\n        ++body;\n"
    "} while (power < limit);" "} while (++test, power < limit);"
    "${newline}" "${newline}\n${count_print}")
endforeach()
