// 第5回 課題4　平均と累乗を関数にする（Functions / functions.c）
// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。
// 関数は計算して値を返すだけで，表示は main が担当する。
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
    return (a + b) / 2.0f;  // 2.0f で割るので小数部を失わない
}

// 範囲: base は 1〜5，exponent は 0〜5（負の指数や int を超える結果は扱わない）
int power(int base, int exponent)
{
    int result = 1;  // 掛け算の単位元。exponent が 0 なら 1 のまま返す
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;  // exponent 回掛け終えてから返す
}
