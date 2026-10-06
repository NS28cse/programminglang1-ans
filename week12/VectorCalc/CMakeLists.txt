# 第12回 課題4 VectorCalc: ソースは講義 7 の 5 ファイル（vector_main.c は講義の版のまま）
softprac_add_program(VectorCalc vector_main.c vector.c matrix.c vector.h matrix.h)

# 手順3: A を単位行列に変えると 2Ax+y が 2x+y と一致する（variants/tests/identity.out）
softprac_add_variant(VectorCalc vector_main.c identity
  "Matrix a = {{1.0, -1.0, -1.0, 1.0}};" "Matrix a = {{1.0, 0.0, 0.0, 1.0}};")
# 手順4: gemv の alpha を 0，beta を 1 にすると結果が y になる（variants/tests/alpha0.out）
softprac_add_variant(VectorCalc vector_main.c alpha0
  "print_vector(gemv(2.0, a, x, 1.0, y));" "print_vector(gemv(0.0, a, x, 1.0, y));")
# 手順5: 関数呼び出しの後に x と y を表示し，変わっていないことを確かめる（variants/tests/unchanged.out）
softprac_add_variant(VectorCalc vector_main.c unchanged
  "    return 0;" [=[    print_vector(x);
    print_vector(y);
    return 0;]=])
