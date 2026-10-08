# 第6回 課題4 CompareJoin
# 本体（容量10，suffix "fuga"）に加えて，演習ページの「容量の境界」の表（9，8）と
# 「比較の条件を変える」（suffix を "hoge"，"z"，""）の版，容量の下限5の版をビルドしてテストする。
# loop_lt は i <= added を i < added にした誤りの例（残りの要素が初期化で 0 なので，表示は正しく見えてしまう）
softprac_add_program(CompareJoin compare_join.c)

# 各版は 1 行目のコメントにも「text の容量を 9 に変えた版」のような説明を足す
set(title [[（CompareJoin / compare_join.c）]])
foreach(capacity IN ITEMS 9 8 5)
  softprac_add_variant(CompareJoin compare_join.c capacity_${capacity}
                       "char text[10]" "char text[${capacity}]"
                       "${title}" "${title}。text の容量を ${capacity} に変えた版")
endforeach()
softprac_add_variant(CompareJoin compare_join.c capacity_5_suffix_empty
                     "char text[10]" "char text[5]" [[suffix[] = "fuga"]] [[suffix[] = ""]]
                     "${title}" [[（CompareJoin / compare_join.c）。text の容量を 5，suffix を "" に変えた版]])
softprac_add_variant(CompareJoin compare_join.c suffix_hoge [[suffix[] = "fuga"]] [[suffix[] = "hoge"]]
                     "${title}" [[（CompareJoin / compare_join.c）。suffix を "hoge" に変えた版]])
softprac_add_variant(CompareJoin compare_join.c suffix_z [[suffix[] = "fuga"]] [[suffix[] = "z"]]
                     "${title}" [[（CompareJoin / compare_join.c）。suffix を "z" に変えた版]])
softprac_add_variant(CompareJoin compare_join.c suffix_empty [[suffix[] = "fuga"]] [[suffix[] = ""]]
                     "${title}" [[（CompareJoin / compare_join.c）。suffix を "" に変えた版]])
softprac_add_variant(CompareJoin compare_join.c loop_lt
                     [[// i == added で suffix の終端もコピーする
        for (size_t i = 0; i <= added; ++i) {]]
                     [[// 誤りの例: i < added では suffix の終端をコピーしない
        for (size_t i = 0; i < added; ++i) {]]
                     [[（CompareJoin / compare_join.c）
// strcmp は戻り値の符号だけを使う。連結は書き込む前に容量を確かめ，終端も含めてループでコピーする。]]
                     [[（CompareJoin / compare_join.c）の誤りの例: ループを i < added にした版
// i < added では suffix の終端をコピーしない（この初期値では残りの要素が 0 なので表示は正しく見える）。]])

# 参考: 容量を確かめた後のループを strcat に置き換えた版（README の「strcat で書く場合」）。
# strcat は MSVC で C4996 になるので，#include より前に _CRT_SECURE_NO_WARNINGS を書く
set(strcat_title_old [[// 第6回 課題4 比較してから連結する（CompareJoin / compare_join.c）
// strcmp は戻り値の符号だけを使う。連結は書き込む前に容量を確かめ，終端も含めてループでコピーする。]])
set(strcat_title_new [[// 第6回 課題4 比較してから連結する（CompareJoin）の参考版: 容量を確かめた後の連結を strcat で行う
// strcmp は戻り値の符号だけを使う。strcat は容量を確かめないので，呼ぶ前に自分で確かめる。]])
set(strcat_include_old [[#include <stdio.h>]])
set(strcat_include_new [[#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>]])
set(strcat_loop_old [[// i == added で suffix の終端もコピーする
        for (size_t i = 0; i <= added; ++i) {
            text[used + i] = suffix[i];
        }]])
set(strcat_loop_new [[// strcat は容量を確かめないので，上の if で確かめてから呼ぶ
        strcat(text, suffix);]])
softprac_add_variant(CompareJoin compare_join.c strcat
                     "${strcat_title_old}" "${strcat_title_new}" "${strcat_include_old}" "${strcat_include_new}"
                     "${strcat_loop_old}" "${strcat_loop_new}")
softprac_add_variant(CompareJoin compare_join.c strcat_capacity_8
                     "${strcat_title_old}" "${strcat_title_new}" "${strcat_include_old}" "${strcat_include_new}"
                     "${strcat_loop_old}" "${strcat_loop_new}" "char text[10]" "char text[8]"
                     [[strcat で行う]] [[strcat で行う版で，text の容量を 8 に変えた版]])
