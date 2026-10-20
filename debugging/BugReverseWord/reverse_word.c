// デバッグ題材: 単語を逆順に表示する（第7回）
// 標準入力の 1 行目（MAX_WORD 文字まで。超えた分は捨てる）を配列 word に文字列として入れ，
// その文字列と，逆順にした文字列を表示する。
#include <stdio.h>

enum { MAX_WORD = 8 };

int main(void)
{
    char word[MAX_WORD];
    int length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length < MAX_WORD) {
            word[length] = (char)ch;
            ++length;
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    word[length] = '\0';

    printf("word: %s\n", word);
    printf("reversed: ");
    for (int i = length - 1; i >= 0; --i) {
        putchar(word[i]);
    }
    printf("\n");
    return 0;
}
