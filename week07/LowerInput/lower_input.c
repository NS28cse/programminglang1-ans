// 第7回 課題1　小文字化フィルタ（LowerInput / lower_input.c）
// 入力を 1 バイトずつ読み，ASCII の英大文字だけを小文字にして出力する。
#include <stdio.h>
int main(void)
{
    int ch;
    while ((ch = getchar()) != EOF) {
        // EOF を除いた後なので ch は実際に読んだ 1 バイト。範囲内だけを変換する
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }
        if (putchar(ch) == EOF) {
            fprintf(stderr, "output error\n");
            return 1;
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    return 0;
}
