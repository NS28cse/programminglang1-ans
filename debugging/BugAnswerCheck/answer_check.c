// デバッグ題材: 答え合わせ（第6回）
// check は答え answer と解答 guess を比べ，同じ文字列なら「guess: correct」，違えば「guess: wrong」と表示する。
// main は 3 つの解答を答え "apple" と比べる。
#include <stdio.h>
#include <string.h>

void check(const char answer[], const char guess[])
{
    if (strcmp(answer, guess)) {
        printf("%s: correct\n", guess);
    } else {
        printf("%s: wrong\n", guess);
    }
}

int main(void)
{
    check("apple", "apple");
    check("apple", "apply");
    check("apple", "Apple");
    return 0;
}
