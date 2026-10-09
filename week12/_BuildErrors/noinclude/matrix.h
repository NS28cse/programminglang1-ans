/* 第12回 課題4　ヘッダの独立性を確認する（_BuildErrors / noinclude/matrix.h）: #include "vector.h" を外した matrix.h．Vector が未定義になりコンパイルエラーになる */
#ifndef PL1_MATRIX_H
#define PL1_MATRIX_H

typedef struct {
    double v[4];
} Matrix;

Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y);
void print_matrix(Matrix a);

#endif
