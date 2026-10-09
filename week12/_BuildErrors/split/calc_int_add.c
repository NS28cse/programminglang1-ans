/* 第12回 課題3　リンクエラーを調べる（_BuildErrors / split/calc_int_add.c）: エラー比較(2)．calc.c の add の戻り値型だけを int にした版で，コンパイルで失敗する */
#include "calc.h"
int add(double a, double b)
{
    return a + b;
}
double multiply(double a, double b)
{
    return a * b;
}
