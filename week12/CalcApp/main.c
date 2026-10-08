/* 第12回 発展1 CalcApp: 静的ライブラリ CalcLib の関数を呼び出すアプリ．このプロジェクトには main.c だけを入れる */
#include <stdio.h>
#include "calc.h"
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));
    printf("subtract=%.1f\n", subtract(5.0, 2.0));
    return 0;
}
