// デバッグ題材: 偶数の合計（第4回）
// 1 から n までの整数のうち，偶数だけを足した合計を表示する（n = 10 なら 2 + 4 + 6 + 8 + 10 = 30）。
#include <stdio.h>

int main(void)
{
    int n = 10;
    int sum = 0;

    for (int i = 1; i < n; ++i) {
        if (i % 2 == 0) {
            sum += i;
        }
    }
    printf("sum=%d\n", sum);
    return 0;
}
