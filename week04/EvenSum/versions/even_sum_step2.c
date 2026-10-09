// 第4回 課題2 偶数の合計：2 ずつ増やす版（EvenSum / versions/even_sum_step2.c）
// i は偶数だけを通るので，偶奇判定の if は不要．本体の回数は約半分になる．
#include <stdio.h>

int main(void)
{
    int n = 10;
    int sum = 0;

    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }
    printf("%d\n", sum);
    return 0;
}
