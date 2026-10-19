// デバッグ題材: 大文字にして写す（第7回）
// 標準入力を EOF まで 1 文字ずつ読み，英小文字は大文字に変え，それ以外の文字はそのまま表示する。
#include <stdio.h>

int main(void)
{
    int ch;

    while (getchar() != EOF) {
        ch = getchar();
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 'A';
        }
        putchar(ch);
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    return 0;
}
