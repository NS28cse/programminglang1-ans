// 第13回 課題3「失敗を模擬する」（NewPointFail / new_point.c）
// NewPoint のコピー。new_point の malloc だけを試験用の point_allocate に置き換え，
// simulate_failure = 1 で確保失敗の経路（NULL を返し，main が診断を出して終了）を確かめる。
// 正常版は NewPoint フォルダに残してある。
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

// 試験用の確保関数：simulate_failure が 1 なら malloc を呼ばずに NULL を返す（errno は設定しない）
static void *point_allocate(size_t bytes)
{
    const int simulate_failure = 1;
    if (simulate_failure) {
        return NULL;
    }
    return malloc(bytes);
}

// 成功なら初期化済みの Point を返し，呼び出し元が free する．失敗なら NULL を返す．
Point *new_point(double x, double y)
{
    Point *p = point_allocate(sizeof *p);
    if (p == NULL) {
        return NULL;            // 失敗時はメンバに触れない
    }
    *p = (Point){.x = x, .y = y};
    return p;
}

int main(void)
{
    Point *p = new_point(3.0, 4.0);
    if (p == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;               // この後で p->x へアクセスしない
    }
    printf("x=%.1f y=%.1f\n", p->x, p->y);
    free(p);
    p = NULL;
    return 0;
}
