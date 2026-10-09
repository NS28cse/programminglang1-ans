# 第13回 発展1「realloc の失敗を模擬する」GrowArrayFail
# 本体は simulate_failure = 1（再確保失敗の経路）。simulate_failure = 0 に戻した版（GrowArray と同じ動作）と，
# 縮小（3→1）の再確保が失敗する版もテストする
softprac_add_program(GrowArrayFail grow_array.c)

set(fail_header [=[// GrowArray のコピーで，realloc の呼び出しを試験用の try_resize（simulate_failure = 1）に置き換えたもの。
// 再確保に失敗しても元の領域が残っていること（p[0] が 1 のまま）を確かめてから解放して終了する。]=])

softprac_add_variant(GrowArrayFail grow_array.c simulate_failure_0
  "${fail_header}"
  [=[// GrowArray のコピーで，realloc の呼び出しを try_resize に置き換え，simulate_failure = 0 にした版。
// 再確保は成功し，GrowArray と同じ表示になる。]=]
  "const int simulate_failure = 1" "const int simulate_failure = 0")
softprac_add_variant(GrowArrayFail grow_array.c shrink_fail_3_to_1
  "${fail_header}"
  [=[// GrowArray のコピーで，try_resize（simulate_failure = 1）を使い，new_n = 1 に書き換えた版。
// 縮小の再確保が失敗しても元の 3 要素が残っていること（p[0] が 1 のまま）を確かめてから解放して終了する。]=]
  "size_t new_n = 5;" "size_t new_n = 1;")
