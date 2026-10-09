/* 第12回 発展1　静的ライブラリとして使う（CalcLib / calc.c）
   静的ライブラリの実装．main は置かない */
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
