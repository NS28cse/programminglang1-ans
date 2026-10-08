/*
 * 第8回 課題3 CopyText: 容量を確かめてから文字列をコピーする（添字なしのポインタ版）
 * 契約: src は終端のある文字列，dst は capacity 要素の書き込み可能な配列，両者は重ならない．
 * 戻り値: 成功なら 1，容量不足なら 0（このとき dst は 1 要素も変更しない）．
 */
#include <stdio.h>
#include <string.h>
int copy_text(char *dst, size_t capacity, const char *src)
{
    /* 終端まで入れるには strlen(src) + 1 要素が必要．書き込みを始める前に判定する */
    if (strlen(src) >= capacity) {
        return 0;
    }
    /* 1 文字代入してから，代入した値が終端か調べる．終端もコピーしてから終わる */
    while ((*dst = *src) != '\0') {
        ++dst;
        ++src;
    }
    return 1;
}
/* 1 ケースの結果を表示する．elements は配列の全要素（%s は最初の終端で止まるため別に表示） */
void report(const char *declaration, const char *src, int result, const char *out, size_t size)
{
    printf("%s src=\"%s\": return=%d out=\"%s\" elements:", declaration, src, result, out);
    for (size_t i = 0; i < size; ++i) {
        if (out[i] == '\0') {
            printf(" \\0");
        } else {
            printf(" %c", out[i]);
        }
    }
    printf("\n");
}
int main(void)
{
    /* 容量を表す引数には sizeof out を渡す（関数へ配列の長さは自動では伝わらない） */
    {
        char out[4] = "";
        int result = copy_text(out, sizeof out, "cat");
        report("char out[4] = \"\";", "cat", result, out, sizeof out);
    }
    {
        char out[3] = "";
        int result = copy_text(out, sizeof out, "cat");
        report("char out[3] = \"\";", "cat", result, out, sizeof out);
    }
    {
        char out[1] = "";
        int result = copy_text(out, sizeof out, "");
        report("char out[1] = \"\";", "", result, out, sizeof out);
    }
    {
        char out[4] = "old";
        int result = copy_text(out, sizeof out, "cats");
        report("char out[4] = \"old\";", "cats", result, out, sizeof out);
    }
    {
        char out[] = "aaaaaaaaaa";
        int result = copy_text(out, sizeof out, "hoge");
        report("char out[] = \"aaaaaaaaaa\";", "hoge", result, out, sizeof out);
    }
    return 0;
}
