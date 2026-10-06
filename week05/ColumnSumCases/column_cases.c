// 第5回 課題2 の検証用（ColumnSumCases / column_cases.c）
// 演習ページで試す 3 つの table について，ColumnSum と同じ二重ループで列ごとの合計を表示する。
// 3 つの table は同じ 2 行 3 列なので，三次元配列 tables[3][2][3] にまとめて順に処理する。
#include <stdio.h>

enum { CASES = 3, ROWS = 2, COLS = 3 };

int main(void)
{
    int tables[CASES][ROWS][COLS] = {
        {{1, 2, 3}, {4, 5, 6}},  // 元の table
        {{1, 1, 1}, {2, 2, 2}},  // 各列が 3
        {{0}},                   // 残りの要素も 0 になる
    };
    for (int t = 0; t < CASES; ++t) {
        printf("table %d\n", t);
        for (int col = 0; col < COLS; ++col) {
            int sum = 0;
            for (int row = 0; row < ROWS; ++row) {
                sum += tables[t][row][col];
            }
            printf("col %d: %d\n", col, sum);
        }
    }
    return 0;
}
