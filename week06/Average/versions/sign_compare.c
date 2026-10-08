// 第6回 課題3 符号の異なる比較の確認用（Average の versions/sign_compare.c。本体とは別にテストする）
// int の -10 と unsigned int の 10u を < で比べる。i が unsigned int（4294967286）に変換されるので結果は 0。
// 警告が出る書き方をわざと示す版なので，その警告だけ CMakeLists.txt で抑止している（README 参照）。
#include <stdio.h>

int main(void)
{
    int i = -10;
    unsigned int u = 10u;
    // 通常の算術型変換で i が unsigned int に変換されてから比べるので偽（0）
    printf("%d\n", i < u);
    return 0;
}
