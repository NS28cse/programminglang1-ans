/* 第12回 発展1　静的ライブラリとして使う（CalcLib / calc.h）
   静的ライブラリが公開する宣言（CalcApp は追加のインクルード ディレクトリで読む） */
#ifndef PL1_CALC_H
#define PL1_CALC_H
double add(double a, double b);
double multiply(double a, double b);
double subtract(double a, double b);
#endif
