/* 第14回 課題3　互除法を反復へ書き換える（GcdLoop / gcd_loop.c）
 * 反復版 gcd_loop と再帰版 gcd を並べて比較する。
 * a と b は main の初期値を書き換えて変える（演習ページの表の 7 組と (0, 0)）。
 */
#include <stdio.h>

/* 再帰版（講義の recursion.c と同じ）。(0, 0) 以外の非負整数を前提とする */
unsigned int gcd(unsigned int a, unsigned int b)
{
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

/* 反復版。再帰の引数 (a, b) の変化を，状態変数 a と b の更新で表す */
unsigned int gcd_loop(unsigned int a, unsigned int b)
{
    while (b != 0) {
        unsigned int remainder = a % b; /* 先に余りを保存する（a を上書きすると元の a を失う） */
        a = b;
        b = remainder;
    }
    return a;
}

int main(void)
{
    unsigned int a = 48;
    unsigned int b = 18;
    /* (0, 0) は入力の対象外なので，呼び出しより前に拒否する */
    if (a == 0 && b == 0) {
        fputs("a and b must not both be zero\n", stderr);
        return 1;
    }
    unsigned int loop = gcd_loop(a, b);
    unsigned int recursive = gcd(a, b);
    printf("gcd(%u, %u): loop=%u recursive=%u equal=%d\n",
           a, b, loop, recursive, loop == recursive);
    return 0;
}
