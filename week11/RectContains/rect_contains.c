// 第11回 発展2: 2 点を軸ごとに下限・上限へそろえる normalized と，半開区間で判定する contains
// 引数なしなら (1, 4)，(3, 1) の sample と点 (2, 2)。
// 「RectContains px py」で点だけ，「RectContains x1 y1 x2 y2 px py」で 2 点と点を変えられる
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
        .lower = {.x = 1.0, .y = 4.0}, // わざと y の順序が逆の 2 点
        .upper = {.x = 3.0, .y = 1.0},
        .name = "sample"
    };
    Point p = {2.0, 2.0};
    if (argc != 1 && argc != 3 && argc != 7) {
        fprintf(stderr, "usage: RectContains [[x1 y1 x2 y2] px py]\n");
        return 1;
    }
    int ok = 1;
    if (argc == 7) {
        ok = parse_coord(argv[1], &r.lower.x) && parse_coord(argv[2], &r.lower.y) &&
             parse_coord(argv[3], &r.upper.x) && parse_coord(argv[4], &r.upper.y);
    }
    if (argc >= 3) {
        ok = ok && parse_coord(argv[argc - 2], &p.x) && parse_coord(argv[argc - 1], &p.y);
    }
    if (!ok) {
        fprintf(stderr, "expected numbers from -1000 to 1000\n");
        return 1;
    }
    Rect standard = normalized(r); // r 自体は入力の順序のまま
    printf("%s lower=%.1f %.1f upper=%.1f %.1f\n", standard.name,
           standard.lower.x, standard.lower.y, standard.upper.x, standard.upper.y);
    printf("inside=%d original=%.1f %.1f\n",
           contains(p, standard), r.lower.x, r.lower.y);
    return 0;
}
