// 第5回 課題2　列ごとの合計（ColumnSum / arrays.c）
// 講義の arrays.c を変更し，二次元配列の行ごとの合計の代わりに列ごとの合計を表示する。
#include <stdio.h>

enum { COUNT = 5 };

int sum_array(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int total = sum_array(scores, COUNT);
    printf("total=%d mean=%.1f\n", total, total / 5.0);
    int table[2][3] = {{1, 2, 3}, {4, 5, 6}};
    // 外側を列（0〜2），内側を行（0〜1）にする。添字は常に table[行][列] の順
    for (int col = 0; col < 3; ++col) {
        int sum = 0;  // 列が変わるたびに 0 から数え直す
        for (int row = 0; row < 2; ++row) {
            sum += table[row][col];
        }
        printf("col %d: %d\n", col, sum);
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
