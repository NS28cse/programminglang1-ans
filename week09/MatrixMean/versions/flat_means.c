// 第9回 課題3　別解：一次元の配列に行の順に並べ，添字 r * cols + c で読む（MatrixMean / versions/flat_means.c）
// 列数を型ではなく引数 cols で渡すので，同じ関数で列数の違う行列も扱える。代わりに添字の計算は自分で正しく書く。
#include <stdio.h>
enum { ROWS = 2, COLS = 3 };
// 一次元の配列 a を rows 行 cols 列の行列として読み，先頭 rows 行の行平均を表示する。
// 契約: rows は 0 以上，cols は 1 以上で，a には rows * cols 個以上の要素があること（rows=0 なら何も表示しない）
void print_means(const int a[], int rows, int cols)
{
    for (int r = 0; r < rows; ++r) {
        int total = 0;
        for (int c = 0; c < cols; ++c) {
            total += a[r * cols + c];  // 行 r の先頭は r * cols 番目
        }
        double mean = (double)total / cols;  // total / cols だと整数除算になり小数部分が失われる
        printf("row%d mean=%.2f\n", r, mean);
    }
}
int main(void)
{
    int flat[ROWS * COLS] = {1, 2, 3, 4, 5, 6};  // 1 行目が flat[0]〜flat[2]，2 行目が flat[3]〜flat[5]
    print_means(flat, ROWS, COLS);
    return 0;
}
