// デバッグ題材: 呼び出し回数を数える（第12回）
// count_call の定義。呼ばれるたびに call_count を 1 増やす。
#include "counter.h"

void count_call(void)
{
    ++call_count;
}
