// 第4回 確認問題2 flag が -1 のときの条件の真偽（Fee / versions/flag_minus1.c）
// if (flag)，if (!flag)，if (flag == 1) の真偽を表示する．
// 0 以外はすべて真なので if (flag) は真．「真」と「1 と等しい」は違うので if (flag == 1) は偽．
#include <stdio.h>

int main(void)
{
    int flag = -1;

    if (flag) {
        printf("if (flag): true\n");
    } else {
        printf("if (flag): false\n");
    }
    if (!flag) {
        printf("if (!flag): true\n");
    } else {
        printf("if (!flag): false\n");
    }
    if (flag == 1) {
        printf("if (flag == 1): true\n");
    } else {
        printf("if (flag == 1): false\n");
    }
    return 0;
}
