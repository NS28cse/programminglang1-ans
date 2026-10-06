// 第5回 ウォームアップ　初期化を読む（Warmup05 / warmup.c）
// 初期化子を書いた配列では，書かなかった残りの要素が 0 になることを表示で確かめる。
#include <stdio.h>

int main(void)
{
    int a[5] = {1, 1};  // {1, 1, 0, 0, 0}
    int b[5] = {0};     // {0, 0, 0, 0, 0}
    for (int i = 0; i < 5; ++i) {
        printf("%d %d\n", a[i], b[i]);
    }
    return 0;
}
