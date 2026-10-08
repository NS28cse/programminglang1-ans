/* 第12回 課題1・2 SplitCalc: 計算関数の定義．自分のヘッダも読み，宣言との型の不一致を検出する */
#include "calc.h"
double add(double a, double b)
{
    return a + b;
}
double multiply(double a, double b)
{
    return a * b;
}
double subtract(double a, double b)
{
    return a - b;
}
int calc_divide(double a, double b, double *out)
{
    if (b == 0.0) {
        return 0;  /* 割る前に検査する．失敗時は *out に書き込まない */
    }
    *out = a / b;
    return 1;
}
