// 第2回 課題4 値・サイズ・場所の観察（Observe / observe.c）
// 代入で変わるのは値だけで，サイズ（型で決まる）と場所（アドレス）は変わらない
// サイズとアドレスは処理系・実行ごとに異なるため，表示の数値は環境によって違う
#include <stdio.h>

int main(void)
{
    int value = 10;

    printf("before: value=%d sizeof value=%zu &value=%p\n",
           value, sizeof value, (void *)&value);

    value = 99;                     // 同じ領域の中身を上書きする
    printf("after:  value=%d sizeof value=%zu &value=%p\n",
           value, sizeof value, (void *)&value);

    printf("sizeof(char)=%zu\n", sizeof(char));
    printf("sizeof(int)=%zu\n", sizeof(int));
    printf("sizeof(long)=%zu\n", sizeof(long));
    printf("sizeof(long long)=%zu\n", sizeof(long long));
    printf("sizeof(double)=%zu\n", sizeof(double));
    return 0;
}
