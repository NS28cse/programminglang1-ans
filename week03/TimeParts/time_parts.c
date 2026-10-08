/* 第3回 課題1 秒を分と秒へ分解する（TimeParts） */
#include <stdio.h>

int main(void)
{
    int seconds = 3671;  /* 入力: 0〜10000秒の整数 */
    int minutes = seconds / 60;  /* 整数同士の除算なので小数部分は切り捨て */
    int rest = seconds % 60;     /* 60で割った余り（0〜59） */
    /* 60.0 で割るので double で除算する（60 だと整数除算の結果が保存される） */
    double decimal_minutes = seconds / 60.0;

    printf("%d min %d sec\n", minutes, rest);
    printf("decimal minutes=%.2f\n", decimal_minutes);
    return 0;
}
