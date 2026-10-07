/* 第10回 発展1 NumberFormats: 3 つの double をテキスト（numbers.txt）とバイナリ（numbers.bin）で保存して読み戻す */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
enum { COUNT = 3 };
int write_text(const char *filename, const double values[], int count);
int write_binary(const char *filename, const double values[], int count);
int read_text(const char *filename, double values[], int count);
int read_binary(const char *filename, double values[], int count);
int main(void)
{
    const double data[COUNT] = {0.5, 1.25, -2.0};
    double text_values[COUNT];
    double binary_values[COUNT];
    /* どれかが失敗したら，読み戻せなかった値は表示しない */
    if (!write_text("numbers.txt", data, COUNT) ||
        !write_binary("numbers.bin", data, COUNT) ||
        !read_text("numbers.txt", text_values, COUNT) ||
        !read_binary("numbers.bin", binary_values, COUNT)) {
        return 1;
    }
    printf("text=%.2f %.2f %.2f\n", text_values[0], text_values[1], text_values[2]);
    printf("binary=%.2f %.2f %.2f\n", binary_values[0], binary_values[1], binary_values[2]);
    return 0;
}
/* テキスト形式: 1 行目に個数，続く各行に値を小数点以下 2 桁で書く（ここで桁が失われる）。成功なら 1 */
int write_text(const char *filename, const double values[], int count)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    int failed = fprintf(fp, "%d\n", count) < 0;
    for (int i = 0; i < count && !failed; ++i) {
        if (fprintf(fp, "%.2f\n", values[i]) < 0) {
            failed = 1;
        }
    }
    if (fclose(fp) == EOF) {
        failed = 1;
    }
    if (failed) {
        fprintf(stderr, "write error: %s\n", filename);
        return 0;
    }
    return 1;
}
/* バイナリ形式: 個数 1 バイトの後に double のメモリ表現を count 個（同じ処理系で読み戻す専用）。成功なら 1 */
int write_binary(const char *filename, const double values[], int count)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    unsigned char header = (unsigned char)count;   /* count は COUNT（3）なので 1 バイトに収まる */
    int failed = fwrite(&header, 1, 1, fp) != 1 ||
                 fwrite(values, sizeof values[0], (size_t)count, fp) != (size_t)count;
    if (fclose(fp) == EOF) {
        failed = 1;
    }
    if (failed) {
        fprintf(stderr, "write error: %s\n", filename);
        return 0;
    }
    return 1;
}
/* テキスト形式を読み戻す。ヘッダの個数が配列の要素数 count と一致するときだけ値を読む。成功なら 1 */
int read_text(const char *filename, double values[], int count)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    int header;
    int ok = fscanf(fp, "%d", &header) == 1 && header == count;
    for (int i = 0; i < count && ok; ++i) {
        ok = fscanf(fp, "%lf", &values[i]) == 1;
    }
    if (ferror(fp)) {
        ok = 0;
    }
    if (fclose(fp) == EOF) {
        ok = 0;
    }
    if (!ok) {
        fprintf(stderr, "invalid data: %s\n", filename);
        return 0;
    }
    return 1;
}
/* バイナリ形式を読み戻す。fread の戻り値は「完全に読めた要素の個数」。成功なら 1 */
int read_binary(const char *filename, double values[], int count)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    unsigned char header;
    int ok = fread(&header, 1, 1, fp) == 1 && header == count &&
             fread(values, sizeof values[0], (size_t)count, fp) == (size_t)count;
    if (ferror(fp)) {
        ok = 0;
    }
    if (fclose(fp) == EOF) {
        ok = 0;
    }
    if (!ok) {
        fprintf(stderr, "invalid data: %s\n", filename);
        return 0;
    }
    return 1;
}
