// デバッグ題材: 点数の控え（第13回）
// 動的に確保した点数の配列を持つ構造体 Scores と，その操作。
#ifndef SCORES_H
#define SCORES_H

#include <stddef.h>

typedef struct {
    size_t count;
    int *data;   // count 個の int を指す（scores_create が確保し，scores_destroy が解放する）
} Scores;

// count（1 以上）個の int を確保して 0 で初期化する。成功なら 1，失敗なら 0 を返す
int scores_create(Scores *s, size_t count);
// data を解放し，data を NULL，count を 0 にする
void scores_destroy(Scores *s);
// 点数を「70 85 90」の形で 1 行に表示する
void scores_print(const Scores *s);
// 平均を返す（count は 1 以上）
double scores_mean(const Scores *s);

#endif
