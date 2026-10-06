// 第13回 発展3「途中で失敗した場合」（DynamicVectorFail / vector.c）
// DynamicVector/vector.c のコピー。vector_create の malloc だけを試験用の vector_allocate に置き換えた。
// fail_on_call 回目の確保だけ NULL を返す（0 なら失敗させない）。この版は演習ページの値 2。
// 0，1，3 の版は CMakeLists.txt の softprac_add_variant が値を書き換えて作る。正常版は DynamicVector に残してある。
#include "vector.h"
#include <stdlib.h>

struct vector {
    double v[2];
};

// 試験用の確保関数：呼ばれた回数を static 変数で数え，fail_on_call 回目だけ失敗させる
static void *vector_allocate(size_t bytes)
{
    static int calls = 0;
    const int fail_on_call = 2;
    ++calls;
    if (calls == fail_on_call) {
        return NULL;
    }
    return malloc(bytes);
}

Vector *vector_create(double x, double y)
{
    Vector *p = vector_allocate(sizeof *p);
    if (p == NULL) {
        return NULL;
    }
    *p = (Vector){.v = {x, y}};
    return p;
}

Vector *vector_axpy(double alpha, const Vector *a, const Vector *b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }
    return vector_create(alpha * a->v[0] + b->v[0],
                         alpha * a->v[1] + b->v[1]);
}

int vector_get(const Vector *p, size_t index, double *out)
{
    if (p == NULL || index >= 2 || out == NULL) {
        return 0;
    }
    *out = p->v[index];
    return 1;
}

void vector_destroy(Vector **p)
{
    if (p != NULL) {
        free(*p);
        *p = NULL;
    }
}
