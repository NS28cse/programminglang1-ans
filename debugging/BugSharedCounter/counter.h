// デバッグ題材: 呼び出し回数を数える（第12回）
// count_call を呼ぶたびに呼び出し回数 call_count を 1 増やす。call_count は main.c からも読む。
#ifndef COUNTER_H
#define COUNTER_H

static int call_count = 0;

void count_call(void);

#endif
