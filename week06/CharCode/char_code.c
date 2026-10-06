// 第6回 ウォームアップ：文字と数値（CharCode / char_code.c）
// char は小さな整数。%c なら文字，%d なら文字コード（ASCII の値）として表示する。
#include <stdio.h>

int main(void)
{
    char c = '3';
    printf("character=%c code=%d\n", c, c);
    // 数字の文字だと確認してから '0' を引く（'A' などは数字として解釈しない）
    if (c >= '0' && c <= '9') {
        printf("digit=%d\n", c - '0');
    }
    // 文字列リテラルも添字で読める（書き換えはしない）
    printf("last=%c\n", "abcd"[3]);
    return 0;
}
