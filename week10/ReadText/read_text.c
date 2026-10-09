/* 第10回 課題1　ファイルを読む（ReadText / read_text.c）
   講義の read_text.c。引数で指定したテキストファイルを 1 文字ずつ読んで表示する */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(int argc, char *argv[])
{
    /* 引数はファイル名 1 個だけ。argc を先に調べてから argv[1] を使う */
    if (argc != 2 || argv[1][0] == '\0') {
        fprintf(stderr, "usage: ReadText filename\n");
        return 1;
    }
    /* 相対パスは作業ディレクトリ（$(ProjectDir)）が基準 */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    int ch;   /* EOF と区別するため char ではなく int で受ける */
    int failed = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (putchar(ch) == EOF) { failed = 1; break; }
    }
    /* EOF はファイル終端でも読み取りエラーでも返るので ferror で区別する */
    if (ferror(fp)) { failed = 1; }
    if (fclose(fp) == EOF) { failed = 1; }
    if (fflush(stdout) == EOF) { failed = 1; }
    if (failed) {
        fprintf(stderr, "I/O error\n");
        return 1;
    }
    return 0;
}
