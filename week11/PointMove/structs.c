// 第11回 課題1: 値渡し（moved）とポインタ渡し（move_in_place）で a の変化を比べる（講義の structs.c）
// 引数なしなら講義と同じ移動量 3, -1。「PointMove dx dy」で両方の呼び出しの移動量を同時に変えられる
// （移動後の座標も -1000〜1000 に収まる値だけを受け付ける）
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
typedef struct {
    double x;
    double y;
} Point;
typedef struct {
    char name[16];
    int score;
} Student;
// p は呼び出し元の Point のコピー。変更したコピーを戻り値で返す
Point moved(Point p, double dx, double dy)
{
    p.x += dx;
    p.y += dy;
    return p;
}
// p はアドレスのコピー。同じアドレスを通して呼び出し元の Point 本体を書き換える
void move_in_place(Point *p, double dx, double dy)
{
    p->x += dx;
    p->y += dy;
}
// 文字列全体を -1000〜1000 の実数として読めたら 1（NaN・無限大・範囲外・余分な文字は 0）
int parse_amount(const char *text, double *value)
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
    double dx = 3.0; // moved と move_in_place で同じ移動量を使う
    double dy = -1.0;
    if (argc != 1 && argc != 3) {
        fprintf(stderr, "usage: PointMove [dx dy]\n");
        return 1;
    }
    if (argc == 3 && (!parse_amount(argv[1], &dx) || !parse_amount(argv[2], &dy))) {
        fprintf(stderr, "expected numbers from -1000 to 1000\n");
        return 1;
    }
    Point a = {1.0, 2.0};
    Point b = moved(a, dx, dy); // a は変わらず，移動した結果が b に入る
    if (!(b.x >= -1000.0 && b.x <= 1000.0 && b.y >= -1000.0 && b.y <= 1000.0)) {
        fprintf(stderr, "moved point must stay from -1000 to 1000\n");
        return 1;
    }
    printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);
    move_in_place(&a, dx, dy); // a 自体が変わる
    printf("a=(%.1f, %.1f)\n", a.x, a.y);
    Student s = {"Aki", 80};
    Student t = s; // name の配列も含めて全メンバをコピーする
    t.name[0] = 'M'; // t の配列だけが変わり，s.name は "Aki" のまま
    printf("%s %s\n", s.name, t.name);
    return 0;
}
