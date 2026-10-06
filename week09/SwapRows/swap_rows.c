// 第9回 課題4　二次元配列の行を交換する（SwapRows / swap_rows.c）
// 3行9列の文字配列で，行の9個の char をすべて交換する。行の開始位置は変わらず，保存された内容が入れ替わる。
// 各ケースは初期状態の別の配列で試す。
#include <stdio.h>

enum { ROWS = 3, WIDTH = 9 };

/* 行 i と行 j の WIDTH 個の char を1個ずつ交換する。i, j は 0〜ROWS-1（同じ行でもよい）。
   終端や初期化で0になった残りも含めて固定幅全体を交換するので，長さの違う文字列でも正しく入れ替わる */
void swap_rows(char names[][WIDTH], int i, int j)
{
    for (int c = 0; c < WIDTH; ++c) {
        char temp = names[i][c];
        names[i][c] = names[j][c];
        names[j][c] = temp;
    }
}

/* 各行の9要素を表示する（値0の char は 0 と表示）。続けて文字列として表示する */
void print_rows(char names[][WIDTH])
{
    for (int r = 0; r < ROWS; ++r) {
        printf("%d:", r);
        for (int c = 0; c < WIDTH; ++c) {
            if (names[r][c] == '\0') {
                printf(" 0");
            } else {
                printf(" %c", names[r][c]);
            }
        }
        printf("  [%s]\n", names[r]);
    }
}

int main(void)
{
    char names[ROWS][WIDTH] = {"toyama", "ishikawa", "fukui"};
    char *row1 = names[1];  /* 2行目の開始位置。交換しても変わらない */
    printf("before:\n");
    print_rows(names);
    swap_rows(names, 1, 2);
    printf("after swap_rows(names, 1, 2):\n");
    print_rows(names);
    printf("row1 == names[1]: %d, row1 = %s\n", row1 == names[1], row1);

    char same[ROWS][WIDTH] = {"toyama", "ishikawa", "fukui"};
    swap_rows(same, 1, 1);
    printf("after swap_rows(same, 1, 1):\n");
    print_rows(same);

    char twice[ROWS][WIDTH] = {"toyama", "ishikawa", "fukui"};
    swap_rows(twice, 1, 2);
    swap_rows(twice, 1, 2);
    printf("after swap_rows(twice, 1, 2) x2:\n");
    print_rows(twice);

    char empty[ROWS][WIDTH] = {"toyama", "ishikawa", ""};
    swap_rows(empty, 1, 2);
    printf("after swap_rows(empty, 1, 2) with \"\":\n");
    print_rows(empty);
    return 0;
}
