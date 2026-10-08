// 第13回 発展2「共有変数の宣言」（SharedCount / main.c）
// counter.h の extern 宣言によって，counter.c で定義された total を使う。add_count を 2 回呼ぶので 2。
#include <stdio.h>
#include "counter.h"

int main(void)
{
    add_count();
    add_count();
    printf("total=%d\n", total);
    return 0;
}
