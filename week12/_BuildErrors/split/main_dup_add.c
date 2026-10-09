/* 第12回 課題3　リンクエラーを調べる（_BuildErrors / split/main_dup_add.c）: エラー比較(4)．add の本体を main.c にもコピーした版で，リンクで失敗する */
#include <stdio.h>
#include "calc.h"
double add(double a, double b)
{
    return a + b;
}
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));
    return 0;
}
