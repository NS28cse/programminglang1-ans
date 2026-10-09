// 第9回 発展1　長さが異なる行を扱う（RaggedRows / versions/letters.c）
// 二重ポインタの別の使い方2: 各要素は1文字だけを指す（終端はないので %s に渡さない）。
#include <stdio.h>
int main(void)
{
    char first = 'a', second = 'b';
    char *letters[] = {&first, &second};
    char **p = letters;
    for (int i = 0; i < 2; ++i) {
        printf("%c\n", *p[i]);
    }
    return 0;
}
