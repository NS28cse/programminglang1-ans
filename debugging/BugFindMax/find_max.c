// デバッグ題材: 最大の要素の場所を返す（第9回）
// find_max は配列の最大の要素の場所を呼び出し元のポインタ変数へ書き，成功なら 1，n <= 0 なら 0 を返す。
// main は最大の点数とその添字を表示する。
#include <stdio.h>

enum { COUNT = 5 };

int find_max(int a[], int n, int *out)
{
    if (n <= 0) {
        return 0;
    }
    out = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > *out) {
            out = &a[i];
        }
    }
    return 1;
}

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int *best = &scores[0];

    if (find_max(scores, COUNT, best)) {
        printf("max=%d index=%d\n", *best, (int)(best - scores));
    }
    return 0;
}
