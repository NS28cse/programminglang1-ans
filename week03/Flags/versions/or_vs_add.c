/* 第3回 課題5（発展） OR と加算の比較（Flags / versions/or_vs_add.c）
 * 同じビットを OR で重ねた値（1u | 1u）と加算した値（1u + 1u）を並べて表示する。
 */
#include <stdio.h>

int main(void)
{
    /* 001 + 001 は桁上がりして 010（2），001 | 001 は 001（1）のまま */
    printf("%u %u\n", 1u + 1u, 1u | 1u);
    return 0;
}
