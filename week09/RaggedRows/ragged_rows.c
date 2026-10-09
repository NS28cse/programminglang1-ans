// 第9回 発展1　長さが異なる行を扱う（RaggedRows / ragged_rows.c）
// 配列本体（row0, row1），先頭を集めたポインタ配列（rows），長さの配列（lengths）の3種類を区別する。
#include <stdio.h>

int main(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int *rows[] = {row0, row1};  // 行の先頭アドレスを集めただけで，内容はコピーしない
    int lengths[] = {3, 2};      // 長さは型に含まれないので別に管理する
    int **p = rows;
    for (int r = 0; r < 2; ++r) {
        int sum = 0;
        for (int c = 0; c < lengths[r]; ++c) {
            sum += p[r][c];
        }
        printf("row%d sum=%d\n", r, sum);
    }
    p[1][0] = 40;  // p[1] は row1 を指すので row1[0] が変わる
    printf("original=%d\n", row1[0]);
    return 0;
}
