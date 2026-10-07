// 第13回 発展2（_SharedCountNoDef / main.c）：SharedCount と同じ内容（変更していないファイル）
// counter.h の extern 宣言によって total を使う（このフォルダでは counter.c の定義を外したのでリンクで失敗する）。
#include <stdio.h>
#include "counter.h"

int main(void)
{
    add_count();
    add_count();
    printf("total=%d\n", total);
    return 0;
}
