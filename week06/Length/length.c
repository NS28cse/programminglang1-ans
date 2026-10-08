// 第6回 課題1 長さを数える（Length / length.c）
// 文字列は最初の終端 '\0' で終わる。関数は配列の容量を受け取らず，終端まで走査する。
#include <stddef.h>
#include <stdio.h>
// strlen を使わずに長さを数える。s は読み取り可能な領域内に終端を持つ文字列であること
size_t my_length(const char s[])
{
    size_t n = 0;
    while (s[n] != '\0') {
        ++n;
    }
    return n;
}

// 半角スペース ' ' の数を数える（講義の count_spaces。タブや改行は数えない）
size_t count_spaces(const char s[])
{
    size_t count = 0;
    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == ' ') {
            ++count;
        }
    }
    return count;
}

int main(void)
{
    // 表の4つの文字列（スペースも1文字に数える）
    printf("length(\"\")=%zu\n", my_length(""));
    printf("length(\"A\")=%zu\n", my_length("A"));
    printf("length(\"Hello\")=%zu\n", my_length("Hello"));
    printf("length(\"A B\")=%zu\n", my_length("A B"));

    // 容量（sizeof）と文字列長は別のもの
    char text[10] = "abc";
    printf("length=%zu capacity=%zu\n", my_length(text), sizeof text);
    text[1] = '\0';
    printf("text=%s length=%zu capacity=%zu\n",
           text, my_length(text), sizeof text);

    printf("spaces=%zu %zu %zu\n",
           count_spaces("abc def gh"),
           count_spaces("ijk lmn opq rst"), count_spaces(""));
    return 0;
}
