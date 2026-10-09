// 第7回 課題2　英字の数を数える（LetterCount / letter_count.c）
// 1 行（改行または EOF まで）に含まれる ASCII 英字の個数を表示する。
#include <stdio.h>
int main(void)
{
    int ch;
    int count = 0;
    // 改行でも止める。左側が偽なら右側の比較は評価されない（短絡評価）
    while ((ch = getchar()) != EOF && ch != '\n') {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            ++count;
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    printf("%d\n", count);
    return 0;
}
