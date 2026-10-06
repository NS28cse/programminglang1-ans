// 第13回 発展2（_SharedCountNoDef / counter.h）：SharedCount と同じ内容（変更していないファイル）
// 実装側（counter.c）と利用側（main.c）が同じヘッダを読み，宣言を 1 か所にそろえる。
#ifndef PL1_COUNTER_H
#define PL1_COUNTER_H
extern int total;       // 宣言だけ（定義は counter.c に 1 つ）
void add_count(void);
#endif
