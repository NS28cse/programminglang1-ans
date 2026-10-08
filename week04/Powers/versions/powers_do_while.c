// 第4回 課題4 100 未満の 2 の累乗（Powers）の do-while 版（while との違いを確かめる比較用）
// 条件を本体の後で調べるため，limit が 1 でも本体を 1 回実行する．
#include <stdio.h>

int main(void)
{
    int limit = 100;
    int power = 1;

    do {
        printf("%d, ", power);
        power *= 2;
    } while (power < limit);
    printf("\n");
    return 0;
}
