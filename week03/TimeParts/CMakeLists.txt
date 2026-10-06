# 第3回 課題1 TimeParts
# 本体は自動の規則と同じ。値を変えて試す版（tests/variants/）を追加するためにこのファイルを置く
softprac_add_program(TimeParts time_parts.c)

include("${CMAKE_CURRENT_LIST_DIR}/../variants.cmake")
# 境界の値を試す（seconds の初期値を変える）。10000 は入力範囲の上限
week03_add_variant(TimeParts time_parts.c seconds_0 "int seconds = 3671;" "int seconds = 0;")
week03_add_variant(TimeParts time_parts.c seconds_59 "int seconds = 3671;" "int seconds = 59;")
week03_add_variant(TimeParts time_parts.c seconds_60 "int seconds = 3671;" "int seconds = 60;")
week03_add_variant(TimeParts time_parts.c seconds_61 "int seconds = 3671;" "int seconds = 61;")
week03_add_variant(TimeParts time_parts.c seconds_10000 "int seconds = 3671;" "int seconds = 10000;")
# 説明すること: seconds = 61 で右辺を seconds / 60 にすると 1.00 になる
week03_add_variant(TimeParts time_parts.c int_division_61
  "int seconds = 3671;" "int seconds = 61;"
  "seconds / 60.0;" "seconds / 60;")
