// 第5回 課題4 の検証用（FunctionsCases / functions_cases.c）
// 演習ページの「境界の値で確認する」の表の呼び出しと，範囲の端の値で戻り値を表示する。
// average と power は Functions/functions.c と同じもの。
#include <stdio.h>

float average(float a, float b);
int power(int base, int exponent);

int main(void)
{
    // 最初の表示に使った呼び出し
    printf("average(2.0f, 4.0f)=%.1f\n", average(2.0f, 4.0f));
    printf("power(2, 5)=%d\n", power(2, 5));
    // 演習ページの表
    printf("average(0.0f, 0.0f)=%.1f\n", average(0.0f, 0.0f));
    printf("average(-4.0f, 2.0f)=%.1f\n", average(-4.0f, 2.0f));
    printf("average(1.0f, 2.0f)=%.1f\n", average(1.0f, 2.0f));
    printf("power(2, 0)=%d\n", power(2, 0));
    printf("power(5, 1)=%d\n", power(5, 1));
    printf("power(5, 5)=%d\n", power(5, 5));
    // 範囲の端
    printf("average(-100.0f, -100.0f)=%.1f\n", average(-100.0f, -100.0f));
    printf("average(-100.0f, 100.0f)=%.1f\n", average(-100.0f, 100.0f));
    printf("average(100.0f, 100.0f)=%.1f\n", average(100.0f, 100.0f));
    printf("power(1, 5)=%d\n", power(1, 5));
    printf("power(1, 0)=%d\n", power(1, 0));
    return 0;
}

// 範囲: a と b は -100〜100
float average(float a, float b)
{
    return (a + b) / 2.0f;
}

// 範囲: base は 1〜5，exponent は 0〜5
int power(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}
