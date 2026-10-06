/* 第12回 課題4 VectorCalc: 講義 7 の vector_main.c に，手順 3〜5 の確認を後ろへ追加した版 */
#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main(void)
{
    Vector x = {{1.0, 2.0}};
    Vector y = {{3.0, 4.0}};
    Matrix a = {{1.0, -1.0, -1.0, 1.0}};

    /* 手順 1・2: 講義の出力（2x+y と 2Ax+y） */
    print_matrix(a);
    print_vector(axpy(2.0, x, y));
    print_vector(gemv(2.0, a, x, 1.0, y));

    /* 手順 3: A を単位行列にすると 2Ax+y は 2x+y と一致する */
    Matrix identity = {{1.0, 0.0, 0.0, 1.0}};
    printf("--- identity ---\n");
    print_matrix(identity);
    print_vector(axpy(2.0, x, y));
    print_vector(gemv(2.0, identity, x, 1.0, y));

    /* 手順 4: alpha=0，beta=1 なら 0*Ax + 1*y = y */
    printf("--- alpha=0, beta=1 ---\n");
    print_vector(gemv(0.0, a, x, 1.0, y));

    /* 手順 5: 値渡しなので，呼び出し後も x と y は元のまま */
    printf("--- x and y after calls ---\n");
    print_vector(x);
    print_vector(y);
    return 0;
}
