/* 第12回 発展3　標準ライブラリの契約を確かめる（LibraryCheck / library_check.c）
   標準ライブラリの契約（ヘッダ・入力条件・戻り値）を確かめる．演習ページのコードのまま */
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char src[5] = {'a', 'b', '\0', 'c', 'd'};
    char text[10] = {0};
    char bytes[10] = {0};
    strcpy(text, src);
    memcpy(bytes, src, sizeof src);
    printf("math=%.1f %.1f %.1f\n",
           sqrt(9.0), pow(3.0, 2.0), fabs(-2.5));
    printf("alpha=%d digit=%d min_positive=%d\n",
           isalpha((unsigned char)'A') != 0,
           isdigit((unsigned char)'7') != 0, FLT_MIN > 0.0f);
    printf("text=%s bytes=%c%c %c%c\n",
           text, bytes[0], bytes[1], bytes[3], bytes[4]);
    assert(text[2] == '\0');
    assert(bytes[3] == 'c');

    srand(123U);
    int first = rand();
    srand(123U);
    int again = rand();
    printf("same_seed=%d\n", first == again);
    double u = (double)rand() / RAND_MAX;
    printf("in_range=%d\n", 0.0 <= u && u <= 1.0);
    return 0;
}
