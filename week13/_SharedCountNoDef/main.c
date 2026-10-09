// 第13回 発展2 変更1　定義を外す（_SharedCountNoDef / main.c）
// SharedCount と同じ内容。counter.h の extern 宣言によって total を使う（このフォルダでは定義がないのでリンクで失敗する）。
#include <stdio.h>
#include "counter.h"

int main(void)
{
    add_count();
    add_count();
    printf("total=%d\n", total);
    return 0;
}
