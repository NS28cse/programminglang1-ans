# 第12回 発展2 SortModule: ソースは自動の規則と同じ（フォルダ内の .c/.h をまとめる）
softprac_add_program(SortModule sort_main.c intlib.c intlib.h)

# 「data の先頭 2 つを INT_MAX，INT_MIN に変え，limits.h を追加して N=2 で試す」版（variants/tests/limits.*）
# intlib.c（main なし）とこのフォルダのヘッダは softprac_add_variant が自動で加える
softprac_add_variant(SortModule sort_main.c limits
  "#include <stdio.h>" "#include <limits.h>\n#include <stdio.h>"
  "{7, -2, 7, 0, 3, 9, -8, 1}" "{INT_MAX, INT_MIN, 7, 0, 3, 9, -8, 1}"
  "引数 N を検査し，固定データの先頭 N 個を昇順に並べて表示する"
  "data の先頭 2 つを INT_MAX，INT_MIN に変えた版（N=2 で小さい方が先になる）")

# 別解: 挿入ソートで書いた intlib（versions/intlib_insertion.c）を本体の sort_main.c と組み合わせる版
# softprac_add_variant が自動で加える同じフォルダの intlib.c を外し，代わりに別解の intlib を使う
function(sortmodule_use_insertion target)
  get_target_property(srcs ${target} SOURCES)
  list(FILTER srcs EXCLUDE REGEX "/intlib\\.c$")
  set_property(TARGET ${target} PROPERTY SOURCES ${srcs})
  foreach(source IN LISTS ARGN)
    target_sources(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
  endforeach()
endfunction()

# 本体と同じ引数で試す（variants/tests/insertion--*）
softprac_add_variant(SortModule versions/intlib_insertion.c insertion)
sortmodule_use_insertion(SortModule_insertion sort_main.c)
# limits と同じ書き換え（INT_MAX，INT_MIN と N=2）を別解の intlib で試す（variants/tests/insertion_limits.*）
softprac_add_variant(SortModule sort_main.c insertion_limits
  "#include <stdio.h>" "#include <limits.h>\n#include <stdio.h>"
  "{7, -2, 7, 0, 3, 9, -8, 1}" "{INT_MAX, INT_MIN, 7, 0, 3, 9, -8, 1}"
  "引数 N を検査し，固定データの先頭 N 個を昇順に並べて表示する"
  "data の先頭 2 つを INT_MAX，INT_MIN に変え，挿入ソートの intlib と組み合わせた版（N=2 で小さい方が先になる）")
sortmodule_use_insertion(SortModule_insertion_limits versions/intlib_insertion.c)
