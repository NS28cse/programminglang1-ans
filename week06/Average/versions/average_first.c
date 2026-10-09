// 第6回 課題3 変換する順序の最初の版（Average / versions/average_first.c）
// 整数除算の後と前でキャストの位置を変えた 2 つの式と，(int)-3.9 の切り捨てを比べる。
#include <stdio.h>
int main(void)
{
    int total = 7, count = 2;
    printf("%.1f\n", (double)(total / count));
    printf("%.1f\n", (double)total / count);
    printf("%d\n", (int)-3.9);
    return 0;
}
