/*
 * 第8回 課題1 Swap: swap を追う
 * 講義の pointers.c（最初の 3 行の表示）に，演習の実験を加えた版．
 *   - 宣言・*p = 5・swap の後の x, y, p の指す先, *p を追跡する（初期値を変えて 3 通り）
 *   - p = q（矢印のコピー）と *p = *q（指す先の値のコピー）の比較
 *   - double 版 swap_double で配列の添字 1 と 4 を交換する（2 通りの書き方を別々の配列で）
 * アドレスは実行ごとに変わるので，指す先は p == &x のような比較（1 か 0）で表示する．
 */
#include <stdio.h>
enum { COUNT = 6 };
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void swap_double(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}
int sum_array(const int *a, int n)
{
    int total = 0;
    for (int i = 0; i < n; ++i) {
        total += *(a + i);
    }
    return total;
}
/* pointers.c の前半を x, y の初期値を変えて実行し，代入ごとの状態を表示する */
void trace_swap(int x_init, int y_init)
{
    int x = x_init;
    int y = y_init;
    int *p = &x;
    printf("trace x=%d y=%d\n", x_init, y_init);
    printf("  init:     x=%d y=%d p_is_x=%d *p=%d\n", x, y, p == &x, *p);
    *p = 5;
    printf("  *p = 5:   x=%d y=%d p_is_x=%d *p=%d\n", x, y, p == &x, *p);
    swap(&x, &y);
    printf("  swap:     x=%d y=%d p_is_x=%d *p=%d\n", x, y, p == &x, *p);
}
/* 演習の「ポインタのコピーを比較する」をそのまま実行する */
void copy_pointer_experiment(void)
{
    int a = 10;
    int b = 3;
    int *p = &a;
    int *q = &b;
    *p = *q;
    printf("a=%d b=%d p_is_a=%d\n", a, b, p == &a);
    p = q;
    *p = 7;
    printf("a=%d b=%d p_is_b=%d\n", a, b, p == &b);
}
void print_doubles(const char *label, const double *a, int n)
{
    printf("%s:", label);
    for (int i = 0; i < n; ++i) {
        printf(" %.1f", a[i]);
    }
    printf("\n");
}
/* 2 通りの呼び出しは，それぞれ初期配列から 1 回だけ交換する（続けて呼ぶと元に戻る） */
void swap_double_by_address(void)
{
    double a[COUNT] = {1.0, 5.0, 3.0, 4.0, 2.0, 6.0};
    print_doubles("before", a, COUNT);
    swap_double(&a[1], &a[4]);
    print_doubles("swap_double(&a[1], &a[4])", a, COUNT);
}
void swap_double_by_pointer(void)
{
    double a[COUNT] = {1.0, 5.0, 3.0, 4.0, 2.0, 6.0};
    swap_double(a + 1, a + 4);
    print_doubles("swap_double(a + 1, a + 4)", a, COUNT);
}
int main(void)
{
    /* ここから講義の pointers.c と同じ処理 */
    int x = 3, y = 8;
    int *p = &x;
    *p = 5;
    swap(&x, &y);
    printf("x=%d y=%d\n", x, y);
    int values[] = {10, 20, 30};
    printf("sum=%d\n", sum_array(values, 3));
    const char *word = "cat";
    printf("%c %s\n", *word, word + 1);

    /* ここから演習の実験．swap の後も p は x を指したまま（指す先の値だけが変わる） */
    printf("after swap: p_is_x=%d *p=%d\n", p == &x, *p);
    trace_swap(3, 8);
    trace_swap(3, 5);
    trace_swap(8, 8);
    copy_pointer_experiment();
    swap_double_by_address();
    swap_double_by_pointer();
    return 0;
}
