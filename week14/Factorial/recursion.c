/* 第14回 課題1 階乗の境界（Factorial）
 * 講義の recursion.c に，反復版 factorial_loop との比較を追加した版。
 * n は引数で変えられる（引数なしなら講義と同じ 5）。例: Factorial 20
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

int main(int argc, char *argv[])
{
    long input = 5;
    if (argc > 2) {
        fprintf(stderr, "usage: Factorial [n]\n");
        return 1;
    }
    if (argc == 2) {
        char *end;
        errno = 0;
        input = strtol(argv[1], &end, 10);
        if (argv[1] == end || *end != '\0' || errno == ERANGE) {
            input = -1;                /* 整数でなければ下の範囲検査で拒否する */
        }
    }
    /* 範囲外なら再帰にも互除法にも入らずに終了する */
    if (input < 0 || input > 20) {
        fprintf(stderr, "n must be 0..20\n");
        return 1;
    }
    unsigned int n = (unsigned int)input;
    printf("%u! = %llu\n", n, factorial(n));
    printf("gcd=%u\n", gcd(48, 18));

    unsigned long long recursive = factorial(n);
    unsigned long long iterative = factorial_loop(n);
    printf("recursive=%llu loop=%llu equal=%d\n",
           recursive, iterative, recursive == iterative);
    return 0;
}
