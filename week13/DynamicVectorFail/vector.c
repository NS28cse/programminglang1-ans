// 第13回 発展3「途中で失敗した場合」（DynamicVectorFail / vector.c）
// DynamicVector/vector.c のコピー。vector_create の malloc だけを試験用の vector_allocate に置き換えた。
// fail_on_call 回目の確保だけ NULL を返す（0 なら失敗させない）。値は FAIL_ON_CALL で指定し，
// CMakeLists.txt が 0〜3 の 4 つの実行ファイルを作る。Visual Studio でこのファイルだけを使う場合は，
// 下の #define の値を書き換えて 1 回ずつ実行し直せばよい。正常版は DynamicVector フォルダに残してある。
#include "vector.h"
#include <stdlib.h>

#ifndef FAIL_ON_CALL
#define FAIL_ON_CALL 2
#endif

struct vector {
    double v[2];
};

// 試験用の確保関数：呼ばれた回数を static 変数で数え，fail_on_call 回目だけ失敗させる
static void *vector_allocate(size_t bytes)
{
    static int calls = 0;
    const int fail_on_call = FAIL_ON_CALL;
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
