/* 第3回 確認問題7 ビットごとの AND と論理 AND（Flags / versions/and_vs_logical_and.c）
 * 4u & 2u と 4u && 2u の値を並べて表示する。
 */
#include <stdio.h>

int main(void)
{
    /* 定数のまま 4u && 2u と書くと Clang が -Wconstant-logical-operand の警告を出すので，変数に入れる */
    unsigned int a = 4u;  /* 100 */
    unsigned int b = 2u;  /* 010 */
    /* & は共通の 1 のビットがないので 0，&& はどちらも 0 でない（真）ので 1 */
    printf("%u %d\n", a & b, a && b);
    return 0;
}
