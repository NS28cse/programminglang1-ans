/*
 * 第8回 課題1　ポインタのコピーを比較する（Swap / versions/copy_pointer.c）
 * 演習のコードを main 内にそのまま書いたもの．*p = *q（指す先の値のコピー）と
 * p = q（ポインタ値のコピー）の違いを，p がどの変数を指すかの比較（1 か 0）で表示する．
 */
#include <stdio.h>
int main(void)
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
    return 0;
}
