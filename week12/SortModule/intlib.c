/* 第12回 発展2 SortModule: 個数の変換と並べ替えの実装 */
#include "intlib.h"
#include <errno.h>
#include <stdlib.h>

/* qsort の比較関数．この翻訳単位の中だけで使うので static にする．
   x - y はオーバーフローし得るので，大小比較で -1・0・1 を返す */
static int compare_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
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
    qsort(a, n, sizeof a[0], compare_int);  /* 関数名を渡す（呼び出した結果ではない） */
}
