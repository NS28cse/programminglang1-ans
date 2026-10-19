// デバッグ題材: 平均点（第6回）
// 5 人の点数の合計と平均（小数第 1 位まで）を表示する。
#include <stdio.h>

enum { COUNT = 5 };

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 81};
    int total = 0;

    for (int i = 0; i < COUNT; ++i) {
        total += scores[i];
    }
    double mean = total / COUNT;
    printf("total=%d mean=%.1f\n", total, mean);
    return 0;
}
