// 第4回 課題2　別解：ループを使わず式で 1 回で求める（EvenSum / versions/even_sum_formula.c）
// 1 から n までの偶数は 2, 4, …, 2m（m = n / 2 個）なので，合計は 2 × (1 + 2 + … + m) = m × (m + 1)．
#include <stdio.h>

int main(void)
{
    int n = 10;
    int m = n / 2;              // 偶数の個数．n が奇数でも整数除算の切り捨てで正しい個数になる
    int sum = m * (m + 1);      // 2 + 4 + … + 2m

    printf("%d\n", sum);
    return 0;
}
