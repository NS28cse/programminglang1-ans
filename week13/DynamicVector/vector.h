// 第13回 発展3　不透明な Vector の生成と解放（DynamicVector / vector.h）
// 公開するのは不完全型 Vector と操作関数の宣言だけ。struct vector のメンバは vector.c だけが知る。
#ifndef PL1_DYNAMIC_VECTOR_H
#define PL1_DYNAMIC_VECTOR_H

#include <stddef.h>

typedef struct vector Vector;

// 成功なら初期化した新しい Vector を返し，所有権は呼び出し元へ移る。確保失敗なら NULL。
Vector *vector_create(double x, double y);
// alpha*a + b を新しく確保して返す（a，b は借りるだけ）。NULL 入力・確保失敗なら NULL。
Vector *vector_axpy(double alpha, const Vector *a, const Vector *b);
// 成功なら成分を *out に保存して 1。p・out が NULL か添字が範囲外なら 0 を返し，*out は変更しない。
int vector_get(const Vector *p, size_t index, double *out);
// p は NULL でもよい。*p は NULL か，所有している有効な Vector でなければならない。解放後 *p を NULL にする。
void vector_destroy(Vector **p);

#endif
