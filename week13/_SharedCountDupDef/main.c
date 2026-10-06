// 第13回 発展2　変更2（_SharedCountDupDef / main.c）：意図的なリンクエラー（ビルドしない）
// counter.c の定義を戻したうえで，main 側にも同じ定義を書いた。外部リンケージの total が
// 2 つの翻訳単位で定義されるため，リンクで「シンボルの多重定義」になる。
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
