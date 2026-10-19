// デバッグ題材: ファイルの文字数と行数（第10回）
// コマンドライン引数で指定したテキストファイルを 1 文字ずつ読み，
// 文字数（改行も 1 文字と数える）と行数（改行の数）を表示する。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: BugCharCount filename\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    long chars = 0;
    long lines = 0;
    while (!feof(fp)) {
        int ch = fgetc(fp);
        ++chars;
        if (ch == '\n') {
            ++lines;
        }
    }
    if (ferror(fp)) {
        fprintf(stderr, "read error\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    printf("chars=%ld lines=%ld\n", chars, lines);
    return 0;
}
