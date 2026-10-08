// 第5回 発展　役割を分ける（SumMean / summean.c）
// 合計を返す sum_array と，平均を計算して表示する main に役割を分ける。
// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n（1〜COUNT）を別に持つ。
#include <stdio.h>

enum { COUNT = 5 };

int sum_array(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};  // 値は 0〜100
    int n = COUNT;                             // 平均で割るので 1 以上
    int total = sum_array(scores, n);
    printf("total=%d mean=%.1f\n", total, (double)total / n);  // 整数除算を避ける
    return 0;
}

// 契約: n は 0 以上で，a から n 個の要素を読めること。n が 0 なら 0 を返す。
int sum_array(const int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}
