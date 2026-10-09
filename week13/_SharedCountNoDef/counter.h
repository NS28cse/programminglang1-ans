// 第13回 発展2 変更1　定義を外す（_SharedCountNoDef / counter.h）
// SharedCount と同じ宣言。実装側（counter.c）と利用側（main.c）が同じヘッダを読み，宣言を 1 か所にそろえる。
// このフォルダでは counter.c の定義を外したので，この宣言に対応する実体がなくリンクで失敗する。
#ifndef PL1_COUNTER_H
#define PL1_COUNTER_H
extern int total;       // 宣言だけ（このフォルダでは定義がどこにもない）
void add_count(void);
#endif
