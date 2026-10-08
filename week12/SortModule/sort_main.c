/* 第12回 発展2 SortModule: 引数 N を検査し，固定データの先頭 N 個を昇順に並べて表示する */
#include <stdio.h>
#include "intlib.h"
int main(int argc, char *argv[])
{
    int data[INTLIB_CAPACITY] = {7, -2, 7, 0, 3, 9, -8, 1};
    int n;

    if (argc != 2) {
        fprintf(stderr, "usage: SortModule N (N is an integer from 0 to %d)\n", INTLIB_CAPACITY);
        return 1;
    }
    if (!parse_count(argv[1], &n)) {
        fprintf(stderr, "invalid N: \"%s\" (expected an integer from 0 to %d)\n",
                argv[1], INTLIB_CAPACITY);
        return 1;
    }

    sort_ints(data, (size_t)n);  /* 容量は 8，並べ替えるのは有効な先頭 n 個だけ */
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", data[i]);
    }
    printf("\n");  /* N=0 では改行だけになる */
    return 0;
}
