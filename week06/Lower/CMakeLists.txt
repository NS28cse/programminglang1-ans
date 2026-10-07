# 第6回 課題2 Lower
# 本体は関数 lower を使う版（期待する表示 hello c17!）。加えて次の版をビルドしてテストする
#   empty など: 演習ページの表の初期値に変えた版
#   inline_if*: 最初の版（ループ内に if を書き，lower を呼ばない版）。表の 5 つの入力で同じ表示になることを確かめる
#   no_assign: 戻り値を代入しない誤りの例（値渡しなので text は変わらない）
softprac_add_program(Lower lower.c)

softprac_add_variant(Lower lower.c empty [["Hello C17!"]] [[""]])
softprac_add_variant(Lower lower.c AZaz09 [["Hello C17!"]] [["AZaz09"]])
softprac_add_variant(Lower lower.c at_AZ_bracket [["Hello C17!"]] [["@AZ["]])
softprac_add_variant(Lower lower.c A_space_B [["Hello C17!"]] [["A B"]])

set(inline_if_old [[text[i] = lower(text[i]);]])
set(inline_if_new [[if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (char)(text[i] + ('a' - 'A'));
        }]])
softprac_add_variant(Lower lower.c inline_if "${inline_if_old}" "${inline_if_new}")
softprac_add_variant(Lower lower.c inline_if_empty
                     "${inline_if_old}" "${inline_if_new}" [["Hello C17!"]] [[""]])
softprac_add_variant(Lower lower.c inline_if_AZaz09
                     "${inline_if_old}" "${inline_if_new}" [["Hello C17!"]] [["AZaz09"]])
softprac_add_variant(Lower lower.c inline_if_at_AZ_bracket
                     "${inline_if_old}" "${inline_if_new}" [["Hello C17!"]] [["@AZ["]])
softprac_add_variant(Lower lower.c inline_if_A_space_B
                     "${inline_if_old}" "${inline_if_new}" [["Hello C17!"]] [["A B"]])

softprac_add_variant(Lower lower.c no_assign [[text[i] = lower(text[i]);]] [[lower(text[i]);]])
