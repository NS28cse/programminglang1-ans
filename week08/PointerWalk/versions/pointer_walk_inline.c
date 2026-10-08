/*
 * 第8回 課題4 PointerWalk の，講義と同じ書き方の版（比較用．CMakeLists.txt の書き換え版 inline でテストする）
 * 講義の例と同じく，合計の添字版・ポインタ版のループを main の中に書き，
 * 合計する前に set_one(a, COUNT); を呼ぶ．set_one の仮引数は int a[] と書いている．
 */
#include <stdio.h>
enum { COUNT = 5 };
size_t pointer_length(const char *s)
{
    const char *start = s;
    while (*s != '\0') {
        ++s;
    }
    return (size_t)(s - start);
}
void set_one(int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        a[i] = 1;
    }
}
int main(void)
{
    int a[COUNT] = {2, 4, 6, 3, 5};
    set_one(a, COUNT);
    int sum_index = 0;
    int sum_pointer = 0;
    for (int i = 0; i < COUNT; ++i) {
        sum_index += a[i];
    }
    for (const int *p = a; p != a + COUNT; ++p) {
        sum_pointer += *p;
    }
    printf("sum=%d %d\n", sum_index, sum_pointer);
    int *p = a + 1;
    int *q = a + 3;
    printf("distance=%td before=%d equal=%d\n", q - p, p < q, p == q);
    printf("length=%zu\n", pointer_length("cat"));
    return 0;
}
