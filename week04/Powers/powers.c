// 第4回 課題4 100 未満の 2 の累乗：for 版（Powers / powers.c）
// 回数ではなく値で継続を決める．power は 1 から始めて 2 倍ずつ更新し，limit 未満の間だけ表示する．
#include <stdio.h>

int main(void)
{
    int limit = 100;    // 1〜100 に限定する（最後の更新でも 128 以下なので int に収まる）

    for (int power = 1; power < limit; power *= 2) {
        printf("%d, ", power);
    }
    printf("\n");       // 改行はループの後で 1 回だけ
    return 0;
}
