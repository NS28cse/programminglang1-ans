// デバッグ題材: 点数の控え（第13回）
// 今日の点数 today の控え backup を作る。today を解放した後も backup は使えるようにし，
// backup の点数と平均を表示してから backup も解放する。
#include <stdio.h>
#include "scores.h"

int main(void)
{
    Scores today;
    if (!scores_create(&today, 3)) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    today.data[0] = 70;
    today.data[1] = 85;
    today.data[2] = 90;

    Scores backup = today;
    scores_destroy(&today);

    printf("backup: ");
    scores_print(&backup);
    printf("mean=%.1f\n", scores_mean(&backup));
    scores_destroy(&backup);
    return 0;
}
