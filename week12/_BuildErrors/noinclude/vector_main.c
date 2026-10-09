/* 第12回 課題4　ヘッダの独立性を確認する（_BuildErrors / noinclude/vector_main.c）: matrix.h だけを読む vector_main.c．このフォルダの matrix.h と組み合わせる */
#include "matrix.h"

int main(void)
{
    Vector x = {{1.0, 2.0}};
    Vector y = {{3.0, 4.0}};
    Matrix a = {{1.0, -1.0, -1.0, 1.0}};

    print_matrix(a);
    print_vector(axpy(2.0, x, y));
    print_vector(gemv(2.0, a, x, 1.0, y));
    return 0;
}
