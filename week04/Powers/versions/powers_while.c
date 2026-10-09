// 第4回 課題4 100 未満の 2 の累乗：while 版（Powers / versions/powers_while.c）
// for の初期化をループの前に，更新を本体の最後に置く．
#include <stdio.h>

int main(void)
{
    int limit = 100;
    int power = 1;

    while (power < limit) {
        printf("%d, ", power);
        power *= 2;
    }
    printf("\n");
    return 0;
}
