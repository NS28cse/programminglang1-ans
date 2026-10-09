/* 第10回 課題2　数値引数の検査（ParseNumber / parse_number.c）
   講義の parse_number.c。引数の整数 1 個（0〜100）を strtol で検査して表示する */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: ParseNumber integer\n");
        return 1;
    }
    char *end;
    errno = 0;
    long value = strtol(argv[1], &end, 10);
    if (argv[1] == end || *end != '\0' || errno == ERANGE ||
        value < 0 || value > 100) {
        fprintf(stderr, "expected an integer from 0 to 100\n");
        return 1;
    }
    printf("%ld\n", value);
    return 0;
}
