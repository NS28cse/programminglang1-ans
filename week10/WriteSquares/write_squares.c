/* 第10回 発展2　二乗の一覧を書き出して検索する（WriteSquares / write_squares.c）
   個数 N（0〜100）と新しいファイル名を受け取り，1 行目に N，続く N 行に 0〜N-1 の二乗を書く（既存のファイルは上書きしない） */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
enum { MAX_COUNT = 100 };
int parse_long(const char *text, long max, long *value);
int main(int argc, char *argv[])
{
    if (argc != 3 || argv[2][0] == '\0') {
        fprintf(stderr, "usage: WriteSquares count filename\n");
        return 1;
    }
    long count;
    if (!parse_long(argv[1], MAX_COUNT, &count)) {
        fprintf(stderr, "expected a count from 0 to 100\n");
        return 1;
    }
    /* wx: 同名のファイルがあれば開くのに失敗する。失敗しても w へ切り替えない */
    FILE *fp = fopen(argv[2], "wx");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    int failed = fprintf(fp, "%ld\n", count) < 0;
    for (long i = 0; i < count && !failed; ++i) {
        /* i は 99 以下なので i * i は 9801 以下で，オーバーフローしない */
        if (fprintf(fp, "%ld\n", i * i) < 0) {
            failed = 1;
        }
    }
    if (fclose(fp) == EOF) {
        failed = 1;
    }
    if (failed) {
        /* 途中までのファイルが残ることがあるので，完成品として使わないよう知らせる */
        fprintf(stderr, "write error: %s may be incomplete\n", argv[2]);
        return 1;
    }
    return 0;
}
/* text 全体が 0〜max の整数なら *value に入れて 1，そうでなければ 0（*value は変えない） */
int parse_long(const char *text, long max, long *value)
{
    char *end;
    errno = 0;
    long result = strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE || result < 0 || result > max) {
        return 0;
    }
    *value = result;
    return 1;
}
