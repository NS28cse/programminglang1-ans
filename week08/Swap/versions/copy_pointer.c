/*
 * 第8回 課題1 Swap の「ポインタのコピーを比較する」（演習のコードを main 内にそのまま書いた版）
 * CMakeLists.txt の書き換え版 copy_pointer として，置換なしでビルド・テストする．
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
