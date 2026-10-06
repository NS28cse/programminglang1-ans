/* 第14回 課題4 再帰の入口を安全にする（CheckedFactorial）
 * 入口 factorial_checked で検査し，再帰は内部関数 factorial_impl だけで行う。
 * n は引数で変えられる（引数なしなら 5）。例: CheckedFactorial -1
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>

/* 内部関数: n は 0〜20 を前提とする（検査は入口で済んでいる） */
static unsigned long long factorial_impl(unsigned int n)
{
    if (n == 0) { return 1; }
    return n * factorial_impl(n - 1);
}

/* n が 0〜20 で out が NULL でなければ *out に n! を保存して 1 を返す。
 * それ以外は 0 を返し，*out は変更しない。NULL 以外の out は有効な
 * unsigned long long を指すことを呼び出し側が保証する */
int factorial_checked(int n, unsigned long long *out)
{
    if (out == NULL || n < 0 || n > 20) {
        return 0;                      /* 不正な値では再帰へ入らない */
    }
    *out = factorial_impl((unsigned int)n); /* 負数を拒否してから unsigned へ変換する */
    return 1;
}

int main(int argc, char *argv[])
{
    long input = 5;
    if (argc > 2) {
        fprintf(stderr, "usage: CheckedFactorial [n]\n");
        return 1;
    }
    if (argc == 2) {
        char *end;
        errno = 0;
        input = strtol(argv[1], &end, 10);
        if (argv[1] == end || *end != '\0' || errno == ERANGE ||
            input < INT_MIN || input > INT_MAX) {
            fprintf(stderr, "n must be an int\n");
            return 1;
        }
    }
    int n = (int)input;
    unsigned long long result = 99;    /* 失敗時に変更されないことを確かめる目印 */
    int ok = factorial_checked(n, &result);
    printf("ok=%d result=%llu\n", ok, result);
    printf("null: ok=%d\n", factorial_checked(n, NULL)); /* out が NULL なら常に 0 */
    return 0;
}
