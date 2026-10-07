# 第13回 発展1「realloc の失敗を模擬する」GrowArrayFail
# 本体は simulate_failure = 1（再確保失敗の経路）。simulate_failure = 0 にした版（GrowArray と同じ動作）と，
# 縮小（3→1）の再確保が失敗する版もビルドしてテストする
softprac_add_program(GrowArrayFail grow_array.c)

softprac_add_variant(GrowArrayFail grow_array.c simulate_failure_0
  "const int simulate_failure = 1" "const int simulate_failure = 0")
softprac_add_variant(GrowArrayFail grow_array.c shrink_fail_3_to_1
  "size_t new_n = 5;" "size_t new_n = 1;")
