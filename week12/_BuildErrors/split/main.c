/* 第12回 課題1 の正常版（講義 3 の main.c） */
#include <stdio.h>
#include "calc.h"
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));
    return 0;
}
