/* 第3回 課題3 範囲の判定と短絡評価（Conditions / conditions.c）
 * score が 0〜100 の範囲内かを && と || で判定し，&& の短絡評価で 0 による除算を防ぐ。
 */
#include <stdio.h>

int main(void)
{
    int score = 75;
    /* 0 <= score <= 100 とは書かず，2つの比較を && でつなぐ */
    int valid = score >= 0 && score <= 100;   /* 0以上100以下なら1 */
    int invalid = score < 0 || score > 100;   /* 0未満または100より大きければ1 */
    printf("score=%d valid=%d invalid=%d\n", score, valid, invalid);

    int n = 12;
    int d = 0;
    /* d != 0 が偽なら && の右側は評価されないので，0による除算は起きない */
    int large = d != 0 && n / d > 2;
    printf("n=%d d=%d large=%d\n", n, d, large);
    return 0;
}
