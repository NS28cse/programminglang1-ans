/*
 * 第8回 発展 Decompose: 複数の結果と場所を返す
 *   - decompose: 整数部（long）と小数部（double）の 2 つの出力先へ書き込む
 *   - min_pointer: 小さい方の値ではなく，その値がある「場所」を返す
 * 最初の 1 行が演習ページのプログラムの表示．その後は検証表と境界の値，min_pointer の実験．
 */
#include <stdio.h>
enum { COUNT = 8 };
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
/* 演習の min_pointer の実験を，x と y の初期値を変えて実行する */
void try_min_pointer(int x_init, int y_init)
{
    int x = x_init;
    int y = y_init;
    printf("[x=%d y=%d]\n", x_init, y_init);
    int *result = min_pointer(&x, &y);
    printf("minimum=%d points_to_y=%d\n", *result, result == &y);
    *result = 0;
    printf("x=%d y=%d\n", x, y);
}
int main(void)
{
    long whole = 0;
    double fraction = 0.0;
    decompose(3.14, &whole, &fraction);
    printf("whole=%ld fraction=%.2f\n", whole, fraction);

    /* 検証表の 4 つの入力と，範囲の両端・0 方向への切り捨てを確かめる値 */
    double inputs[COUNT] = {3.14, -3.14, 0.0, 5.0, -100.0, 100.0, 99.99, -0.5};
    for (int i = 0; i < COUNT; ++i) {
        decompose(inputs[i], &whole, &fraction);
        printf("x=%.2f: whole=%ld fraction=%.2f\n", inputs[i], whole, fraction);
    }

    try_min_pointer(9, 3);
    try_min_pointer(3, 9);
    try_min_pointer(5, 5);
    return 0;
}
