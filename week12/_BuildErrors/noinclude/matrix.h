/* 第12回 課題4 （比較用）#include "vector.h" を外した matrix.h．Vector が未定義になりコンパイルエラー（ビルドしない） */
#ifndef PL1_MATRIX_H
#define PL1_MATRIX_H

typedef struct {
    double v[4];
} Matrix;

Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y);
void print_matrix(Matrix a);

#endif
