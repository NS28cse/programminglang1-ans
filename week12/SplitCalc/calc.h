/* 第12回 課題1・2 SplitCalc: 公開する宣言（利用側の main.c と実装側の calc.c の両方が読む） */
#ifndef PL1_CALC_H
#define PL1_CALC_H
double add(double a, double b);
double multiply(double a, double b);
double subtract(double a, double b);
/* b が 0.0 なら 0 を返し，*out を変更しない．それ以外は a / b を *out に保存して 1 を返す．
   out は有効な double を指すこと（呼び出し側の条件） */
int calc_divide(double a, double b, double *out);
#endif
