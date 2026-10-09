/* 第14回 発展1　再帰の呼び出し数（Fibonacci / fibonacci.c）
 * 演習ページの fibonacci.c。呼び出し回数と最大深さを Stats へのポインタで共有する。
 * input は main の初期値を書き換えて変える（0〜5，10，20，-1，21）。
 */
#include <stdio.h>

typedef struct {
    unsigned long long calls;
    unsigned int max_depth;
} Stats;

/* n は 0〜20，depth は最初の呼び出しで 1，stats は有効な Stats を指すことを前提とする */
unsigned long long fib(unsigned int n, unsigned int depth, Stats *stats)
{
    ++stats->calls;                    /* 基底条件の呼び出しも 1 回と数える */
    if (depth > stats->max_depth) {
        stats->max_depth = depth;
    }
    if (n < 2) {
        return n;
    }
    /* 文を分けて左 → 右の順序を明示する */
    unsigned long long left = fib(n - 1, depth + 1, stats);
    unsigned long long right = fib(n - 2, depth + 1, stats);
    return left + right;
}

/* 前の 2 項だけを保持する反復版（n は 0〜20 を前提とする） */
unsigned long long fib_loop(unsigned int n)
{
    unsigned long long a = 0;
    unsigned long long b = 1;
    for (unsigned int i = 0; i < n; ++i) {
        unsigned long long next = a + b;
        a = b;
        b = next;
    }
    return a;
}

int main(void)
{
    int input = 4;
    /* 再帰へ入る前に拒否する */
    if (input < 0 || input > 20) {
        fputs("n must be 0..20\n", stderr);
        return 1;
    }
    unsigned int n = (unsigned int)input;
    Stats stats = {0, 0};              /* 測定ごとに {0, 0} から始める */
    unsigned long long result = fib(n, 1, &stats);
    printf("fib=%llu calls=%llu depth=%u loop=%llu\n",
           result, stats.calls, stats.max_depth, fib_loop(n));
    return 0;
}
