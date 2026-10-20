// 第5回 課題4　別解：指数を半分にしながら掛ける累乗（Functions / versions/power_squaring.c）
// base^exponent を，exponent が奇数なら result に base を掛け，base を 2 乗して exponent を半分にする，の繰り返しで求める。
#include <stdio.h>

float average(float a, float b);
int power(int base, int exponent);

int main(void)
{
    float result = average(2.0f, 4.0f);  // 戻り値を変数に保存してから表示する
    printf("average=%.1f\n", result);
    printf("power=%d\n", power(2, 5));
    return 0;
}

// 範囲: a と b は -100〜100
float average(float a, float b)
{
    return (a + b) / 2.0f;
}

// 範囲: base は 1〜5，exponent は 0〜5（負の指数や int を超える結果は扱わない）
// 仮引数 base と exponent はコピーなので，書き換えても呼び出し元の値は変わらない
int power(int base, int exponent)
{
    int result = 1;  // exponent が 0 なら 1 回も掛けずに 1 を返す
    // 例: 2^5 = 2^1 * 2^4。exponent の 2 進数 101 の 1 の桁に当たる base を result に掛ける
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        exponent /= 2;
        if (exponent > 0) {
            base *= base;  // 次の桁の分。もう使わない最後の 2 乗はしない
        }
    }
    return result;
}
