// 第9回 課題3　行ごとの平均（MatrixMean / matrix.c）。本体: 例題 matrix.c をもとに演習ページの指示をすべて反映した版
// 2行3列，値は0〜100，列数は COLS=3 に固定。表の入力・sizeof の確認・全体平均は CMakeLists.txt の variant でテストする。
#include <stdio.h>
enum { ROWS = 2, COLS = 3 };
// 先頭 rows 行の行平均を表示する。rows は 0〜実際の行数（rows=0 なら何も表示しない）。
// a は「int が COLS 個の行」へのポインタ。関数内の sizeof a はポインタの大きさなので行数は rows で受け取る
void print_means(int (*a)[COLS], int rows)
{
    for (int r = 0; r < rows; ++r) {
        int total = 0;
        for (int c = 0; c < COLS; ++c) {
            total += a[r][c];
        }
        double mean = (double)total / COLS;  // total / COLS だと整数除算になり小数部分が失われる
        printf("row%d mean=%.2f\n", r, mean);
    }
}
int main(void)
{
    int a[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}};
    print_means(a, ROWS);
    return 0;
}
