// 第7回 課題2: EOF までに読み取ったバイト数（改行を含む）を数える
#include <stdio.h>
int main(void)
{
    int count = 0; // 入力は合計 1000 バイト以内とする（int で十分）
    while (getchar() != EOF) {
        ++count;
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    printf("%d\n", count);
    return 0;
}
