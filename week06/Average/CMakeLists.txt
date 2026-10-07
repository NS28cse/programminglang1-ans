# 第6回 課題3 Average
# 本体は演習ページの「完全なプログラム」。加えて次の版をビルドしてテストする
#   first, first_total_minus7: 最初の版（versions/average_first.c）と，total を -7 に変えた版
#   page_literal: 演習ページどおり (unsigned char)300 と書いた版（本体は MSVC の C4310 を避けて変数を経由）
#   i_100, i_100_no_cast, i_100_late_cast: i を 100 にした版。10000 は int の範囲内なので，キャストを外しても
#     計算後にキャストしても同じ結果になる。i = 50000 のまま i * i とする版は範囲外の計算なので作らない（読解だけ）
softprac_add_program(Average average.c)

softprac_add_variant(Average versions/average_first.c first)
softprac_add_variant(Average versions/average_first.c first_total_minus7 "int total = 7" "int total = -7")
softprac_add_variant(Average average.c page_literal
                     [[int large = 300;
    unsigned char small = (unsigned char)large;]]
                     [[unsigned char small = (unsigned char)300;]])
softprac_add_variant(Average average.c i_100 "int i = 50000" "int i = 100")
softprac_add_variant(Average average.c i_100_no_cast
                     "int i = 50000" "int i = 100" "(long long)i * i" "i * i")
softprac_add_variant(Average average.c i_100_late_cast
                     "int i = 50000" "int i = 100" "(long long)i * i" "(long long)(i * i)")
