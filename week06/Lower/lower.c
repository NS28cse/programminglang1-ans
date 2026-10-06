// 第6回 課題2 ASCIIの小文字へ変換（Lower / lower.c）。1文字の変換を関数 lower に分けた最終版
// ASCII を前提に，'A'〜'Z' だけを小文字にする。数字・記号・スペース・終端は変えない。
#include <stddef.h>
#include <stdio.h>

// c のコピーを受け取り，変換した文字を返す（呼び出し元の配列は変更しない）
char lower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return (char)(c - 'A' + 'a');
    }
    return c;
}

int main(void)
{
    char text[] = "Hello C17!";
    // 終端の手前まで処理する。返された文字を代入しないと text は変わらない
    for (size_t i = 0; text[i] != '\0'; ++i) {
        text[i] = lower(text[i]);
    }
    printf("%s\n", text);
    return 0;
}
