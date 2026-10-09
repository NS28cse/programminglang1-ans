// 第11回 課題3　長方形を表す（Rect / rect.c）
// Point を 2 つ持つ Rect（入れ子の構造体）の面積とメンバ参照。名前もメンバに持つ。
#include <stdio.h>
enum { MAX_NAME = 20 };
typedef struct {
    double x;
    double y;
} Point;
typedef struct {
    Point lower; // 左下（各座標の下限）
    Point upper; // 右上（各座標の上限）
    char name[MAX_NAME + 1]; // ASCII で 20 文字と終端
} Rect;
// r は Rect へのポインタなので r->lower で Rect の先へ進み，lower は Point 本体なので .x を続ける。
// upper の各座標が lower 以上であることが前提（逆向きの座標は発展2で正規化する）
double area(const Rect *r)
{
    return (r->upper.x - r->lower.x) * (r->upper.y - r->lower.y);
}
// 終端まで入る容量があるときだけ name を src へ置き換えて 1 を返す（入らなければ何も変えず 0）
int set_name(Rect *r, const char *src)
{
    size_t len = 0;
    while (src[len] != '\0') {
        ++len;
    }
    if (len + 1 > sizeof r->name) {
        return 0;
    }
    for (size_t i = 0; i <= len; ++i) { // 終端もコピーする
        r->name[i] = src[i];
    }
    return 1;
}
int main(void)
{
    // 座標は -1000〜1000 で，upper の x・y はそれぞれ lower 以上にする
    Rect r = {
        .lower = {1.0, 2.0},
        .upper = {5.0, 5.0},
        .name = "sample"
    };
    // main の r は Rect 本体なので，ドットを 2 回使う
    printf("%s lower=(%.1f, %.1f) upper=(%.1f, %.1f)\n",
           r.name, r.lower.x, r.lower.y, r.upper.x, r.upper.y);
    printf("width=%.1f height=%.1f area=%.1f\n",
           r.upper.x - r.lower.x, r.upper.y - r.lower.y, area(&r));
    Rect *q = &r;
    printf("%.1f %.1f %.1f %.1f\n",
           r.lower.x, (r.lower).x, q->lower.x, (q->lower).x);
    // r.name = "other"; とは書けないので，容量を確かめて文字をコピーする
    if (!set_name(&r, "other")) {
        fprintf(stderr, "name too long\n");
        return 1;
    }
    printf("renamed=%s\n", r.name);
    return 0;
}
