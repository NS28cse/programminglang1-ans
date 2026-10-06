# 第3回 課題4 Leap
# 本体は自動の規則と同じ。値を変えて試す版（tests/variants/）を追加するためにこのファイルを置く
softprac_add_program(Leap leap.c)

include("${CMAKE_CURRENT_LIST_DIR}/../variants.cmake")
# 例外を含む年で確認する（2000 は本体の tests/basic）
week03_add_variant(Leap leap.c year_1900 "int year = 2000;" "int year = 1900;")
week03_add_variant(Leap leap.c year_2024 "int year = 2000;" "int year = 2024;")
week03_add_variant(Leap leap.c year_2025 "int year = 2000;" "int year = 2025;")
