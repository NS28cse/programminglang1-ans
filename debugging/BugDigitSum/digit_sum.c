// デバッグ題材: 各桁の和（第6回）
// 数字だけからなる文字列 digits の各桁の数を足した和を表示する（"2024" なら 2 + 0 + 2 + 4 = 8）。
#include <stdio.h>

int main(void)
{
    char digits[] = "2024";
    int sum = 0;

    for (int i = 0; digits[i] != '\0'; ++i) {
        sum += digits[i];
    }
    printf("sum=%d\n", sum);
    return 0;
}
