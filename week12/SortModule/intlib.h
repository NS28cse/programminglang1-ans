/* 第12回 発展2 SortModule: 整数配列モジュールの公開する宣言．比較関数は実装の都合なのでここに置かない */
#ifndef PL1_INTLIB_H
#define PL1_INTLIB_H
#include <stddef.h>  /* size_t のため．利用側に取り込み順を要求しない */

#define INTLIB_CAPACITY 8

/* text が 0〜INTLIB_CAPACITY の整数だけなら *out に保存して 1 を返す．
   失敗時は 0 を返し，*out を変更しない */
int parse_count(const char *text, int *out);
/* a[0]〜a[n-1] を昇順に並べ替える */
void sort_ints(int a[], size_t n);
#endif
