// デバッグ題材: 点数の平均（第5回）
// 配列 scores の先頭の n 個（n = 1〜3）の平均を，小数第 1 位まで「n=個数 mean=平均」の形で表示する。
#include <stdio.h>

enum { COUNT = 3 };

double mean_score(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {70, 85, 90};
    for (int n = 1; n <= COUNT; ++n) {
        printf("n=%d mean=%.1f\n", n, mean_score(scores, n));
    }
    return 0;
}

// 契約: n は 1 以上で，a から n 個の要素を読めること。a[0]〜a[n-1] の平均を返す
double mean_score(const int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    double mean = sum / n;
    return mean;
}
