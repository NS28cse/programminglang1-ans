/*
 * 第8回 発展 Decompose: 複数の結果と場所を返す
 *   - decompose: 整数部（long）と小数部（double）の 2 つの出力先へ書き込む
 *   - min_pointer: 小さい方の値ではなく，その値がある「場所」を返す（講義のとおり main の前に定義）
 * main は演習ページのプログラムどおり．入力を変えた版・値引数の版・min_pointer の実験は
 * CMakeLists.txt で書き換えた版としてテストする．
 */
#include <stdio.h>
/* x は −100〜100 の有限な値．whole と fraction は有効な long と double を指す */
void decompose(double x, long *whole, double *fraction)
{
    *whole = (long)x;          /* 0 方向への切り捨て（四捨五入でも床関数でもない） */
    *fraction = x - *whole;
}
/* 等しいときは b を返す．返す場所は呼び出し元の変数なので，戻った後も寿命が続いている */
int *min_pointer(int *a, int *b)
{
    if (*a < *b) {
        return a;
    }
    return b;
}
int main(void)
{
    long whole = 0;
    double fraction = 0.0;
    decompose(3.14, &whole, &fraction);
    printf("whole=%ld fraction=%.2f\n", whole, fraction);
    return 0;
}
