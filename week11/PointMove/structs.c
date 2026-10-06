// 第11回 課題1: 値渡し（moved）とポインタ渡し（move_in_place）で a の変化を比べる（講義の structs.c）
// 移動量を変えるときは，moved と move_in_place の 2 か所を同じ値に書き換える
#include <stdio.h>
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
int main(void)
{
    Point a = {1.0, 2.0};
    // b には a のコピーを移動した値が入り，a は変わらない。move_in_place は a 自体を変える
    Point b = moved(a, 3.0, -1.0);
    printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);
    move_in_place(&a, 3.0, -1.0);
    printf("a=(%.1f, %.1f)\n", a.x, a.y);
    Student s = {"Aki", 80};
    Student t = s; // name の配列も含めて全メンバをコピーする
    t.name[0] = 'M'; // t の配列だけが変わり，s.name は "Aki" のまま
    printf("%s %s\n", s.name, t.name);
    return 0;
}
