// 第7回 発展　別解：お手本の文字数だけ読んで採点する（Typing / versions/typing_bounded.c）
// 繰り返しの条件の先頭で position < length を調べ，13 文字を読んだら残りの入力は読まずに採点を終える。
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
    size_t position = 0;            // 次に読む文字の位置
    int score = 0;                  // 一致した場合だけ増える
    int ch;
    printf("Model: %s\n", target);
    printf("Input: ");
    fflush(stdout);
    // 左から順に評価する。position が 13 になったら getchar を呼ばずに終わる（14 文字目以降は読まない）
    while (position < length && (ch = getchar()) != EOF && ch != '\n') {
        // 条件で範囲を確かめた後なので，target[position] は必ずお手本の文字
        if (lower(ch) == lower(target[position])) {
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
