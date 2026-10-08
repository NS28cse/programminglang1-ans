// 第6回 課題3 変換する順序（Average）の最初の版：キャストの位置と (int)-3.9 を比べる
// 本体 average.c は演習ページの「完全なプログラム」。この版は CMakeLists.txt の variant（first など）でテストする。
#include <stdio.h>
int main(void)
{
    int total = 7, count = 2;
    printf("%.1f\n", (double)(total / count));
    printf("%.1f\n", (double)total / count);
    printf("%d\n", (int)-3.9);
    return 0;
}
