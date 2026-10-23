// デバッグ題材: 行ごとの合計（第5回）
// 3 行 3 列の表 table について，行ごとの合計を「row 行番号: 合計」の形で表示する。
#include <stdio.h>

enum { ROWS = 3, COLS = 3 };

int main(void)
{
    int table[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int sum = 0;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            sum += table[row][col];
        }
        printf("row %d: %d\n", row, sum);
    }
    return 0;
}
