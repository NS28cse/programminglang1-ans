// 第13回 課題3「戻り方を比較する」（NewPoint / versions/return_styles.c）
// Point を値として返す，呼び出し元の Point * へ書き込む，malloc した Point * を返す，の 3 つを並べて比べる。
// 3 つとも同じ (3.0, 4.0) を表示する。解放が必要なのは (c) だけ。
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

// (a) 値として返す：本体は呼び出し元の変数にコピーされる。失敗はなく，解放も不要
Point make_point(double x, double y)
{
    return (Point){.x = x, .y = y};
}

// (b) 呼び出し元が用意した Point へ書き込む：領域の寿命・所有者は呼び出し元
int init_point(Point *out, double x, double y)
{
    if (out == NULL) {
        return 0;
    }
    *out = (Point){.x = x, .y = y};
    return 1;
}

// (c) malloc した Point * を返す：成功なら初期化済みの Point を返し，呼び出し元が free する．失敗なら NULL を返す．
Point *new_point(double x, double y)
{
    Point *p = malloc(sizeof *p);
    if (p == NULL) {
        return NULL;
    }
    *p = (Point){.x = x, .y = y};
    return p;
}

int main(void)
{
    Point a = make_point(3.0, 4.0);
    Point b;
    if (!init_point(&b, 3.0, 4.0)) {
        return 1;
    }
    Point *c = new_point(3.0, 4.0);
    if (c == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    printf("a: x=%.1f y=%.1f\n", a.x, a.y);
    printf("b: x=%.1f y=%.1f\n", b.x, b.y);
    printf("c: x=%.1f y=%.1f\n", c->x, c->y);
    free(c);
    c = NULL;
    return 0;
}
