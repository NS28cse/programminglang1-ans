/* 第14回 課題1　階乗の境界（Factorial / recursion.c）
 * 講義の recursion.c に，反復版 factorial_loop と比較の断片を追加した版。
 * n は main の初期値を書き換えて変える（0，1，5，20，21 など）。
 */
#include <stdio.h>

/* n は 0〜20 を前提とする（21! は unsigned long long に収まらない） */
unsigned long long factorial(unsigned int n)
{
    if (n == 0) { return 1; }          /* 基底条件: 0! = 1 */
    return n * factorial(n - 1);       /* 子が戻った後（復帰時）に掛ける */
}

/* 講義6.1 の反復版。ループの各回で積を更新する（n は 0〜20 を前提とする） */
unsigned long long factorial_loop(unsigned int n)
{
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

/* (0, 0) 以外の非負整数を前提とする。b が 0 か調べてから剰余を求める */
unsigned int gcd(unsigned int a, unsigned int b)
{
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

int main(void)
{
    unsigned int n = 5;
    /* 範囲外なら再帰にも互除法にも入らずに終了する */
    if (n > 20) {
        fprintf(stderr, "n must be 0..20\n");
        return 1;
    }
    printf("%u! = %llu\n", n, factorial(n));
    printf("gcd=%u\n", gcd(48, 18));

    unsigned long long recursive = factorial(n);
    unsigned long long iterative = factorial_loop(n);
    printf("recursive=%llu loop=%llu equal=%d\n",
           recursive, iterative, recursive == iterative);
    return 0;
}
