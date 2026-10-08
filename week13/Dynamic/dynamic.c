// 第13回 課題1・課題2　動的配列と逆順（Dynamic / dynamic.c）
// 起動引数の個数 n（1〜1000）だけ int を動的確保し，1〜n を書き込んで合計と平均を表示する。
// 課題2として，同じ領域の中で配列を逆順に並べ替えて表示してから解放する。
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // (1) 引数の個数と数値を調べる（数字がない・末尾に余計な文字・long の範囲外・1〜1000 以外を拒否）
    if (argc != 2) {
        fprintf(stderr, "usage: Dynamic count (1..1000)\n");
        return 1;
    }
    char *end;
    errno = 0;
    long count = strtol(argv[1], &end, 10);
    if (argv[1] == end || *end != '\0' || errno == ERANGE ||
        count < 1 || count > 1000) {
        fprintf(stderr, "count must be 1..1000\n");
        return 1;
    }

    // (2) 有効な要素数へ変換する（1 以上を確認済みなので，負数が size_t へ回り込むことはない）
    size_t n = (size_t)count;
    int *values = NULL;

    // (3) 必要バイト数 n * sizeof *values を表せるかを，掛け算の前に除算で調べる
    if (n > SIZE_MAX / sizeof *values) {
        fprintf(stderr, "size overflow\n");
        return 1;
    }

    // (4) 領域を確保し，失敗なら要素を使わず終了する（まだ何も確保していないので解放は不要）
    values = malloc(n * sizeof *values);
    if (values == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }

    // (5) 値を書き込んでから合計を計算する（有効な添字は 0〜n-1 なので i < n）
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        values[i] = (int)i + 1;
        sum += values[i];
    }
    printf("n=%zu sum=%lld mean=%.1f\n", n, sum, (double)sum / (double)n);

    // 課題2：先頭と末尾から組にして n/2 組だけ交換する（奇数個の中央の要素は動かさない）
    for (size_t i = 0; i < n / 2; ++i) {
        int temp = values[i];
        values[i] = values[n - 1 - i];
        values[n - 1 - i] = temp;
    }
    printf("reversed:");
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", values[i]);
    }
    printf("\n");

    // (6) 使い終わった領域を解放する（values は確保した先頭を指したまま）
    free(values);
    values = NULL;
    return 0;
}
