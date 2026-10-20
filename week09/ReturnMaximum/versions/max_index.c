// 第9回 課題1　別解：最大要素の場所を添字で返す（ReturnMaximum / versions/max_index.c）
// max_pointer の代わりに，最大要素の添字（n<=0 なら -1）を返す max_index を使う。
// 添字は配列の名前 a と組にして a[i] と書くときだけ要素を表す（表示は本体と同じ before=12 12 と after=12 99）。
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

// 最大要素の添字を返す。n<=0 なら -1（有効な添字は 0 以上なので，失敗と区別できる）。
// 添字を返すだけなので，配列は書き換えない（const で受け取れる）
int max_index(const int a[], int n)
{
    if (n <= 0) { return -1; }
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[best]) { best = i; }
    }
    return best;
}

int main(void)
{
    int a[] = {7, 12, 4};
    int saved = max_value(a, 3);  // その時点の最大値のコピー
    int index = max_index(a, 3);  // 最大要素の添字（ここでは 1）
    if (index >= 0) {
        printf("before=%d %d\n", saved, a[index]);
        a[index] = 99;            // 配列 a が変わる。saved は変わらない
        printf("after=%d %d\n", saved, a[index]);
    }
    return 0;
}
