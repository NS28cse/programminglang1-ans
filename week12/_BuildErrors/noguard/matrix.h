/* 第12回 課題4 ガードなしの vector.h と組み合わせる正常な matrix.h（講義 7 の matrix.h のまま．ビルドしない） */
#ifndef PL1_MATRIX_H
#define PL1_MATRIX_H

#include "vector.h"

typedef struct {
    double v[4];
} Matrix;

Vector gemv(double alpha, Matrix a, Vector x, double beta, Vector y);
void print_matrix(Matrix a);

#endif
