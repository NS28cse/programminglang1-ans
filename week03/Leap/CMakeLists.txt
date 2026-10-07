# 第3回 課題4 Leap
# 本体（2000 年）に加えて，「例外を含む年で確認する」版をビルドしてテストする
softprac_add_program(Leap leap.c)

softprac_add_variant(Leap leap.c year_1900 "year = 2000" "year = 1900")
softprac_add_variant(Leap leap.c year_2024 "year = 2000" "year = 2024")
softprac_add_variant(Leap leap.c year_2025 "year = 2000" "year = 2025")
# 講義の例題と同じ 1 つの式（3 つの変数を使わない）で書いても同じ結果になる（例外の 1900 と 2000）
softprac_add_variant(Leap leap.c one_expr_1900
  "year = 2000" "year = 1900"
  "(div4 && not_div100) || div400" "(year % 4 == 0 && year % 100 != 0) || year % 400 == 0")
softprac_add_variant(Leap leap.c one_expr_2000
  "(div4 && not_div100) || div400" "(year % 4 == 0 && year % 100 != 0) || year % 400 == 0")
# 誤りの例（README の採点のポイント）: 100 の例外を落とす → 1900 が 1 になる
softprac_add_variant(Leap leap.c wrong_no_100_rule_1900
  "year = 2000" "year = 1900"
  "(div4 && not_div100) || div400" "year % 4 == 0 || year % 400 == 0")
