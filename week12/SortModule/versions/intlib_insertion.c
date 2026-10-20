/* 第12回 発展2　別解：挿入ソートで並べ替える（SortModule / versions/intlib_insertion.c）
   qsort と比較関数の代わりに，整列済みの先頭部分へ次の要素を 1 つずつ差し込む挿入ソートで sort_ints を書く．
   intlib.h の宣言（公開する使い方）は本体と同じなので，sort_main.c は変更しなくてよい．parse_count は本体と同じ */
#include "intlib.h"
#include <errno.h>
#include <stdlib.h>

/* a[0]〜a[k-1] が昇順のとき，a[k] を正しい位置へ差し込んで a[0]〜a[k] を昇順にする．
   この翻訳単位の中だけで使うので static にする．値を直接比べるので差のオーバーフローは起きない */
static void insert_at(int a[], size_t k)
{
    int key = a[k];
    size_t j = k;
    while (j > 0 && a[j - 1] > key) {  /* key より大きい要素を 1 つ後ろへずらす．等しい要素は越えない */
        a[j] = a[j - 1];
        --j;
    }
    a[j] = key;
}

int parse_count(const char *text, int *out)
{
    char *end;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE ||
        value < 0 || value > INTLIB_CAPACITY) {
        return 0;  /* 数字がない・余分な文字・long の範囲外・0〜8 の範囲外 */
    }
    *out = (int)value;
    return 1;
}

void sort_ints(int a[], size_t n)
{
    for (size_t k = 1; k < n; ++k) {  /* n が 0・1 なら何もしない */
        insert_at(a, k);
    }
}
