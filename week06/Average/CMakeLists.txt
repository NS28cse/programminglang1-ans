# 第6回 課題3 Average
# 本体は演習ページの「完全なプログラム」。加えて次の版をビルドしてテストする
#   first, first_total_minus7: 最初の版（versions/average_first.c）と，total を -7 に変えた版
#   page_literal: 演習ページどおり (unsigned char)300 と書いた版（本体は MSVC の C4310 を避けて変数を経由）
#   i_100, i_100_no_cast, i_100_late_cast: i を 100 にした版。10000 は int の範囲内なので，キャストを外しても
#     計算後にキャストしても同じ結果になる。i = 50000 のまま i * i とする版は範囲外の計算なので作らない（読解だけ）
#   sign_compare: 符号の異なる比較 -10 < 10u の確認用（versions/sign_compare.c。結果は 0）
softprac_add_program(Average average.c)

softprac_add_variant(Average versions/average_first.c first)
softprac_add_variant(Average versions/average_first.c first_total_minus7
                     "int total = 7" "int total = -7"
                     [[の最初の版：キャストの位置と (int)-3.9 を比べる]]
                     [[の最初の版で total を -7 に変えた版：負の値でもキャストの位置と (int)-3.9 を比べる]])
set(title [[「完全なプログラム」]])
softprac_add_variant(Average average.c page_literal
                     "${title}" [[「完全なプログラム」を演習ページどおり (unsigned char)300 と書いた版]]
                     [[// 演習ページの (unsigned char)300 は定数を切り詰めるキャストで MSVC /W4 の C4310 になるため，
    // 300 をいったん int の変数に入れてから変換する（結果は同じ 44。README 参照）
    int large = 300;
    unsigned char small = (unsigned char)large;]]
                     [[// 演習ページどおりの書き方（MSVC /W4 では C4310。この版だけ /wd4310 でビルドする）
    unsigned char small = (unsigned char)300;]])
# 演習ページどおりの (unsigned char)300 は MSVC /W4 で C4310（cast truncates constant value）になる。
# CI の実行 37673022240（コミット 762b3fb，windows-msvc ジョブ，MSVC 19.51，/W4 /WX）のログで確認:
#   variants\page_literal\average.c(19,42): warning C4310: cast truncates constant value（/WX により C2220 のエラー）
# この版は「同じ 4 行を表示する」ことを確かめるためのものなので，C4310 だけ止める
target_compile_options(Average_page_literal PRIVATE $<$<C_COMPILER_ID:MSVC>:/wd4310>)
set(i_comment [[// 掛ける前に long long へ広げる（i * i を int のまま計算するとオーバーフローする）
    int i = 50000;]])
softprac_add_variant(Average average.c i_100
                     "${i_comment}"
                     [[// i を 100 にした版。掛ける前に long long へ広げる形のまま（10000 は int の範囲内）
    int i = 100;]]
                     "${title}" [[「完全なプログラム」で i を 100 にした版]])
softprac_add_variant(Average average.c i_100_no_cast
                     "${i_comment}"
                     [[// i = 100 なら積 10000 は int の範囲内なので，キャストなしでも同じ結果（大きな値では安全でない）
    int i = 100;]]
                     "(long long)i * i" "i * i"
                     "${title}" [[「完全なプログラム」で i を 100 にし，キャストを外した版]])
softprac_add_variant(Average average.c i_100_late_cast
                     "${i_comment}"
                     [[// 計算後に変換する形。i = 100 なら範囲内なので同じ結果になるが，解決にはならない
    int i = 100;]]
                     "(long long)i * i" "(long long)(i * i)"
                     "${title}" [[「完全なプログラム」で i を 100 にし，計算後にキャストする版]])

# README の「符号の異なる比較を読む」の確認用。int と unsigned int を < で比べると結果は 0。
# 警告が出る書き方をわざと示す版なので，CI の /WX と -DSOFTPRAC_WERROR=ON で止まらないよう，この版だけ
# MSVC の signed/unsigned mismatch（番号は例: C4018）と GCC/Clang の -Wsign-compare（-Wextra で有効）を止める
softprac_add_variant(Average versions/sign_compare.c sign_compare)
target_compile_options(Average_sign_compare PRIVATE $<$<C_COMPILER_ID:MSVC>:/wd4018> $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wno-sign-compare>)
