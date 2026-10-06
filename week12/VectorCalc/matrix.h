/* 第12回 課題4 VectorCalc: 2 行 2 列の行列．Vector を使うので，このヘッダ自身が vector.h を読む（講義 7 の matrix.h） */
#ifndef PL1_MATRIX_H
#define PL1_MATRIX_H

#include "vector.h"

typedef struct {
    double v[4];
} Matrix;

Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y);
void print_matrix(Matrix a);

#endif
