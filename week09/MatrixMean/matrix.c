// 第9回 課題3　行ごとの平均（MatrixMean / matrix.c をもとにした最終版）
// 2行3列，値は0〜100，列数は COLS=3 に固定。表の4ケース，sizeof の確認，全体平均を順に表示する。
#include <stdio.h>

enum { ROWS = 2, COLS = 3 };

/* 先頭 rows 行の行平均を表示する。rows は 0〜実際の行数（rows=0 なら何も表示しない）。
   a は「int が COLS 個の行」へのポインタ。関数内の sizeof a はポインタの大きさなので行数は rows で受け取る */
void print_means(int (*a)[COLS], int rows)
{
    for (int r = 0; r < rows; ++r) {
        int total = 0;
        for (int c = 0; c < COLS; ++c) {
            total += a[r][c];
        }
        double mean = (double)total / COLS;  /* total / COLS だと整数除算になり小数部分が失われる */
        printf("row%d mean=%.2f\n", r, mean);
    }
}

/* 全要素の平均を *mean へ書いて1を返す。rows<=0 は平均が定義できないので0を返す（*mean は変更しない） */
int overall_mean(int (*a)[COLS], int rows, double *mean)
{
    if (rows <= 0) { return 0; }
    double sum = 0.0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < COLS; ++c) {
            sum += a[r][c];
        }
    }
    *mean = sum / ((double)rows * COLS);
    return 1;
}

void print_overall(int (*a)[COLS], int rows)
{
    double mean = 0.0;
    if (overall_mean(a, rows, &mean)) {
        printf("overall rows=%d: mean=%.2f\n", rows, mean);
    } else {
        printf("overall rows=%d: undefined\n", rows);
    }
}

int main(void)
{
    int a[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}};
    int low_high[ROWS][COLS] = {{0, 0, 0}, {100, 100, 100}};
    int fraction[ROWS][COLS] = {{1, 1, 2}, {2, 2, 3}};

    printf("{1, 2, 3}, {4, 5, 6} rows=2:\n");
    print_means(a, 2);
    printf("{1, 2, 3}, {4, 5, 6} rows=1:\n");
    print_means(a, 1);
    printf("{0, 0, 0}, {100, 100, 100} rows=2:\n");
    print_means(low_high, 2);
    printf("{1, 1, 2}, {2, 2, 3} rows=2:\n");
    print_means(fraction, 2);
    printf("{1, 2, 3}, {4, 5, 6} rows=0:\n");
    print_means(a, 0);

    /* main の実際の配列に対する sizeof（バイト数は処理系依存なので式で比べる） */
    printf("sizeof a == 2 * COLS * sizeof(int): %d\n", sizeof a == 2 * COLS * sizeof(int));
    printf("sizeof a[0] == COLS * sizeof(int): %d\n", sizeof a[0] == COLS * sizeof(int));
    printf("sizeof a / sizeof a[0] = %zu\n", sizeof a / sizeof a[0]);
    printf("sizeof a[0] / sizeof a[0][0] = %zu\n", sizeof a[0] / sizeof a[0][0]);

    print_overall(a, 2);
    print_overall(a, 0);
    return 0;
}
