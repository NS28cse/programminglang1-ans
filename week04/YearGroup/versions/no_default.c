// 第4回 確認問題7 default のない switch で，一致する case がないとき（YearGroup / versions/no_default.c）
// school_year = 5 はどの case にも一致しないので，switch の中の文を何も実行せずに switch の後の文へ進む．
#include <stdio.h>

int main(void)
{
    int school_year = 5;

    switch (school_year) {
    case 1:
    case 2:
        printf("lower years\n");
        break;
    case 3:
    case 4:
        printf("upper years\n");
        break;
    }
    printf("after switch\n");   // 一致する case がなくても，ここから続ける
    return 0;
}
