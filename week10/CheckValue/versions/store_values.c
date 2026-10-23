/* 第10回 発展2　別解：値を全部配列に保存してから探す（CheckValue / versions/store_values.c）
   read_values でファイル全体を検査しながら値を配列へ集め，形式が正しいと分かってから contains で探す。
   検査と検索が別の関数になるので「見つけてもすぐ return しない」を意識せずに済むが，値の個数分（最大 100 個）の配列が要る */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
enum { MAX_COUNT = 100, MAX_VALUE = 9801, MAX_LINE = 30 };
int parse_long(const char *text, long max, long *value);
int read_value(FILE *fp, long max, long *value);
int read_values(FILE *fp, long values[], long *count);
int contains(const long values[], long count, long target);
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
    long values[MAX_COUNT];   /* ヘッダの個数は 0〜100 と検査するので，100 個分あれば足りる */
    long count = 0;
    int ok = read_values(fp, values, &count);
    if (fclose(fp) == EOF) {
        fprintf(stderr, "read error\n");
        ok = 0;
    }
    if (!ok) {
        return 1;
    }
    /* ファイル全体が正しい形式だと確認できてから，保存した count 個の中を探す */
    printf("%s\n", contains(values, count, target) ? "found" : "not found");
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
/* ファイル全体の形式を検査し，値を values[0]〜values[*count - 1] に保存する。正しい形式なら 1，誤りなら 0。
   values には MAX_COUNT 個分の領域があること */
int read_values(FILE *fp, long values[], long *count)
{
    long n;
    int result = read_value(fp, MAX_COUNT, &n);   /* n が 0〜100 なので values の範囲内に収まる */
    if (result != 1) {
        report_line_error(fp, 1, result, "count from 0 to 100");
        return 0;
    }
    for (long i = 0; i < n; ++i) {
        result = read_value(fp, MAX_VALUE, &values[i]);
        if (result != 1) {
            report_line_error(fp, i + 2, result, "value from 0 to 9801");
            return 0;
        }
    }
    /* N 個の値の後には何もない（空行も不可） */
    if (fgetc(fp) != EOF) {
        fprintf(stderr, "line %ld: extra data\n", n + 2);
        return 0;
    }
    if (ferror(fp)) {
        fprintf(stderr, "read error\n");
        return 0;
    }
    *count = n;
    return 1;
}
/* values[0]〜values[count - 1] に target があれば 1，なければ 0 */
int contains(const long values[], long count, long target)
{
    for (long i = 0; i < count; ++i) {
        if (values[i] == target) {
            return 1;   /* 検査は済んでいるので，見つけたらすぐ返してよい */
        }
    }
    return 0;
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
