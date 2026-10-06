// 第5回 課題2 補足　三次元配列の添字（Array3D / array3d.c）
// int data[2][3][4] の最後の要素 data[1][2][3] へ 7 を代入して表示し，総要素数も確かめる。
#include <stdio.h>

int main(void)
{
    int data[2][3][4] = {0};  // 添字の範囲は 0〜1，0〜2，0〜3。総要素数は 2*3*4 = 24
    data[1][2][3] = 7;        // 各次元の最大の添字（要素数 - 1）を並べたものが最後の要素
    printf("last=%d count=%zu\n", data[1][2][3],
           sizeof data / sizeof data[0][0][0]);
    return 0;
}
