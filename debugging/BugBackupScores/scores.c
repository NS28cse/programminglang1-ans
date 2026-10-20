// デバッグ題材: 点数の控え（第13回）
// Scores の確保・解放・表示・平均。
#include <stdio.h>
#include <stdlib.h>
#include "scores.h"

int scores_create(Scores *s, size_t count)
{
    s->data = calloc(count, sizeof *s->data);
    if (s->data == NULL) {
        s->count = 0;
        return 0;
    }
    s->count = count;
    return 1;
}

void scores_destroy(Scores *s)
{
    free(s->data);
    s->data = NULL;
    s->count = 0;
}

void scores_print(const Scores *s)
{
    for (size_t i = 0; i < s->count; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", s->data[i]);
    }
    printf("\n");
}

double scores_mean(const Scores *s)
{
    long long sum = 0;
    for (size_t i = 0; i < s->count; ++i) {
        sum += s->data[i];
    }
    return (double)sum / (double)s->count;
}
