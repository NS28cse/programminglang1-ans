/* 第14回 課題1　呼び出し回数と最大深さを数える（Factorial / versions/factorial_count.c）
 * factorial の呼び出し回数と最大深さを数え，0〜20 で反復版と一致することを確かめる。
 * 回数と最大深さは fibonacci.c と同じく Stats へのポインタで渡し，測定ごとに {0, 0} から始める。
 * 最初の factorial を深さ 1 と数え，main は数えない。
 */
#include <stdio.h>

typedef struct {
    unsigned long long calls;
    unsigned int max_depth;
} Stats;

/* n は 0〜20，depth は最初の呼び出しで 1，stats は有効な Stats を指すことを前提とする */
unsigned long long factorial(unsigned int n, unsigned int depth, Stats *stats)
{
    ++stats->calls;                    /* 基底条件の呼び出しも 1 回と数える */
    if (depth > stats->max_depth) {
        stats->max_depth = depth;
    }
    if (n == 0) { return 1; }
    return n * factorial(n - 1, depth + 1, stats);
}

unsigned long long factorial_loop(unsigned int n)
{
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main(void)
{
    unsigned int list[] = {0, 1, 5, 20};
    for (int i = 0; i < 4; ++i) {
        Stats stats = {0, 0};          /* 測定ごとに {0, 0} から始める */
        unsigned long long r = factorial(list[i], 1, &stats);
        printf("n=%u result=%llu calls=%llu depth=%u\n", list[i], r, stats.calls, stats.max_depth);
    }
    int all = 1;
    for (unsigned int n = 0; n <= 20; ++n) {
        Stats stats = {0, 0};
        if (factorial(n, 1, &stats) != factorial_loop(n)) {
            all = 0;
            printf("differ at %u\n", n);
        }
    }
    printf("0..20 all equal=%d\n", all);
    return 0;
}
