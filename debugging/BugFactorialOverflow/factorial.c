// デバッグ題材: 大きな階乗（第14回）
// 0 から 15 までの n について，再帰関数 factorial で n! を求めて表示する（15! = 1307674368000）。
#include <stdio.h>

// 範囲: n は 0〜15
int factorial(int n)
{
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(void)
{
    for (int n = 0; n <= 15; ++n) {
        printf("%2d! = %d\n", n, factorial(n));
    }
    return 0;
}
