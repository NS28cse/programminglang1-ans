# 第12回 発展2 SortModule: ソースは自動の規則と同じ（フォルダ内の .c/.h をまとめる）
softprac_add_program(SortModule sort_main.c intlib.c intlib.h)

# 「data の先頭 2 つを INT_MAX，INT_MIN に変え，limits.h を追加して N=2 で試す」版（variants/tests/limits.*）
# intlib.c（main なし）とこのフォルダのヘッダは softprac_add_variant が自動で加える
softprac_add_variant(SortModule sort_main.c limits
  "#include <stdlib.h>" "#include <limits.h>\n#include <stdlib.h>"
  "{7, -2, 7, 0, 3, 9, -8, 1}" "{INT_MAX, INT_MIN, 7, 0, 3, 9, -8, 1}")
