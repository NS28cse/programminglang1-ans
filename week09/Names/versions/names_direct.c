// 第9回 課題2　関数へ分ける前の途中版（main に直接交換を書いた版）
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
