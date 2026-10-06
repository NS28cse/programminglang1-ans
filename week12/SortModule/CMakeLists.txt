# 第12回 発展2 SortModule: ソースは自動の規則と同じ（フォルダ内の .c/.h をまとめる）
softprac_add_program(SortModule sort_main.c intlib.c intlib.h)

# 検証表の「引数として空文字列 ""」のケース．tests/<ケース>.args では
# 空行 1 行だけのファイルが「引数なし」として渡されるため（cmake/RunTest.cmake の制限），ここで直接登録する
add_test(NAME "${SOFTPRAC_WEEK}/SortModule/empty_string" COMMAND SortModule "")
set_tests_properties("${SOFTPRAC_WEEK}/SortModule/empty_string" PROPERTIES
  PASS_REGULAR_EXPRESSION "^invalid N: \"\" \\(expected an integer from 0 to 8\\)\r?\n$")

# 「data の先頭 2 つを INT_MAX，INT_MIN に変え，limits.h を追加して N=2 で試す」版（variants/tests/limits.*）
softprac_add_variant(SortModule sort_main.c limits
  "#include <stdlib.h>" "#include <limits.h>\n#include <stdlib.h>"
  "{7, -2, 7, 0, 3, 9, -8, 1}" "{INT_MAX, INT_MIN, 7, 0, 3, 9, -8, 1}")
# 書き換えた sort_main.c は別のフォルダに作られるので，残りのソースとヘッダの場所を追加する
target_sources(SortModule_limits PRIVATE intlib.c)
target_include_directories(SortModule_limits PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
