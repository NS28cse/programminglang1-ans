# 第13回 発展3 DynamicVector
# 本体は講義の 3 ファイルに「添字と保存先の検査」の断片を加えたもの。「解放後に NULL になること」と
# 「二重ポインタの意味」（後始末の後にもう一度 vector_destroy(&x) を呼んでも何もしない）を版としてテストする
softprac_add_program(DynamicVector vector_main.c vector.c vector.h)

softprac_add_variant(DynamicVector vector_main.c destroy_again
  [=[// 演習ページの「添字と保存先の検査」の断片（範囲外の添字 2 で vector_get が失敗し，out が 99.0 のまま）も含む。]=]
  [=[// 後始末の後に vector_destroy(&x) をもう一度呼び，3 つのポインタが NULL であることを表示する版。
// 演習ページの「添字と保存先の検査」の断片（範囲外の添字 2 で vector_get が失敗し，out が 99.0 のまま）も含む。]=]
  [=[    vector_destroy(&x);
    return status;]=]
  [=[    vector_destroy(&x);
    vector_destroy(&x);   // 確認用：x はすでに NULL なので何もしない
    if (x == NULL && y == NULL && result == NULL) {
        printf("x=NULL y=NULL result=NULL\n");
    } else {
        printf("some pointer is not NULL\n");
    }
    return status;]=])
