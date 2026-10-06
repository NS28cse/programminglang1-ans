# 第3回 課題4 Leap
# 本体（2000 年）に加えて，「例外を含む年で確認する」版をビルドしてテストする
softprac_add_program(Leap leap.c)

softprac_add_variant(Leap leap.c year_1900 "year = 2000" "year = 1900")
softprac_add_variant(Leap leap.c year_2024 "year = 2000" "year = 2024")
softprac_add_variant(Leap leap.c year_2025 "year = 2000" "year = 2025")
