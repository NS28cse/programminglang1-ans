/* 第3回 課題4 うるう年の条件式（Leap） */
#include <stdio.h>

int main(void)
{
    int year = 2000;  /* 正の整数として与える */

    /* 規則を3つの条件に分けて確認する（真なら1，偽なら0） */
    int div4 = year % 4 == 0;         /* 4で割り切れる */
    int not_div100 = year % 100 != 0; /* 100では割り切れない */
    int div400 = year % 400 == 0;     /* 400で割り切れる */

    /* (4で割り切れる かつ 100では割り切れない) または 400で割り切れる */
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    printf("year=%d\n", year);
    printf("div4=%d not_div100=%d div400=%d\n", div4, not_div100, div400);
    printf("leap=%d\n", leap);
    return 0;
}
