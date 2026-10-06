// 第11回 課題3: Point を 2 つ持つ Rect（入れ子の構造体）の面積とメンバ参照
// 引数なしなら左下 (1, 2)，右上 (5, 5)。「Rect lx ly ux uy」で座標を変えられる（ux >= lx，uy >= ly）
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
// 文字列全体を -1000〜1000 の実数として読めたら 1
int parse_coord(const char *text, double *value)
{
    char *end;
    errno = 0;
    double v = strtod(text, &end);
    if (text == end || *end != '\0' || errno == ERANGE ||
        !(v >= -1000.0 && v <= 1000.0)) {
        return 0;
    }
    *value = v;
    return 1;
}
int main(int argc, char *argv[])
{
    Rect r = {
        .lower = {1.0, 2.0},
        .upper = {5.0, 5.0},
        .name = "sample"
    };
    if (argc != 1 && argc != 5) {
        fprintf(stderr, "usage: Rect [lx ly ux uy]\n");
        return 1;
    }
    if (argc == 5) {
        if (!parse_coord(argv[1], &r.lower.x) || !parse_coord(argv[2], &r.lower.y) ||
            !parse_coord(argv[3], &r.upper.x) || !parse_coord(argv[4], &r.upper.y)) {
            fprintf(stderr, "expected numbers from -1000 to 1000\n");
            return 1;
        }
        if (r.upper.x < r.lower.x || r.upper.y < r.lower.y) {
            fprintf(stderr, "upper must not be less than lower\n");
            return 1;
        }
    }
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
