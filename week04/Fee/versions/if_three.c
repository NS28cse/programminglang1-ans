// 第4回 確認問題1 if (3) は真・偽のどちらの経路へ進むか（Fee / versions/if_three.c）
// C の条件は 0 が偽，0 以外がすべて真なので，3 では真の経路（true）へ進む．
#include <stdio.h>

int main(void)
{
    if (3) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}
