/* 第14回 課題3 互除法を反復へ書き換える（GcdLoop）
 * 反復版 gcd_loop と再帰版 gcd を並べて比較する。
 * a と b は引数で変えられる（引数なしなら 48 18）。例: GcdLoop 18 48
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

/* text 全体が 0〜INT_MAX の整数なら *out に保存して 1 を返す */
int parse_value(const char *text, unsigned int *out)
{
    char *end;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (text == end || *end != '\0' || errno == ERANGE ||
        value < 0 || value > INT_MAX) {
        return 0;
    }
    *out = (unsigned int)value;
    return 1;
}

int main(int argc, char *argv[])
{
    unsigned int a = 48;
    unsigned int b = 18;
    if (argc != 1 && argc != 3) {
        fprintf(stderr, "usage: GcdLoop [a b]\n");
        return 1;
    }
    if (argc == 3 && (!parse_value(argv[1], &a) || !parse_value(argv[2], &b))) {
        fprintf(stderr, "a and b must be integers from 0 to %d\n", INT_MAX);
        return 1;
    }
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
