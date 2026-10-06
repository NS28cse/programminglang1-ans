/* 第10回 課題3「バイト順を調べる」ByteOrder: unsigned short のメモリ上のバイト順と，1 バイトの 2 進数表示を観察する
   講義の観察用断片（value を 0x1234 へ変更した版）と，演習の 2 進数表示の断片を 1 つの main にまとめた */
#include <stdio.h>
int main(void)
{
    unsigned short value = 0x1234;
    printf("sizeof value = %zu\n", sizeof value);
    /* オブジェクトの表現を unsigned char として 1 バイトずつ見る。サイズは 2 と決めつけず sizeof で回す */
    const unsigned char *bytes = (const unsigned char *)&value;
    for (size_t i = 0; i < sizeof value; ++i) {
        printf("%02X%s", (unsigned int)bytes[i],
               i + 1 == sizeof value ? "\n" : " ");
    }
    /* 1 バイトの中は上位ビット（bit 7）から表示する */
    unsigned char byte = 1;
    for (int bit = 7; bit >= 0; --bit) {
        putchar((byte & (1u << bit)) != 0 ? '1' : '0');
    }
    putchar('\n');
    return 0;
}
