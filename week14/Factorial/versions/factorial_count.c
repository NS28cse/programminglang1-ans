/* 第14回 課題1 Factorial の確認用（本体には含めない）
 * factorial の呼び出し回数と最大深さを数え，0〜20 で反復版と一致することを確かめる。
 * 最初の factorial を深さ 1 と数え，main は数えない。
 */
#include <stdio.h>

unsigned long long calls;              /* 測定ごとに 0 に戻す */
unsigned int max_depth;

/* n は 0〜20，depth は最初の呼び出しで 1 を前提とする */
unsigned long long factorial(unsigned int n, unsigned int depth)
{
    ++calls;
    if (depth > max_depth) {
        max_depth = depth;
    }
    if (n == 0) { return 1; }
    return n * factorial(n - 1, depth + 1);
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
        calls = 0;
        max_depth = 0;
        unsigned long long r = factorial(list[i], 1);
        printf("n=%u result=%llu calls=%llu depth=%u\n", list[i], r, calls, max_depth);
    }
    int all = 1;
    for (unsigned int n = 0; n <= 20; ++n) {
        if (factorial(n, 1) != factorial_loop(n)) {
            all = 0;
            printf("differ at %u\n", n);
        }
    }
    printf("0..20 all equal=%d\n", all);
    return 0;
}
