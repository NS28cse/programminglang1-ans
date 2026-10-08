// 第2回 課題5 発展：小数を使った計算（Temperature / temperature.c）
// 摂氏 celsius から華氏 fahrenheit を計算する。77.0 を直接書かず，式で求める
#include <stdio.h>

int main(void)
{
    double celsius = 25.0;
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;    // 9.0，5.0，32.0 と小数で書き，double で計算する

    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    return 0;
}
