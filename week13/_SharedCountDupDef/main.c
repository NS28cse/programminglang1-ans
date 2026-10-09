// 第13回 発展2 変更2　定義を重複させる（_SharedCountDupDef / main.c）
// counter.c の定義を戻したうえで，main 側にも同じ定義 int total = 0; を書いた版。外部リンケージの total が
// 2 つの翻訳単位で定義されるため，リンクで「シンボルの多重定義」になる（意図的なリンクエラー）。
#include <stdio.h>
#include "counter.h"
int total = 0;

int main(void)
{
    add_count();
    add_count();
    printf("total=%d\n", total);
    return 0;
}
