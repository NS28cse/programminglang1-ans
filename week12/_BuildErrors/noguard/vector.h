/* 第12回 課題4 ガードの 3 行（#ifndef・#define・#endif）だけを外した vector.h（ビルドしない） */

typedef struct {
    double v[2];
} Vector;

Vector axpy(double alpha, Vector a, Vector b);
void print_vector(Vector a);

