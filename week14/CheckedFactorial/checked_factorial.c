/* 第14回 課題4 再帰の入口を安全にする（CheckedFactorial）
 * 入口 factorial_checked で検査し，再帰は内部関数 factorial_impl だけで行う。
 * n は main の初期値を書き換えて変える（0，1，5，20，-1，21）。
 */
#include <stdio.h>
#include <stddef.h>

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

int main(void)
{
    int n = 5;
    unsigned long long result = 99;    /* 失敗時に変更されないことを確かめる目印 */
    int ok = factorial_checked(n, &result);
    printf("ok=%d result=%llu\n", ok, result);
    return 0;
}
