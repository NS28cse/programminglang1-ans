// 第5回 課題2　別解：列の合計を配列に持ち，行の順に 1 回走査する（ColumnSum / versions/row_major.c）
// 講義と同じ「外側が行」の順にメモリ上の並びどおり読み，各要素を自分の列の合計 col_sum[col] へ足す。
#include <stdio.h>

enum { COUNT = 5 };

int sum_array(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int total = sum_array(scores, COUNT);
    printf("total=%d mean=%.1f\n", total, total / 5.0);
    int table[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int col_sum[3] = {0};  // 3 列の合計をすべて 0 から始める（要素数は table の列数と同じ）
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            col_sum[col] += table[row][col];
        }
    }
    // 全要素を足し終えてから，列ごとに表示する
    for (int col = 0; col < 3; ++col) {
        printf("col %d: %d\n", col, col_sum[col]);
    }
    return 0;
}

int sum_array(const int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}
