// デバッグ題材: 階乗の表（第14回）
// 0 から 5 までの n について，再帰関数 factorial で n! を求めて表示する（0! = 1）。
#include <stdio.h>

// 範囲: n は 0〜12（13! は int に収まらない）
int factorial(int n)
{
    if (n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(void)
{
    for (int n = 0; n <= 5; ++n) {
        printf("%d! = %d\n", n, factorial(n));
    }
    return 0;
}
