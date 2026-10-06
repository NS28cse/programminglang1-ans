/* 第12回 課題1・2 SplitCalc: 計算関数を呼び出す側．main はこのファイルだけに置く */
#include <stdio.h>
#include "calc.h"
int main(void)
{
    printf("add=%.1f\n", add(1.5, 2.0));
    printf("multiply=%.1f\n", multiply(1.5, 2.0));

    printf("subtract=%.1f\n", subtract(5.0, 2.0));
    printf("subtract(0.0, 0.0)=%.1f\n", subtract(0.0, 0.0));
    printf("subtract(2.0, 5.0)=%.1f\n", subtract(2.0, 5.0));

    /* 検証表の 4 組．毎回 q を 99.0 にしてから呼び，失敗時に q が変わらないことを確かめる */
    const double pairs[4][2] = {{6.0, 2.0}, {-6.0, 2.0}, {0.0, 2.0}, {6.0, 0.0}};
    for (int i = 0; i < 4; ++i) {
        double q = 99.0;
        int ok = calc_divide(pairs[i][0], pairs[i][1], &q);
        printf("calc_divide(%.1f, %.1f): ok=%d q=%.1f\n",
               pairs[i][0], pairs[i][1], ok, q);
    }
    return 0;
}
