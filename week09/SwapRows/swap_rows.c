// 第9回 課題4　二次元配列の行を交換する（SwapRows / swap_rows.c）
// 3行9列の文字配列で，2行目と3行目の9個の char をすべて交換する。行の開始位置は変わらず，保存された内容が入れ替わる。
// 同じ行の交換・2回の交換・空文字列・終端までしか交換しない誤りなどは CMakeLists.txt の variant でテストする。
#include <stdio.h>

enum { ROWS = 3, WIDTH = 9 };

// 行 i と行 j の WIDTH 個の char を1個ずつ交換する。i, j は 0〜ROWS-1（同じ行でもよい）。
// 終端や初期化で0になった残りも含めて固定幅全体を交換するので，長さの違う文字列でも正しく入れ替わる
void swap_rows(char names[][WIDTH], int i, int j)
{
    for (int c = 0; c < WIDTH; ++c) {
        char temp = names[i][c];
        names[i][c] = names[j][c];
        names[j][c] = temp;
    }
}

// 各行の9要素を表示する（値0の char は 0 と表示）。続けて [ ] の中に文字列として表示する
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
    printf("before:\n");
    print_rows(names);
    swap_rows(names, 1, 2);
    printf("after:\n");
    print_rows(names);
    return 0;
}
