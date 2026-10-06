// 第13回 発展2（_SharedCountDupDef / counter.c）：SharedCount と同じ内容（変更していないファイル）
// total の定義（実体）はこのファイルに 1 つだけ置く。外部リンケージ・静的記憶期間を持つ。
#include "counter.h"
int total = 0;
void add_count(void)
{
    ++total;
}
