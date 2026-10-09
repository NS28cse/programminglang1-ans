# 第4回 発展 YearGroup: 本体（switch 版，school_year = 1）と if・else if・else 版（versions/）を school_year = 0〜5 で。
# 最初の break を外した版，発展「途中で飛ばす処理」の断片（versions/skip.c），確認問題7・8 の確認用のコード（versions/）も。
# 各版は先頭コメントの 2 行目を版の説明にする
softprac_add_program(YearGroup year_group.c)

set(switch_head "// school_year が 1 か 2 なら lower years，3 か 4 なら upper years，それ以外なら invalid を表示する．")
set(if_head "// switch 版と同じ区分を == と || の条件で書き，if・else if・else で 1 つだけ選ぶ．")

foreach(year 0 2 3 4 5)
  softprac_add_variant(YearGroup year_group.c switch_year_${year}
    "school_year = 1" "school_year = ${year}"
    "${switch_head}" "// school_year を ${year} に書き換えた版．1 か 2 なら lower years，3 か 4 なら upper years，それ以外なら invalid を表示する．")
endforeach()
softprac_add_variant(YearGroup versions/year_group_if.c if_year_1)
foreach(year 0 2 3 4 5)
  softprac_add_variant(YearGroup versions/year_group_if.c if_year_${year}
    "school_year = 1" "school_year = ${year}"
    "${if_head}" "// school_year を ${year} に書き換えた版．switch 版と同じ区分を == と || の条件で書き，if・else if・else で 1 つだけ選ぶ．")
endforeach()

# 最初の break を外した版（誤りの例。1・2 では lower years の後に upper years も表示する。0, 3, 4, 5 は元と同じ）
set(break_old [=[        printf("lower years\n");
        break;              // これがないと次の case の文へ続けて実行する（フォールスルー）
]=])
set(break_new [=[        printf("lower years\n");    // break を外したので，次の case の文へ続けて実行する（フォールスルー）
]=])
foreach(year 0 1 2 3 4 5)
  # school_year = 1 の版は値を置き換えない（置換前と置換後が同じ）
  softprac_add_variant(YearGroup year_group.c no_first_break_year_${year}
    "school_year = 1" "school_year = ${year}"
    "${switch_head}" "// 最初の break を外した版（誤りの例。1・2 では lower years の後に upper years も表示する）．school_year = ${year}．"
    "${break_old}" "${break_new}")
  # わざと break を外した版なので，GCC の -Wimplicit-fallthrough（-Wextra に含まれる）だけを止める
  target_compile_options(YearGroup_no_first_break_year_${year} PRIVATE $<$<C_COMPILER_ID:GNU>:-Wno-implicit-fallthrough>)
endforeach()

# 発展「途中で飛ばす処理」: 演習ページの断片（0，1，3）と，i == 4 の break を continue に変えた版（0，1，3，5）
softprac_add_variant(YearGroup versions/skip.c skip_break)
softprac_add_variant(YearGroup versions/skip.c skip_continue
  "// i == 2 では continue で printf を飛ばして更新 ++i へ進み，i == 4 では break で for を抜ける．"
  "// i == 4 の break を continue に変えた版（4 も printf だけを飛ばして更新へ進み，5 まで表示する）．"
  "        if (i == 4) { break; }"
  "        if (i == 4) { continue; }   // break を continue に変えた")

# 確認問題7: default がなく一致する case もないときは，switch の後の文へ進む
softprac_add_variant(YearGroup versions/no_default.c no_default_year_5)

# 確認問題8: 講義の goto の例と，goto done; を break; に置き換えた版（どちらも 0，1，2，done）
softprac_add_variant(YearGroup versions/goto_done.c goto_done)
softprac_add_variant(YearGroup versions/goto_done.c goto_to_break
  "// n が 3 になったら，for の直後にあるラベル done へ移動する（この回の課題では goto を使わない）．"
  "// goto done; を break; に置き換え，使わなくなったラベル done: を消した版（break で for の直後の文へ進む）．"
  "            goto done;" "            break;          // goto done; の代わりに for を抜ける"
  "done:\n" "")
