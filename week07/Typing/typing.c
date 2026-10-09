// 第7回 発展　タイピングの採点（Typing / typing.c）
// お手本 "This is a pen" と同じ位置の文字を，大文字・小文字を区別せずに比較して得点を数える。
#include <stdio.h>
#include <string.h>

// ASCII の英大文字だけを小文字にする。EOF を除いた後の値を渡す
int lower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

int main(void)
{
    const char target[] = "This is a pen";
    size_t length = strlen(target); // 13
    size_t position = 0;            // 次に読む文字の位置（入力するたびに進む）
    int score = 0;                  // 一致した場合だけ増える
    int ch;
    printf("Model: %s\n", target);
    printf("Input: ");
    fflush(stdout);
    while ((ch = getchar()) != EOF && ch != '\n') {
        // 範囲内かを先に調べてから target を読む（14 文字目以降は加点しない）
        if (position < length && lower(ch) == lower(target[position])) {
            ++score;
        }
        ++position;
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    printf("score=%d\n", score);
    return 0;
}
