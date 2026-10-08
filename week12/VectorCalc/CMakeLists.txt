# 第12回 課題4 VectorCalc: ソースは講義 7 の 5 ファイル（vector_main.c は講義の版のまま）
softprac_add_program(VectorCalc vector_main.c vector.c matrix.c vector.h matrix.h)

# 各版の先頭コメント（本体の説明）を，その版の説明に置き換えるための文字列
set(vc_comment "講義 7 の vector_main.c（手順3〜5 の書き換えは CMakeLists.txt の版でテストする）")

# 手順3: A を単位行列に変えると 2Ax+y が 2x+y と一致する（variants/tests/identity.out）
softprac_add_variant(VectorCalc vector_main.c identity
  "Matrix a = {{1.0, -1.0, -1.0, 1.0}};" "Matrix a = {{1.0, 0.0, 0.0, 1.0}};"
  "${vc_comment}" "手順3: A を単位行列に書き換えた版（2Ax+y が 2x+y と一致）")
# 手順4: gemv の alpha を 0，beta を 1 にすると結果が y になる（variants/tests/alpha0.out）
softprac_add_variant(VectorCalc vector_main.c alpha0
  "print_vector(gemv(2.0, a, x, 1.0, y));" "print_vector(gemv(0.0, a, x, 1.0, y));"
  "${vc_comment}" "手順4: alpha を 0 にした版（結果が y）")
# 手順5: 関数呼び出しの後に x と y を表示し，変わっていないことを確かめる（variants/tests/unchanged.out）
softprac_add_variant(VectorCalc vector_main.c unchanged
  "    return 0;" [=[    print_vector(x);
    print_vector(y);
    return 0;]=]
  "${vc_comment}" "手順5: 呼び出し後に x と y を表示する版")
# ヘッダの独立性: 直接の #include "vector.h" を外しても matrix.h 経由で読まれるのでビルドでき，講義の 4 行が出る
softprac_add_variant(VectorCalc vector_main.c no_direct_include
  [=[#include "vector.h"
]=] ""
  "${vc_comment}" [=[直接の #include "vector.h" を外した版（matrix.h 経由で読まれるのでビルドできる）]=])
