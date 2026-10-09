/* 第10回 課題4　テキストを書き出す（WriteText / write_text.c）
   scores.txt へ 72，85，60 を 1 行ずつ書く（モード "w"：何回実行しても 3 行） */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
enum { COUNT = 3 };
int main(void)
{
    const int scores[COUNT] = {72, 85, 60};
    /* w: ファイルがなければ作り，あれば開いた時点で以前の内容を消す（a なら末尾へ追記する） */
    FILE *fp = fopen("scores.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    int failed = 0;
    for (int i = 0; i < COUNT; ++i) {
        if (fprintf(fp, "%d\n", scores[i]) < 0) {
            failed = 1;
            break;
        }
    }
    /* バッファに残った出力は閉じるときに書かれるので，fclose の失敗も書き込みの失敗として扱う */
    if (fclose(fp) == EOF) {
        failed = 1;
    }
    if (failed) {
        fprintf(stderr, "write error: scores.txt may be incomplete\n");
        return 1;
    }
    return 0;
}
