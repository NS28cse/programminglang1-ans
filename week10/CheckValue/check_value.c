/* 第10回 発展2　二乗の一覧を書き出して検索する（CheckValue / check_value.c）
   WriteSquares の形式（ASCII・NUL なし・1 行 1 整数・各行 30 バイト以内。1 行目が個数 N（0〜100），続く N 行が値（0〜9801））の
   ファイルを最後まで検査しながら，指定した値（0〜9801）を探す。値の前後の空白と最後の行の改行なしは許し，
   空行・個数不足・余分な行・範囲外の値・長すぎる行は拒否する。NUL や非 ASCII のバイトは前提として検査しない
   （例: "9\0x" の行は fgets 後の文字列が "9" なので 9 として読む） */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
enum { MAX_COUNT = 100, MAX_VALUE = 9801, MAX_LINE = 30 };
int parse_long(const char *text, long max, long *value);
int read_value(FILE *fp, long max, long *value);
int check_file(FILE *fp, long target, int *found);
void report_line_error(FILE *fp, long line_number, int result, const char *expected);
int main(int argc, char *argv[])
{
    if (argc != 3 || argv[1][0] == '\0') {
        fprintf(stderr, "usage: CheckValue filename value\n");
        return 1;
    }
    long target;
    if (!parse_long(argv[2], MAX_VALUE, &target)) {
        fprintf(stderr, "expected a value from 0 to 9801\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    int found = 0;
    int ok = check_file(fp, target, &found);
    if (fclose(fp) == EOF) {
        ok = 0;
    }
    if (!ok) {
        return 1;
    }
    /* ファイル全体が正しい形式だと確認できてから結果を表示する */
    printf("%s\n", found ? "found" : "not found");
    return 0;
}
/* text 全体が 0〜max の整数なら *value に入れて 1，そうでなければ 0（*value は変えない） */
int parse_long(const char *text, long max, long *value)
{
    char *end;
    errno = 0;
    long result = strtol(text, &end, 10);   /* 先頭の空白と符号は strtol が受け付ける */
    if (end == text || *end != '\0' || errno == ERANGE || result < 0 || result > max) {
        return 0;
    }
    *value = result;
    return 1;
}
/* 1 行読み，0〜max の整数 1 個なら *value に入れて 1 を返す。
   行がない（終端または読み取りエラー）なら 0，形式が誤りなら -1，31 バイト以上の行なら -2。失敗時は *value を変えない */
int read_value(FILE *fp, long max, long *value)
{
    char line[MAX_LINE + 2];   /* 30 バイト + 改行 + 終端 */
    if (fgets(line, sizeof line, fp) == NULL) {
        return 0;
    }
    size_t length = strlen(line);
    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }
    if (length > (size_t)MAX_LINE) {
        return -2;   /* 31 バイト以上の行（改行が配列に入りきらなかった） */
    }
    /* 末尾の空白を除く。CR は CRLF のファイルをテキスト変換のない環境で読んだときに残る */
    while (length > 0 && (line[length - 1] == ' ' || line[length - 1] == '\t' ||
                          line[length - 1] == '\r')) {
        line[--length] = '\0';
    }
    return parse_long(line, max, value) ? 1 : -1;
}
/* ファイル全体の形式を検査し，target があれば *found を 1 にする。正しい形式なら 1，誤りなら 0 */
int check_file(FILE *fp, long target, int *found)
{
    long count;
    int result = read_value(fp, MAX_COUNT, &count);
    if (result != 1) {
        report_line_error(fp, 1, result, "count from 0 to 100");   /* 読めなかった count は使わない */
        return 0;
    }
    /* ヘッダの個数を信用せず，その個数の行が本当にあるかを 1 行ずつ確かめる */
    for (long i = 0; i < count; ++i) {
        long value;
        result = read_value(fp, MAX_VALUE, &value);
        if (result != 1) {
            report_line_error(fp, i + 2, result, "value from 0 to 9801");
            return 0;
        }
        if (value == target) {
            *found = 1;   /* ここで return せず，残りの行も検査する */
        }
    }
    /* N 個の値の後には何もない（空行も不可） */
    if (fgetc(fp) != EOF) {
        fprintf(stderr, "line %ld: extra data\n", count + 2);
        return 0;
    }
    if (ferror(fp)) {
        fprintf(stderr, "read error\n");
        return 0;
    }
    return 1;
}
/* read_value の失敗（result が 0，-1，-2）を行番号付きで標準エラーへ説明する */
void report_line_error(FILE *fp, long line_number, int result, const char *expected)
{
    if (ferror(fp)) {
        fprintf(stderr, "line %ld: read error\n", line_number);
    } else if (result == 0) {
        fprintf(stderr, "line %ld: missing %s\n", line_number,
                line_number == 1 ? "count" : "value");
    } else if (result == -2) {
        fprintf(stderr, "line %ld: line too long\n", line_number);
    } else {
        fprintf(stderr, "line %ld: expected a %s\n", line_number, expected);
    }
}
