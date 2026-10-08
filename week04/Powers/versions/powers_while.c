// 第4回 課題4 100 未満の 2 の累乗（Powers）の while 版
// for の初期化をループの前へ，更新を本体の最後へ移した．
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
