// 第9回 課題1　値を返す版と場所を返す版の比較（ReturnMaximum / return_maximum.c）
// 期待する表示は before=12 12 と after=12 99。負の配列・場所の版だけ n=0 などは CMakeLists.txt の variant でテストする。
#include <stdio.h>

// 最大の整数値を返す。条件: n>=1 で，a には n 要素以上あること（空入力には対応しない）
int max_value(const int a[], int n)
{
    int best = a[0];  // 0 からではなく先頭要素から始める（全要素が負でも正しい）
    for (int i = 1; i < n; ++i) {
        if (a[i] > best) { best = a[i]; }
    }
    return best;
}

// 最大要素の場所を返す。n<=0 なら NULL。返すのは呼び出し元の配列の要素の場所
int *max_pointer(int a[], int n)
{
    if (n <= 0) { return NULL; }
    int *best = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > *best) { best = &a[i]; }
    }
    return best;  // best 自身のアドレスではなく，best が保存している配列要素のアドレスを返す
}

int main(void)
{
    int a[] = {7, 12, 4};
    int saved = max_value(a, 3);      // その時点の最大値のコピー
    int *found = max_pointer(a, 3);   // 元の配列の要素を指す
    if (found != NULL) {
        printf("before=%d %d\n", saved, *found);
        *found = 99;                  // 配列 a が変わる。saved は変わらない
        printf("after=%d %d\n", saved, *found);
    }
    return 0;
}
