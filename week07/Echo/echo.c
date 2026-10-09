// 第7回 課題1　入力をそのまま出力する（Echo / echo.c）
// 講義の echo.c。getchar で読んだ 1 バイトを，EOF になるまで putchar でそのまま書き出す。
#include <stdio.h>
int main(void)
{
    int ch; // EOF と 256 通りのバイト値を区別するため char ではなく int で受ける
    while ((ch = getchar()) != EOF) {
        if (putchar(ch) == EOF) {
            fprintf(stderr, "output error\n");
            return 1;
        }
    }
    // 入力終了と読み取りエラーはどちらも EOF で届くので，ループ後に区別する
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    return 0;
}
