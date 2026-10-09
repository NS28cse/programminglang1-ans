// 第6回 課題3 変換する順序（Average / average.c）
// 演習ページの「完全なプログラム」。整数拡張・積の型・往復変換・符号なしへの変換を確かめる。
#include <stdio.h>
int main(void)
{
    // char は計算の前に int へ整数拡張されるので，途中の 1000 も int で計算する
    char c1 = 10, c2 = 100, c3 = 20;
    int promoted = c1 * c2 / c3;
    // 掛ける前に long long へ広げる（i * i を int のまま計算するとオーバーフローする）
    int i = 50000;
    long long square = (long long)i * i;
    // char -> int -> char は値を保つ
    char original = 'A';
    int saved = original;
    char restored = (char)saved;
    // 符号なしへの変換は 256 を法とする値になり，失った情報は戻らない。
    // 演習ページの (unsigned char)300 は定数を切り詰めるキャストで MSVC /W4 の C4310 になるため，
    // 300 をいったん int の変数に入れてから変換する（結果は同じ 44）
    int large = 300;
    unsigned char small = (unsigned char)large;
    printf("promoted=%d\n", promoted);
    printf("square=%lld\n", square);
    printf("roundtrip=%d\n", original == restored);
    printf("unsigned=%u\n", (unsigned int)small);
    return 0;
}
