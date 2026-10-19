// デバッグ題材: 文字列をコピーする（第8回）
// copy_text は src の文字列（終端まで）を dst へコピーする。dst は src が入る大きさの配列とする。
// 同じ配列 buffer へ 2 つの単語を順にコピーし，コピーするたびに buffer を表示する。
#include <stdio.h>

void copy_text(char *dst, const char *src)
{
    while (*src != '\0') {
        *dst = *src;
        ++dst;
        ++src;
    }
}

int main(void)
{
    char buffer[16] = "";

    copy_text(buffer, "horse");
    printf("%s\n", buffer);
    copy_text(buffer, "cat");
    printf("%s\n", buffer);
    return 0;
}
