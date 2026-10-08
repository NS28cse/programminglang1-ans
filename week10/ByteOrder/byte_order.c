/* 第10回 課題3「バイト順を調べる」ByteOrder: unsigned short のメモリ上のバイト順を観察する
   講義の観察用断片（unsigned short value = 1）を別の main にした（演習ページの 2 進数表示の断片は variant bits_of_byte） */
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
