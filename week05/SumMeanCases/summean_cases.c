// 第5回 発展 の検証用（SumMeanCases / summean_cases.c）
// 演習ページの 3 つの場合と範囲の端について，sum_array の戻り値と平均を表示する。
// sum_array は SumMean/summean.c と同じもの。
#include <stdio.h>

enum { COUNT = 5 };

int sum_array(const int a[], int n);
void print_case(const int a[], int n);

int main(void)
{
    int original[COUNT] = {72, 85, 60, 93, 80};
    int zero[COUNT] = {0};
    int hundred[COUNT] = {100, 100, 100};
    int full[COUNT] = {100, 100, 100, 100, 100};

    print_case(original, 5);
    print_case(zero, 1);
    print_case(hundred, 3);
    print_case(full, 5);  // 範囲の最大（合計 500）
    printf("sum_array(zero, 0)=%d\n", sum_array(zero, 0));  // 合計だけなら n=0 も受け付ける
    return 0;
}

// n（1 以上）と合計・平均を，SumMean と同じ形式で表示する
void print_case(const int a[], int n)
{
    int total = sum_array(a, n);
    printf("n=%d total=%d mean=%.1f\n", n, total, (double)total / n);
}

// 契約: n は 0 以上で，a から n 個の要素を読めること
int sum_array(const int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}
