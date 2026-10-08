# 第4回 課題2 EvenSum
# 本体（for 版，n = 10）に加えて，n を変えた版と，比較用の while 版・2 ずつ増やす版（versions/）を
# 演習ページの n（0, 1, 2, 10, 100）でビルドしてテストする。n = 4 は「値を追跡する」の表の確認。
# 各版は先頭コメントの 2 行目を版の説明に置き換える。確認問題3 の for（versions/three_times.c）もここでテストする
softprac_add_program(EvenSum even_sum.c)

set(for_head "// 1 から n までの偶数の合計を for 文で求める．n は 0〜100 の固定値．")
set(while_head "// for の初期化をループの前へ，更新を本体の最後へ移した．")
set(step2_head "// i は偶数だけを通るので，偶奇判定の if は不要．本体の回数は約半分になる．")

# n_value(<変数> <n>): 本体（even_sum.c）の "n = 10; "（; の後の空白 1 つまで）を置き換える文字列。
# 同じ長さになるように ; の後に空白を補い，行末のコメントの桁を本体とそろえる
# （versions/ の n には行末のコメントがないので，そちらは "n = ${n}" のまま置き換える）
function(n_value out n)
  set(text "n = ${n};")
  string(LENGTH "${text}" len)
  math(EXPR npad "8 - ${len}")
  set(pad "")
  if(npad GREATER 0)
    string(REPEAT " " ${npad} pad)
  endif()
  set(${out} "${text}${pad}" PARENT_SCOPE)
endfunction()

foreach(n 0 1 2 4 100)
  n_value(n_new ${n})
  softprac_add_variant(EvenSum even_sum.c for_n_${n}
    "n = 10; " "${n_new}"
    "${for_head}" "// n を ${n} に書き換えた版．1 から n までの偶数の合計を for 文で求める．")
endforeach()
softprac_add_variant(EvenSum versions/even_sum_while.c while_n_10)
softprac_add_variant(EvenSum versions/even_sum_step2.c step2_n_10)
foreach(n 0 1 2 100)
  softprac_add_variant(EvenSum versions/even_sum_while.c while_n_${n}
    "n = 10" "n = ${n}"
    "${while_head}" "// n を ${n} に書き換えた版．for の初期化をループの前へ，更新を本体の最後へ移した．")
  softprac_add_variant(EvenSum versions/even_sum_step2.c step2_n_${n}
    "n = 10" "n = ${n}"
    "${step2_head}" "// n を ${n} に書き換えた版．i は偶数だけを通るので，偶奇判定の if は不要．")
endforeach()

