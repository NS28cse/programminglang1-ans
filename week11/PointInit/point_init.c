// 第11回 発展1: 指定初期化子，省略したメンバ，複合リテラル，構造体を返す関数
#include <stdio.h>
// タグ付きの typedef: struct point と Point は同じ型を表す
typedef struct point {
    double x;
    double y;
} Point;
// a と b は呼び出し元のコピー。a を変更して返しても呼び出し元の a は変わらない
Point add_point(Point a, Point b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}
int main(void)
{
    Point a = {.y = 2.0, .x = 10.0}; // 指定した名前どおり x=10.0, y=2.0
    struct point b = {3.0, 5.0}; // 名前を指定しない初期化は宣言順（x, y）
    Point result = add_point(a, b);
    printf("a=%.1f %.1f result=%.1f %.1f\n", a.x, a.y, result.x, result.y);
    Point partial = {.x = 3.0}; // 初期化リストで省略した y は 0.0
    Point zero = {0};
    printf("partial=%.1f %.1f zero=%.1f %.1f\n", partial.x, partial.y, zero.x, zero.y);
    a = (Point){.x = -1.0, .y = 4.0}; // 宣言後は型名を付けた複合リテラルで全体を代入する
    printf("assigned=%.1f %.1f\n", a.x, a.y);
    return 0;
}
