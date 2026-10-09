// 第6回 課題3 符号の異なる比較（Average / versions/sign_compare.c）
// int の -10 と unsigned int の 10u を < で比べる。i が unsigned int（4294967286）に変換されるので結果は 0。
// 符号の異なる比較の警告（GCC/Clang の -Wsign-compare，MSVC の C4018）が出る書き方をわざと示している。
#include <stdio.h>

int main(void)
{
    int i = -10;
    unsigned int u = 10u;
    // 通常の算術型変換で i が unsigned int に変換されてから比べるので偽（0）
    printf("%d\n", i < u);
    return 0;
}
