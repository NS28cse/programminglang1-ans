// 第4回 課題2 偶数の合計（EvenSum / even_sum.c）
// 1 から n までの偶数の合計を for 文で求める．n は 0〜100 の固定値．
#include <stdio.h>

int main(void)
{
    int n = 10;     // 入力の代わりの固定値（0, 1, 2, 4, 100 に変えて確かめる）
    int sum = 0;    // それまでの合計．ループの前で 1 回だけ 0 にする

    for (int i = 1; i <= n; ++i) {      // i は今調べている数
        if (i % 2 == 0) {               // 偶数のときだけ加算する
            sum += i;
        }
    }
    printf("%d\n", sum);
    return 0;
}
