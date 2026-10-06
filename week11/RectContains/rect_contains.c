// 第11回 発展2: 2 点を軸ごとに下限・上限へそろえる normalized と，半開区間で判定する contains
#include <stdio.h>
enum { MAX_NAME = 20 };
typedef struct {
    double x;
    double y;
} Point;
typedef struct {
    Point lower;
    Point upper;
    char name[MAX_NAME + 1];
} Rect;
// r のコピー result から始めるので name も含めて全メンバが値を持つ。
// x と y を独立に比べ，小さい方を lower，大きい方を upper に置く
Rect normalized(Rect r)
{
    Rect result = r;
    if (r.lower.x > r.upper.x) {
        result.lower.x = r.upper.x;
        result.upper.x = r.lower.x;
    }
    if (r.lower.y > r.upper.y) {
        result.lower.y = r.upper.y;
        result.upper.y = r.lower.y;
    }
    return result;
}
// 下限を含み上限を含まない（半開区間）。r は正規化済みであることが前提
int contains(Point p, Rect r)
{
    return p.x >= r.lower.x && p.x < r.upper.x &&
           p.y >= r.lower.y && p.y < r.upper.y;
}
int main(void)
{
    // わざと y の順序が逆の 2 点（座標は有限な -1000〜1000）
    Rect r = {
        .lower = {.x = 1.0, .y = 4.0},
        .upper = {.x = 3.0, .y = 1.0},
        .name = "sample"
    };
    Point p = {2.0, 2.0};
    Rect standard = normalized(r); // r 自体は入力の順序のまま
    printf("%s lower=%.1f %.1f upper=%.1f %.1f\n", standard.name,
           standard.lower.x, standard.lower.y, standard.upper.x, standard.upper.y);
    printf("inside=%d original=%.1f %.1f\n",
           contains(p, standard), r.lower.x, r.lower.y);
    return 0;
}