# 誤りの例: 本体の先頭で毎回 sum = 0 に戻す版（最後の反復で加えた分しか残らない）
foreach(n 4 9 10)
  n_value(n_new ${n})
  softprac_add_variant(EvenSum even_sum.c reset_in_body_n_${n}
    "n = 10; " "${n_new}"
    "${for_head}" "// 誤りの例: 本体の先頭で毎回 sum = 0 に戻す版（累積にならず，最後の反復で加えた分しか残らない）．n = ${n}．"
    "    int sum = 0;    // それまでの合計．ループの前で 1 回だけ 0 にする"
    "    int sum = 0;    // それまでの合計（ループの前でも 0 にするが，本体でも毎回 0 に戻してしまう）"
    [=[        if (i % 2 == 0) {               // 偶数のときだけ加算する]=]
    [=[        sum = 0;                        // 誤り: 毎回 0 に戻すので累積にならない
        if (i % 2 == 0) {               // 偶数のときだけ加算する]=])
endforeach()

# 誤りの例: 継続条件を i < n にした版（n が偶数のとき最後の n を加えない）
foreach(n 2 10)
  n_value(n_new ${n})
  softprac_add_variant(EvenSum even_sum.c lt_n_${n}
    "n = 10; " "${n_new}"
    "${for_head}" "// 誤りの例: 継続条件を i < n にした版（n が偶数のとき最後の n を加えない）．n = ${n}．"
    "    for (int i = 1; i <= n; ++i) {      // i は今調べている数"
    "    for (int i = 1; i < n; ++i) {       // 誤り: n そのものを調べない")
endforeach()

# 誤りの例: while 版で更新 ++i を本体の先頭に置いた版（i = 2〜n + 1 を調べてしまう）
foreach(n 1 9 10)
  softprac_add_variant(EvenSum versions/even_sum_while.c early_increment_n_${n}
    "n = 10" "n = ${n}"
    "${while_head}" "// 誤りの例: while 版の更新 ++i を本体の先頭に置いた版（i = 2〜n + 1 を調べてしまう）．n = ${n}．"
    [=[        if (i % 2 == 0) {
            sum += i;
        }
        ++i;                    // for の更新（本体の最後）
]=]
    [=[        ++i;                    // 誤り: 更新を本体の先頭に置いた（1 を調べず n + 1 まで調べる）
        if (i % 2 == 0) {
            sum += i;
        }
]=])
endforeach()

# while 版のループの後で i も表示する版（for と違い i はループの後でも使え，値は n + 1）
foreach(n 0 10)
  softprac_add_variant(EvenSum versions/even_sum_while.c while_i_after_n_${n}
    "n = 10" "n = ${n}"
    "${while_head}" "// while 版のループの後で i の値も表示する版（確認用．i はループの後でも使え，値は n + 1）．n = ${n}．"
    [=[    printf("%d\n", sum);]=]
    [=[    printf("%d\n", sum);
    printf("i=%d\n", i);        // ループを抜けたときの i（条件 i <= n が偽になった値）]=])
endforeach()

# 回数の確認: 条件判定（test）・本体（body）・加算（add）の回数を数えて合計の後に表示する版
# （確認用。条件判定は，ループの前で最初の 1 回分を，本体の最後で次の判定の分を ++test で数える。
#   本体に continue がないので，本体の最後まで来るたびに次の判定が 1 回行われ，判定の回数と一致する）
set(count_decl [=[    int test = 0;   // 条件判定の回数
    int body = 0;   // 本体の回数
    int add = 0;    // 加算の回数
]=])
set(count_print [=[    printf("%d\n", sum);
    printf("test=%d body=%d add=%d\n", test, body, add);]=])
foreach(n 0 1 2 4 10 100)
  n_value(n_new ${n})
  softprac_add_variant(EvenSum even_sum.c count_n_${n}
    "n = 10; " "${n_new}"
    "${for_head}" "// 条件判定（test）・本体（body）・加算（add）の回数を数えて合計の後に表示する版（確認用）．n = ${n}．"
    "    for (int i = 1; i <= n; ++i) {      // i は今調べている数\n"
    "${count_decl}    ++test;                             // 最初の条件判定の分\n    for (int i = 1; i <= n; ++i) {      // i は今調べている数\n        ++body;\n"
    "            sum += i;\n        }\n"
    "            sum += i;\n            ++add;\n        }\n        ++test;                         // 本体の後（更新の後）の条件判定の分\n"
    [=[    printf("%d\n", sum);]=] "${count_print}")
  softprac_add_variant(EvenSum versions/even_sum_step2.c count_step2_n_${n}
    "n = 10" "n = ${n}"
    "${step2_head}" "// 2 ずつ増やす版に，条件判定（test）・本体（body）・加算（add）の回数を数えて合計の後に表示する処理を足した版（確認用）．n = ${n}．"
    "    for (int i = 2; i <= n; i += 2) {\n"
    "${count_decl}    ++test;         // 最初の条件判定の分\n    for (int i = 2; i <= n; i += 2) {\n        ++body;\n"
    "        sum += i;\n"
    "        sum += i;\n        ++add;\n        ++test;     // 本体の後（更新の後）の条件判定の分\n"
    [=[    printf("%d\n", sum);]=] "${count_print}")
endforeach()

# 確認問題3: 演習ページの for (int i = 0; i < 3; ++i) そのもの（本体で i を表示する）と，
# 条件判定（test）と本体（body）の回数を数えて最後に表示する版（test=4 body=3）
softprac_add_variant(EvenSum versions/three_times.c three_times)
softprac_add_variant(EvenSum versions/three_times.c count_three_times
  "// 演習ページの for をそのまま実行し，本体で i を表示する．"
  "// 条件判定（test）と本体（body）の回数を数えて最後に表示する版（確認用）．"
  "    for (int i = 0; i < 3; ++i) {\n"
  "    int test = 0;   // 条件判定の回数\n    int body = 0;   // 本体の回数\n    ++test;         // 最初の条件判定の分\n    for (int i = 0; i < 3; ++i) {\n        ++body;\n"
  [=[        printf("%d\n", i);
]=]
  [=[        printf("%d\n", i);
        ++test;     // 本体の後（更新の後）の条件判定の分
]=]
  "    return 0;" "    printf(\"test=%d body=%d\\n\", test, body);\n    return 0;")
