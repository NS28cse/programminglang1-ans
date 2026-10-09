/* 第12回 課題3　リンクエラーを調べる（_BuildErrors / split/main.c）: 課題1 の講義どおりの main.c（正常版） */
#include <stdio.h>
#include "calc.h"
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));
    return 0;
}
