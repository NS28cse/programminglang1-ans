/* 第12回 課題4　ベクトルと行列を分割する（VectorCalc / vector.h）
   講義 7 の vector.h．2 成分ベクトルの型と操作の宣言 */
#ifndef PL1_VECTOR_H
#define PL1_VECTOR_H

typedef struct {
    double v[2];
} Vector;

Vector axpy(double alpha, Vector a, Vector b);
void print_vector(Vector a);

#endif
