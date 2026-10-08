// 第2回 課題1 長方形の面積と再計算（Rectangle / rectangle.c）
// area に保存されるのは式ではなく，計算した時点の値であることを確かめる
#include <stdio.h>

int main(void)
{
    int height = 7;
    int width = 4;
    int area = height * width;      // この時点の積 28 を保存する

    printf("first=%d\n", area);

    width = 6;                      // width だけが変わり，area は 28 のまま
    printf("before recalculation=%d\n", area);

    area = height * width;          // 既にある area へ代入し直す（int は付けない）
    printf("after recalculation=%d\n", area);
    return 0;
}
