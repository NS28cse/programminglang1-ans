/* 第10回 課題3 Binary: 4 バイトを bytes.bin へバイナリで書き，読み返して 16 進数で表示する
   講義の binary.c の data を UTF-8 の「あ」と LF（E3 81 82 0A）へ置き換えた最終版 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
    /* ソースに日本語を直接書かずに，UTF-8 のバイト列として指定する（BOM は付けない） */
    const unsigned char data[] = {0xE3, 0x81, 0x82, 0x0A};
    /* wb: 既存の bytes.bin は上書き。b なので 0A を CRLF に変換しない */
    FILE *fp = fopen("bytes.bin", "wb");
    if (fp == NULL) { perror("fopen"); return 1; }
    size_t written = fwrite(data, 1, sizeof data, fp);
    int closed = fclose(fp);
    if (written != sizeof data || closed == EOF) {
        fprintf(stderr, "write error\n");
        return 1;
    }
    fp = fopen("bytes.bin", "rb");
    if (fp == NULL) { perror("fopen"); return 1; }
    unsigned char buffer[16];
    /* size=1 なので戻り値 n は読めたバイト数。buffer の n 個目以降は使わない */
    size_t n = fread(buffer, 1, sizeof buffer, fp);
    int failed = ferror(fp);
    closed = fclose(fp);
    if (failed || closed == EOF) {
        fprintf(stderr, "read error\n");
        return 1;
    }
    for (size_t i = 0; i < n; ++i) {
        printf("%02X%s", (unsigned int)buffer[i], i + 1 == n ? "\n" : " ");
    }
    return 0;
}
