// 第13回 発展2 変更2　定義を重複させる（_SharedCountDupDef / counter.h）
// SharedCount と同じ内容。
// 実装側（counter.c）と利用側（main.c）が同じヘッダを読み，宣言を 1 か所にそろえる。
#ifndef PL1_COUNTER_H
#define PL1_COUNTER_H
extern int total;       // 宣言だけ（定義は counter.c に 1 つ）
void add_count(void);
#endif
