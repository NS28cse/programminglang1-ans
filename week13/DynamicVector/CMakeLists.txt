# 第13回 発展3 DynamicVector
# 本体（講義の 3 ファイル＋「添字と保存先の検査」の断片）に加えて，README の「解放後に NULL になること」と
# 「二重ポインタの意味」（後始末の後にもう一度 vector_destroy(&x) を呼んでも何もしない）を確かめる版をテストする
softprac_add_program(DynamicVector vector_main.c vector.c vector.h)

softprac_add_variant(DynamicVector vector_main.c destroy_again
  [=[// 「添字と保存先の検査」の断片（範囲外の添字 2 で vector_get が失敗し，out が 99.0 のまま）も追加した。]=]
  [=[// （確認版）後始末の後に vector_destroy(&x) をもう一度呼び，3 つのポインタが NULL であることを表示する。]=]
  [=[    vector_destroy(&x);
    return status;]=]
  [=[    vector_destroy(&x);
    vector_destroy(&x);   // 確認用：x はすでに NULL なので何もしない
    printf("x=%s y=%s result=%s\n", x == NULL ? "NULL" : "not NULL",
           y == NULL ? "NULL" : "not NULL", result == NULL ? "NULL" : "not NULL");
    return status;]=])
