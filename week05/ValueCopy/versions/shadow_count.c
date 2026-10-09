// 第5回 確認問題6　グローバル変数の隠蔽（ValueCopy / versions/shadow_count.c）
// 講義の tick に同名の局所変数 count を宣言し，++count が局所変数だけを変えること（隠蔽）を確かめる。
// MSVC /W4 では C4459（グローバル宣言の隠蔽）の警告が出る。
#include <stdio.h>

int count = 0;

void tick(void)
{
    int count = 3;  // グローバル変数 count を隠す局所変数
    ++count;        // 局所変数が 4 になるだけ
    printf("local count=%d\n", count);
}

int main(void)
{
    printf("global count=%d\n", count);
    tick();
    printf("global count=%d\n", count);
    return 0;
}
