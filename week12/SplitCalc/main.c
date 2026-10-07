/* 第12回 課題1・2 SplitCalc: 計算関数を呼び出す側．main はこのファイルだけに置く */
#include <stdio.h>
#include "calc.h"
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));
    printf("subtract=%.1f\n", subtract(5.0, 2.0));
    double q = 99.0;  /* 失敗したときに保存先が変わらないことを確かめるための初期値 */
    int ok = calc_divide(6.0, 2.0, &q);
    printf("calc_divide(6.0, 2.0): ok=%d q=%.1f\n", ok, q);
    return 0;
}
