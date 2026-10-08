# 第6回 課題2 Lower
# 本体は関数 lower を使う版（期待する表示 hello c17!）。加えて次の版をビルドしてテストする
#   empty など: 演習ページの表の初期値に変えた版（各版は 1 行目のコメントにも変えた初期値を書く）
#   inline_if*: 最初の版（ループ内に if を書き，lower を呼ばない版）。表の 5 つの入力で同じ表示になることを確かめる
#   no_assign: 戻り値を代入しない誤りの例（値渡しなので text は変わらない）
softprac_add_program(Lower lower.c)

set(inline_if_old [[// 終端の手前まで処理する。返された文字を代入しないと text は変わらない
    for (size_t i = 0; text[i] != '\0'; ++i) {
        text[i] = lower(text[i]);]])
set(inline_if_new [[// 最初の版: ループの中で範囲を確かめて直接変換する
    for (size_t i = 0; text[i] != '\0'; ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (char)(text[i] + ('a' - 'A'));
        }]])
# 1 行目のコメントも，その版の説明に置き換える
set(inline_if_title_old [[1文字の変換を関数 lower に分けた版]])
set(inline_if_title_new [[最初の版（ループ内の if で変換。lower は使わない）]])
softprac_add_variant(Lower lower.c inline_if "${inline_if_old}" "${inline_if_new}"
                     "${inline_if_title_old}" "${inline_if_title_new}")

# 表の初期値に変えた版（本体と最初の版の両方）。1 行目のコメントにも変えた初期値を書く
softprac_add_variant(Lower lower.c empty [["Hello C17!"]] [[""]]
                     "${inline_if_title_old}" [[1文字の変換を関数 lower に分けた版で，初期値を "" に変えた版]])
softprac_add_variant(Lower lower.c AZaz09 [["Hello C17!"]] [["AZaz09"]]
                     "${inline_if_title_old}" [[1文字の変換を関数 lower に分けた版で，初期値を "AZaz09" に変えた版]])
softprac_add_variant(Lower lower.c at_AZ_bracket [["Hello C17!"]] [["@AZ["]]
                     "${inline_if_title_old}" [[1文字の変換を関数 lower に分けた版で，初期値を "@AZ[" に変えた版]])
softprac_add_variant(Lower lower.c A_space_B [["Hello C17!"]] [["A B"]]
                     "${inline_if_title_old}" [[1文字の変換を関数 lower に分けた版で，初期値を "A B" に変えた版]])
softprac_add_variant(Lower lower.c inline_if_empty
                     "${inline_if_old}" "${inline_if_new}" "${inline_if_title_old}"
                     [[最初の版（ループ内の if で変換。lower は使わない）で，初期値を "" に変えた版]]
                     [["Hello C17!"]] [[""]])
softprac_add_variant(Lower lower.c inline_if_AZaz09
                     "${inline_if_old}" "${inline_if_new}" "${inline_if_title_old}"
                     [[最初の版（ループ内の if で変換。lower は使わない）で，初期値を "AZaz09" に変えた版]]
                     [["Hello C17!"]] [["AZaz09"]])
softprac_add_variant(Lower lower.c inline_if_at_AZ_bracket
                     "${inline_if_old}" "${inline_if_new}" "${inline_if_title_old}"
                     [[最初の版（ループ内の if で変換。lower は使わない）で，初期値を "@AZ[" に変えた版]]
                     [["Hello C17!"]] [["@AZ["]])
softprac_add_variant(Lower lower.c inline_if_A_space_B
                     "${inline_if_old}" "${inline_if_new}" "${inline_if_title_old}"
                     [[最初の版（ループ内の if で変換。lower は使わない）で，初期値を "A B" に変えた版]]
                     [["Hello C17!"]] [["A B"]])

softprac_add_variant(Lower lower.c no_assign [[text[i] = lower(text[i]);]] [[lower(text[i]);]]
                     "${inline_if_title_old}" [[誤りの例（lower の戻り値を代入しないので text は変わらない）]])
