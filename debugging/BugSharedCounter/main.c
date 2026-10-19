// デバッグ題材: 呼び出し回数を数える（第12回）
// count_call を 3 回呼んでから，呼び出し回数 call_count を表示する。
#include <stdio.h>
#include "counter.h"

int main(void)
{
    for (int i = 0; i < 3; ++i) {
        count_call();
    }
    printf("calls=%d\n", call_count);
    return 0;
}
