// 第10回 課題1　別解：fgets で配列へまとめて読み，fputs でそのまま表示する（ReadText / versions/read_lines.c）
// 1 回の呼び出しで 1 文字ではなく最大 sizeof line - 1 バイトを扱う。長い行は何回かに分かれて読まれるが，
// 読んだ順に続けて表示するので出力は 1 文字ずつ読む本体と同じになる（途中に NUL を含むファイルは対象外）
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0') {
        fprintf(stderr, "usage: ReadText filename\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    char line[256];  // 1 行がこれより長くても，残りは次の fgets で読む
    int failed = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        // fgets は改行も配列に残すので，fputs（改行を足さない）でそのまま書く
        if (fputs(line, stdout) == EOF) { failed = 1; break; }
    }
    // fgets の NULL は終端でも読み取りエラーでも返るので ferror で区別する
    if (ferror(fp)) { failed = 1; }
    if (fclose(fp) == EOF) { failed = 1; }
    if (fflush(stdout) == EOF) { failed = 1; }
    if (failed) {
        fprintf(stderr, "I/O error\n");
        return 1;
    }
    return 0;
}
