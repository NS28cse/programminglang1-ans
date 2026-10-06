/* 第10回 課題2 ParseNumber: 引数の整数（各 0〜100，1〜10 個）を検査して合計を表示する
   講義の parse_number.c の検査・変換部分を「複数の数値を合計するなら」の断片へ置き換えた最終版 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 11) {
        fprintf(stderr, "expected 1 to 10 integers\n");
        return 1;
    }
    /* 各値は 0〜100，最大 10 個なので合計は 1000 以下で long の範囲内 */
    long total = 0;
    for (int i = 1; i < argc; ++i) {
        char *end;
        errno = 0;
        long value = strtol(argv[i], &end, 10);
        if (end == argv[i] || *end != '\0' || errno == ERANGE ||
            value < 0 || value > 100) {
            fprintf(stderr, "invalid integer\n");
            return 1;
        }
        total += value;
    }
    printf("%ld\n", total);
    return 0;
}
