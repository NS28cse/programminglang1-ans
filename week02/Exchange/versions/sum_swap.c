// 第2回 課題3　別解：一時変数を使わず，足し算と引き算で交換する（Exchange / versions/sum_swap.c）
// a に 2 つの値の和を入れておき，和から b を引けば元の a，和から元の a を引けば元の b が取り出せる。
// a + b が int の範囲を超える初期値では正しく動かない（本体の temp を使う方法を勧める）
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 20;

    printf("before: a=%d b=%d\n", a, b);

    a = a + b;                      // a は和の 30。元の a の値は和の中に残っている
    b = a - b;                      // 30 - 20 = 10（元の a）
    a = a - b;                      // 30 - 10 = 20（元の b）

    printf("after: a=%d b=%d\n", a, b);
    return 0;
}
