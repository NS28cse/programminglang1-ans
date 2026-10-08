/* 第12回 課題3 エラー比較(1): main.c の include を存在しない calc_missing.h にした版（前処理で失敗する．ビルドしない） */
#include <stdio.h>
#include "calc_missing.h"
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));
    return 0;
}
