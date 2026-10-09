/* 第10回 課題3　バイト順を調べる（ByteOrder / byte_order.c）
   講義の観察用断片（unsigned short value = 1）を別の main にし，unsigned short のメモリ上のバイト順を観察する */
#include <stdio.h>
int main(void)
{
    unsigned short value = 1;
    printf("sizeof value = %zu\n", sizeof value);
    /* オブジェクトの表現を unsigned char として 1 バイトずつ見る。サイズは 2 と決めつけず sizeof で回す */
    const unsigned char *bytes = (const unsigned char *)&value;
    for (size_t i = 0; i < sizeof value; ++i) {
        printf("%02X%s", (unsigned int)bytes[i],
               i + 1 == sizeof value ? "\n" : " ");
    }
    return 0;
}
