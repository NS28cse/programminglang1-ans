// 第6回 課題4 比較してから連結する（CompareJoin / compare_join.c）
// strcmp は戻り値の符号だけを使う。連結は書き込む前に容量を確かめ，終端も含めてループでコピーする。
#include <stdio.h>
#include <string.h>

int main(void)
{
    char text[10] = "hoge";
    char suffix[] = "fuga";

    int comparison = strcmp(text, suffix);
    if (comparison < 0) {
        printf("before\n");
    } else if (comparison == 0) {
        printf("equal\n");
    } else {
        printf("after\n");
    }

    size_t used = strlen(text);
    size_t added = strlen(suffix);
    // 残り容量 sizeof text - used に，追加する added 文字と終端の1バイトが入るか
    // （used + added + 1 <= sizeof text と同じ）。text は容量内に終端を持つので used < sizeof text
    if (added < sizeof text - used) {
        // i == added で suffix の終端もコピーする
        for (size_t i = 0; i <= added; ++i) {
            text[used + i] = suffix[i];
        }
    } else {
        // 書き込みを始める前に判定しているので，元の文字列がそのまま残る
        printf("not enough space\n");
    }
    printf("text=%s length=%zu capacity=%zu\n", text, strlen(text), sizeof text);
    return 0;
}
