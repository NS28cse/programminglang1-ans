// 第5回 確認問題6 の確認用（ValueCopy の versions/shadow_count.c。本体とは別にテストする）
// 講義の tick に同名の局所変数 count を宣言し，++count が局所変数だけを変えること（隠蔽）を確かめる。
// MSVC /W4 では「グローバル宣言を隠す」警告（番号は例: C4459）が出る（この版だけ CMakeLists.txt で抑止している）。
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
