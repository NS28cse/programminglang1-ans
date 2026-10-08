# 第6回 課題4 CompareJoin
# 本体（容量10，suffix "fuga"）に加えて，演習ページの「容量の境界」の表（9，8）と
# 「比較の条件を変える」（suffix を "hoge"，"z"，""）の版，容量の下限5の版をビルドしてテストする。
# loop_lt は i <= added を i < added にした誤りの例（残りの要素が初期化で 0 なので，表示は正しく見えてしまう）
softprac_add_program(CompareJoin compare_join.c)

softprac_add_variant(CompareJoin compare_join.c capacity_9 "char text[10]" "char text[9]")
softprac_add_variant(CompareJoin compare_join.c capacity_8 "char text[10]" "char text[8]")
softprac_add_variant(CompareJoin compare_join.c capacity_5 "char text[10]" "char text[5]")
softprac_add_variant(CompareJoin compare_join.c capacity_5_suffix_empty
                     "char text[10]" "char text[5]" [[suffix[] = "fuga"]] [[suffix[] = ""]])
softprac_add_variant(CompareJoin compare_join.c suffix_hoge [[suffix[] = "fuga"]] [[suffix[] = "hoge"]])
softprac_add_variant(CompareJoin compare_join.c suffix_z [[suffix[] = "fuga"]] [[suffix[] = "z"]])
softprac_add_variant(CompareJoin compare_join.c suffix_empty [[suffix[] = "fuga"]] [[suffix[] = ""]])
softprac_add_variant(CompareJoin compare_join.c loop_lt
                     [[// i == added で suffix の終端もコピーする
        for (size_t i = 0; i <= added; ++i) {]]
                     [[// 誤りの例: i < added では suffix の終端をコピーしない
        for (size_t i = 0; i < added; ++i) {]])

# 参考: 容量を確かめた後のループを strcat に置き換えた版（README の「strcat で書く場合」）。
# strcat は MSVC で C4996 になるので，#include より前に _CRT_SECURE_NO_WARNINGS を書く
set(strcat_pairs
    [[// 第6回 課題4 比較してから連結する（CompareJoin / compare_join.c）]]
    [[// 第6回 課題4 比較してから連結する（CompareJoin）の参考版: 容量を確かめた後の連結を strcat で行う]]
    [[#include <stdio.h>]]
    [[#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>]]
    [[// i == added で suffix の終端もコピーする
        for (size_t i = 0; i <= added; ++i) {
            text[used + i] = suffix[i];
        }]]
    [[// strcat は容量を確かめないので，上の if で確かめてから呼ぶ
        strcat(text, suffix);]])
softprac_add_variant(CompareJoin compare_join.c strcat ${strcat_pairs})
softprac_add_variant(CompareJoin compare_join.c strcat_capacity_8 ${strcat_pairs} "char text[10]" "char text[8]")
