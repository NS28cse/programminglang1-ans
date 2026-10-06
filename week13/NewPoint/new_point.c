// 第13回 課題3　構造体を確保する関数（NewPoint / new_point.c）
// new_point が Point を 1 個動的確保して初期化し，所有権を呼び出し元（main）へ渡す。
// main は NULL を検査し，成功時だけ両メンバを表示してから解放する。
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

// 成功なら初期化済みの Point を返し，呼び出し元が free する．失敗なら NULL を返す．
Point *new_point(double x, double y)
{
    Point *p = malloc(sizeof *p);
    if (p == NULL) {
        return NULL;            // 失敗時はメンバに触れない
    }
    *p = (Point){.x = x, .y = y};   // 左辺は p ではなく本体の *p
    return p;                   // p の寿命は終わるが，本体は free まで有効
}

int main(void)
{
    Point *p = new_point(3.0, 4.0);
    if (p == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    printf("x=%.1f y=%.1f\n", p->x, p->y);
    free(p);                    // 所有者の main が解放する
    p = NULL;
    return 0;
}
