/*
 * 第8回 課題1　配列要素も交換する（Swap / versions/swap_double.c）
 * double 版の swap_double で，初期配列の添字 1 と 4 を 1 回だけ交換して表示する．
 * 続けて 2 回呼ぶと元に戻るので，呼び出し方を変えて試すときも初期配列から 1 回だけ呼ぶ．
 */
#include <stdio.h>
enum { COUNT = 6 };
void swap_double(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}
int main(void)
{
    double a[COUNT] = {1.0, 5.0, 3.0, 4.0, 2.0, 6.0};
    swap_double(&a[1], &a[4]);
    printf("a:");
    for (int i = 0; i < COUNT; ++i) {
        printf(" %.1f", a[i]);
    }
    printf("\n");
    return 0;
}
