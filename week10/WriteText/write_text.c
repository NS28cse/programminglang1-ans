/* 第10回 課題4 WriteText: scores.txt へ 72，85，60 を 1 行ずつ書く
   最初はモード "w"（上書き）で実行し，次にモードだけを "a"（追記）へ変えた最終版 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
enum { COUNT = 3 };
int main(void)
{
    const int scores[COUNT] = {72, 85, 60};
    /* a: ファイルがなければ作り，あれば末尾へ追記する（w なら開いた時点で以前の内容を消す） */
    FILE *fp = fopen("scores.txt", "a");
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
