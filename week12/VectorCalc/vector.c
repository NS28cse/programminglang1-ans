/* 第12回 課題4　ベクトルと行列を分割する（VectorCalc / vector.c）
   講義 7 の vector.c．ベクトルの計算．入力は値渡しなので呼び出し側の a，b は変わらない */
#include "vector.h"
#include <stdio.h>

Vector axpy(double alpha, Vector a, Vector b)
{
    Vector result = {{alpha * a.v[0] + b.v[0],
                      alpha * a.v[1] + b.v[1]}};
    return result;
}

void print_vector(Vector a)
{
    printf("(%.1f, %.1f)\n", a.v[0], a.v[1]);
}
