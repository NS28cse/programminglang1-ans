// 第9回 課題2　表示順を変更する（Names / versions/names_direct.c）
// 関数へ分ける前の形: main の中で names[0] と names[2] のポインタ値を直接交換する。
#include <stdio.h>
int main(void)
{
    const char *names[] = {"Tokyo", "Osaka", "Nagoya"};
    const char *temp = names[0];
    names[0] = names[2];
    names[2] = temp;
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", names[i]);
    }
    return 0;
}
