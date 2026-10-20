// 第4回 課題3　別解：1 列目を内側のループの前に表示し，2 列目からは区切りを前に付けて表示する（Table / versions/table_first_col.c）
// 「最後の列か」を調べる if がなくなり，列の数は内側の for の上限 1 か所だけで決まる．
#include <stdio.h>

int main(void)
{
    for (int row = 1; row <= 3; ++row) {
        printf("%2d", row);                     // 1 列目（row × 1）は前に区切りを付けない
        for (int col = 2; col <= 3; ++col) {    // 2 列目から
            printf(" %2d", row * col);          // 区切りの空白を数の前に付ける
        }
        printf("\n");
    }
    return 0;
}
