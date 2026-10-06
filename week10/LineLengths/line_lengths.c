/* 第10回 課題1 LineLengths: 各行の長さ（改行を除く）を表示する（講義の line_lengths.c）
   対象は ASCII・NUL なし・各行 31 文字以内のテキスト */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0') {
        fprintf(stderr, "usage: LineLengths filename\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) { perror("fopen"); return 1; }
    char line[32];   /* 最大 31 バイト + 終端 */
    int failed = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            /* 改行を実際に読んだときだけ 1 バイト除く（常に -1 にしない） */
            line[--length] = '\0';
        } else if (length == sizeof line - 1) {
            /* 31 文字で改行が入らなかった: 次の 1 文字が改行か EOF なら 31 文字の行 */
            int ch = fgetc(fp);
            if (ch != '\n' && ch != EOF) {
                fprintf(stderr, "line too long\n");
                failed = 1;
                break;
            }
        }
        if (printf("%zu\n", length) < 0) { failed = 1; break; }
    }
    if (ferror(fp)) { failed = 1; }
    if (fclose(fp) == EOF) { failed = 1; }
    if (fflush(stdout) == EOF) { failed = 1; }
    if (failed) { fprintf(stderr, "read or output error\n"); return 1; }
    return 0;
}
