# 第3回 課題3 Conditions
# 本体は自動の規則と同じ。値を変えて試す版（tests/variants/）を追加するためにこのファイルを置く
softprac_add_program(Conditions conditions.c)

include("${CMAKE_CURRENT_LIST_DIR}/../variants.cmake")
# 条件の境界を試す（1項目ずつ変える）。score を変えるときは d = 0 のまま
week03_add_variant(Conditions conditions.c score_minus1 "int score = 75;" "int score = -1;")
week03_add_variant(Conditions conditions.c score_0 "int score = 75;" "int score = 0;")
week03_add_variant(Conditions conditions.c score_100 "int score = 75;" "int score = 100;")
week03_add_variant(Conditions conditions.c score_101 "int score = 75;" "int score = 101;")
# score = 75 に戻して d を変える
week03_add_variant(Conditions conditions.c d_3 "int d = 0;" "int d = 3;")
week03_add_variant(Conditions conditions.c d_6 "int d = 0;" "int d = 6;")
