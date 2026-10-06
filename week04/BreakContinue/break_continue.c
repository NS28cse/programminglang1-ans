// 第4回 発展 途中で飛ばす処理（演習ページの断片を main に入れたもの．プロジェクト名は解答で付けた）
// i == 2 では残りを飛ばして更新 ++i へ進み，i == 4 ではループを抜ける．
#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 6; ++i) {
        if (i == 2) {
            continue;
        }
        if (i == 4) {
            break;
        }
        printf("%d\n", i);
    }
    return 0;
}
