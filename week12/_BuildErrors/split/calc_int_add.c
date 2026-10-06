/* 第12回 課題3 エラー比較(2): calc.c の add の戻り値型だけを int にした版（コンパイルで失敗する．ビルドしない） */
#include "calc.h"
int add(double a, double b)
{
    return a + b;
}
double multiply(double a, double b)
{
    return a * b;
}
