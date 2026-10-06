# 第3回 課題2 Update
# 本体は自動の規則と同じ。値や書き方を変えて試す版（tests/variants/）を追加するためにこのファイルを置く
softprac_add_program(Update update.c)

include("${CMAKE_CURRENT_LIST_DIR}/../variants.cmake")
# 複合代入を通常の代入の形へ書き換えても同じ結果になる
week03_add_variant(Update update.c plain_assignment
  "x += 3;" "x = x + 3;"
  "x *= 2;" "x = x * 2;")
# 最初の x を 0，-2 に変える
week03_add_variant(Update update.c x_0 "int x = 5;" "int x = 0;")
week03_add_variant(Update update.c x_minus2 "int x = 5;" "int x = -2;")
# 説明すること: x *= 2; と x += 3; の順番を逆にすると 17 になる
week03_add_variant(Update update.c swapped_order
  "    x += 3;\n    x *= 2;\n" "    x *= 2;\n    x += 3;\n")
