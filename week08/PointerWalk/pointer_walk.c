/*
 * 第8回 課題4 PointerWalk: ポインタで配列・文字列を走査する
 * 最初の 3 行が演習ページの期待する表示．その後の行は「値を変えて確認する」
 * 「関数から配列を書き換える」の確認（set_one は最後に呼んで合計 5 を表示する）．
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

    /* ここから追加の確認 */
    printf("p - q: distance=%td\n", p - q);
    q = a + 1;
    printf("q = a + 1: distance=%td before=%d equal=%d\n", q - p, p < q, p == q);
    int zeros[COUNT] = {0, 0, 0, 0, 0};
    int ascending[COUNT] = {1, 2, 3, 4, 5};
    printf("{0, 0, 0, 0, 0}: sum=%d %d\n", sum_by_index(zeros, COUNT), sum_by_pointer(zeros, COUNT));
    printf("{1, 2, 3, 4, 5}: sum=%d %d\n", sum_by_index(ascending, COUNT), sum_by_pointer(ascending, COUNT));
    printf("length(\"\")=%zu\n", pointer_length(""));
    printf("length(\"A\")=%zu\n", pointer_length("A"));
    printf("length(\"Hello\")=%zu\n", pointer_length("Hello"));
    /* 先頭を指す値がコピーされるので，関数内の変更が呼び出し元の a に残る */
    set_one(a, COUNT);
    printf("after set_one: sum=%d %d\n", sum_by_index(a, COUNT), sum_by_pointer(a, COUNT));
    return 0;
}
