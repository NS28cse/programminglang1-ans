/* 第10回 課題1　別解：fgetc で 1 文字ずつ数え，行を配列に保存しない（LineLengths / versions/count_chars.c）
   改行を読んだら数えた長さを表示して 0 に戻す。ファイルの終わりで数えかけの文字があれば，改行のない最後の行として表示する。
   本体と同じく，32 文字目を読んだ時点で長すぎる行として終了する */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
enum { MAX_LENGTH = 31 };
int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0') {
        fprintf(stderr, "usage: LineLengths filename\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) { perror("fopen"); return 1; }
    int ch;
    int length = 0;   /* 今の行でここまでに読んだ文字数（改行は含めない） */
    int failed = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            if (printf("%d\n", length) < 0) { failed = 1; break; }
            length = 0;
        } else if (length == MAX_LENGTH) {
            fprintf(stderr, "line too long\n");   /* 改行の前に 32 文字目が来た */
            failed = 1;
            break;
        } else {
            ++length;
        }
    }
    /* 最後の行に改行がないとき（length > 0）も 1 行として表示する。空ファイルは何も表示しない */
    if (!failed && !ferror(fp) && length > 0) {
        if (printf("%d\n", length) < 0) { failed = 1; }
    }
    if (ferror(fp)) { failed = 1; }
    if (fclose(fp) == EOF) { failed = 1; }
    if (fflush(stdout) == EOF) { failed = 1; }
    if (failed) { fprintf(stderr, "read or output error\n"); return 1; }
    return 0;
}
