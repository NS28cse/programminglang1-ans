# 第4回 課題4 Powers: 本体（for 版，limit = 100）と while 版・do-while 版（versions/）を，演習ページの表の limit（1, 2, 64, 65, 100）で。
# le_limit_64 は < を <= にした版。回数を数える版も。各版は先頭コメントの 2 行目を版の説明にする
softprac_add_program(Powers powers.c)

set(for_head "// 回数ではなく値で継続を決める．power は 1 から始めて 2 倍ずつ更新し，limit 未満の間だけ表示する．")
set(while_head "// for の初期化をループの前に，更新を本体の最後に置く．")
set(do_while_head "// 条件を本体の後で調べるため，limit が 1 でも本体を 1 回実行する．")

# limit_value(<変数> <limit>): 本体（powers.c）の "limit = 100;" を置き換える文字列。同じ長さになるように ; の後に空白を補い，
# 行末のコメントの桁を本体とそろえる（versions/ の limit には行末のコメントがないので，そちらは "limit = ${limit}" のまま置き換える）
function(limit_value out limit)
  set(text "limit = ${limit};")
  string(LENGTH "${text}" len)
  math(EXPR npad "12 - ${len}")
  set(pad "")
  if(npad GREATER 0)
    string(REPEAT " " ${npad} pad)
  endif()
  set(${out} "${text}${pad}" PARENT_SCOPE)
endfunction()

foreach(limit 1 2 64 65)
  limit_value(limit_new ${limit})
  softprac_add_variant(Powers powers.c for_limit_${limit}
    "limit = 100;" "${limit_new}"
    "${for_head}" "// limit を ${limit} に書き換えた版．power は 1 から始めて 2 倍ずつ更新し，limit 未満の間だけ表示する．")
endforeach()
softprac_add_variant(Powers versions/powers_while.c while_limit_100)
softprac_add_variant(Powers versions/powers_do_while.c do_while_limit_100)
foreach(limit 1 2 64 65)
  softprac_add_variant(Powers versions/powers_while.c while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${while_head}" "// limit を ${limit} に書き換えた版．for の初期化をループの前に，更新を本体の最後に置く．")
  softprac_add_variant(Powers versions/powers_do_while.c do_while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${do_while_head}" "// limit を ${limit} に書き換えた版．条件を本体の後で調べるため，limit が 1 でも本体を 1 回実行する．")
endforeach()
limit_value(limit_new 64)
softprac_add_variant(Powers powers.c le_limit_64
  "${for_head}" "// 継続条件の < を <= に変えた版（limit 以下の間表示するので，limit = 64 では 64 も表示する）．limit = 64．"
  "power < limit" "power <= limit" "limit = 100;" "${limit_new}")

# 回数の確認: 条件判定（test）と本体（body）の回数を数えて最後に表示する版（3 つの版 × 表の limit）
# （確認用。for・while 版はループの前で最初の条件判定の 1 回分を，本体の最後で次の判定の分を ++test で数える。
#   do-while 版は判定が本体の後にしかないので，本体の最後だけで数える。どの版も本体に continue がないので，判定の回数と一致する）
set(count_decl [=[    int test = 0;       // 条件判定の回数
    int body = 0;       // 本体の回数
]=])
set(count_print [=[    printf("test=%d body=%d\n", test, body);]=])
set(for_newline [=[    printf("\n");       // 改行はループの後で 1 回だけ]=])
set(newline [=[    printf("\n");]=])
set(body_end_test [=[        ++test;         // 本体の後の条件判定の分
]=])
foreach(limit 1 2 64 65 100)
  set(head "の条件判定（test）と本体（body）の回数を数えて最後に表示する版（確認用）．limit = ${limit}．")
  limit_value(limit_new ${limit})
  softprac_add_variant(Powers powers.c count_for_limit_${limit}
    "limit = 100;" "${limit_new}"
    "${for_head}" "// for 版${head}"
    "    for (int power = 1; power < limit; power *= 2) {\n"
    "${count_decl}    ++test;             // 最初の条件判定の分\n    for (int power = 1; power < limit; power *= 2) {\n        ++body;\n"
    [=[        printf("%d, ", power);
]=] [=[        printf("%d, ", power);
        ++test;         // 本体の後（更新の後）の条件判定の分
]=]
    "${for_newline}" "${for_newline}\n${count_print}")
  softprac_add_variant(Powers versions/powers_while.c count_while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${while_head}" "// while 版${head}"
    "    while (power < limit) {\n"
    "${count_decl}    ++test;             // 最初の条件判定の分\n    while (power < limit) {\n        ++body;\n"
    "        power *= 2;\n" "        power *= 2;\n${body_end_test}"
    "${newline}" "${newline}\n${count_print}")
  softprac_add_variant(Powers versions/powers_do_while.c count_do_while_limit_${limit}
    "limit = 100" "limit = ${limit}"
    "${do_while_head}" "// do-while 版${head}"
    "    do {\n" "${count_decl}    do {\n        ++body;\n"
    "        power *= 2;\n" "        power *= 2;\n${body_end_test}"
    "${newline}" "${newline}\n${count_print}")
endforeach()
