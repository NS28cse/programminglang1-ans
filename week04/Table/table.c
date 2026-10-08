// 第4回 課題3 小さな掛け算表（Table）
// 外側の for を行 row，内側の for を列 col として 1〜3 の掛け算表を表示する．
#include <stdio.h>

int main(void)
{
    for (int row = 1; row <= 3; ++row) {
        for (int col = 1; col <= 3; ++col) {   // 行が変わるたびに col は 1 から始まる
            printf("%2d", row * col);
            if (col < 3) {                      // 列の間だけ区切りを入れ，行末には付けない
                printf(" ");
            }
        }
        printf("\n");                           // 内側のループが終わった後に 1 回だけ改行する
    }
    return 0;
}
