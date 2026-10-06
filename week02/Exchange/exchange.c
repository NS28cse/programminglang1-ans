// 第2回 課題3 値のコピーと交換（Exchange / exchange.c）
// a = b; で a の元の値が失われるので，先に temp へ保存してから交換する
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 20;

    printf("before: a=%d b=%d\n", a, b);

    int temp = a;                   // 上書きされる前の a の値を保存する
    a = b;
    b = temp;

    printf("after: a=%d b=%d\n", a, b);
    return 0;
}
