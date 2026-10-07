/*
 * 第8回 課題4 PointerWalk: ポインタで配列・文字列を走査する
 * 配列の合計（添字版・ポインタ版），ポインタの差と比較，ポインタ版の文字列長．
 * set_one は main より前に定義してある．「合計する前に set_one(a, COUNT); を呼ぶ」版や
 * 値を変えた版は，CMakeLists.txt で書き換えた版としてテストする．
 */
#include <stdio.h>
enum { COUNT = 5 };
int sum_by_index(const int *a, int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}
int sum_by_pointer(const int *a, int n)
{
    int sum = 0;
    /* 本体では p は a[0]〜a[n-1] のどれかを指す．1 つ先 a + n に着いたら読まずに終わる */
    for (const int *p = a; p != a + n; ++p) {
        sum += *p;
    }
    return sum;
}
size_t pointer_length(const char *s)
{
    const char *start = s;
    /* s が指す文字は変更しないが，s 自身は進めてよい（const char *） */
    while (*s != '\0') {
        ++s;
    }
    return (size_t)(s - start);
}
/* 先頭を指す値がコピーされるので，関数内の変更が呼び出し元の配列に残る */
void set_one(int *a, int n)
{
    for (int i = 0; i < n; ++i) {
        a[i] = 1;
    }
}
int main(void)
{
    int a[COUNT] = {2, 4, 6, 3, 5};
    printf("sum=%d %d\n", sum_by_index(a, COUNT), sum_by_pointer(a, COUNT));
    int *p = a + 1;
    int *q = a + 3;
    printf("distance=%td before=%d equal=%d\n", q - p, p < q, p == q);
    printf("length=%zu\n", pointer_length("cat"));
    return 0;
}
