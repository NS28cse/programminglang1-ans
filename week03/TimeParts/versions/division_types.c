/* 第3回 確認問題2・3 整数除算と浮動小数点の除算の比較（TimeParts の比較用） */
#include <stdio.h>

int main(void)
{
    /* int 同士は整数除算で 3，一方が double なら浮動小数点の除算で 3.5 */
    printf("%d %.1f\n", 7 / 2, 7 / 2.0);

    /* 右辺が int 同士で先に 3 になり，代入で 3.0 に変換される（0.5 は戻らない） */
    double x = 7 / 2;
    printf("%.1f\n", x);
    return 0;
}
