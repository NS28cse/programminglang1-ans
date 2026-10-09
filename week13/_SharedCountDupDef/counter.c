// 第13回 発展2 変更2　定義を重複させる（_SharedCountDupDef / counter.c）
// SharedCount と同じ内容。total の定義（実体）を置く。外部リンケージ・静的記憶期間を持つ。
#include "counter.h"
int total = 0;
void add_count(void)
{
    ++total;
}
