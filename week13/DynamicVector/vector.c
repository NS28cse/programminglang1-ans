// 第13回 発展3　不透明な Vector の生成と解放（DynamicVector / vector.c）
// 構造体の定義と，確保・計算・取得・解放の実装。sizeof *p や p->v を使えるのはこのファイルだけ。
#include "vector.h"
#include <stdlib.h>

struct vector {
    double v[2];    // 配列メンバは本体に含まれるので，本体の free だけで後始末が終わる
};

Vector *vector_create(double x, double y)
{
    Vector *p = malloc(sizeof *p);
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
        return 0;   // 失敗時は *out に書き込まない
    }
    *out = p->v[index];
    return 1;
}

void vector_destroy(Vector **p)
{
    if (p != NULL) {
        free(*p);   // *p が NULL なら free は何もしない
        *p = NULL;  // 呼び出し元のポインタ変数を NULL にする
    }
}
