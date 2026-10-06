/* 第12回 課題4 VectorCalc: 行列とベクトルの計算．v[2*i+j] が第 i 行第 j 列（講義 7 の matrix.c） */
#include "matrix.h"
#include <stdio.h>

Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y)
{
    Vector result = {{
        alpha * (a.v[0] * x.v[0] + a.v[1] * x.v[1]) + beta * y.v[0],
        alpha * (a.v[2] * x.v[0] + a.v[3] * x.v[1]) + beta * y.v[1]
    }};
    return result;
}

void print_matrix(Matrix a)
{
    printf("[%.1f %.1f]\n[%.1f %.1f]\n",
           a.v[0], a.v[1], a.v[2], a.v[3]);
}
