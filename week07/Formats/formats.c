// 第7回 課題4　printf の幅と書式を確かめる（Formats / formats.c）
// 演習ページのコード。printf の幅・精度・基数・長さ修飾子による表示を確かめる（入力は待たない）。
#include <stdio.h>
int main(void)
{
    int n = 3;
    double value = 154.423;
    unsigned int base = 500u;
    long long big = 5000000000LL; // int に入らない値なので long long と %lld を使う
    printf("|%d|%5d|\n", n, n);
    printf("|%f|%.2f|%8.2f|\n", value, value, value);
    printf("|%e|%g|\n", 1.3e10, 1.3e10);
    printf("%u %o %x\n", base, base, base);
    printf("%lld\n", big);
    return 0;
}
