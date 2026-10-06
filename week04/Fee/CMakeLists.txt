# 第4回 課題1（Fee）: 本体と，age を検証表の値へ変えた版をビルドしてテストする
softprac_add_program(Fee fee.c)

include("${CMAKE_CURRENT_SOURCE_DIR}/../_cmake/variants.cmake")
week04_add_variant(age_m1 fee.c variants/age_m1 "age = 17" "age = -1")
week04_add_variant(age_0  fee.c variants/age_0  "age = 17" "age = 0")
week04_add_variant(age_5  fee.c variants/age_5  "age = 17" "age = 5")
week04_add_variant(age_6  fee.c variants/age_6  "age = 17" "age = 6")
week04_add_variant(age_18 fee.c variants/age_18 "age = 17" "age = 18")
