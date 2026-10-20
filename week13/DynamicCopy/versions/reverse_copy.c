// 第13回 課題2「追加：独立したコピー」　別解：逆順に読みながらコピーする（DynamicCopy / versions/reverse_copy.c）
// copy[i] に values[n - 1 - i] を入れれば，コピーと逆順が 1 回の走査で済み，交換も temp も要らない。
// 所有する領域は values と copy の 2 つ（本体と同じ）。
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // (1) 引数の個数と数値を調べる
    if (argc != 2) {
        fprintf(stderr, "usage: DynamicCopy count (1..1000)\n");
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

    // (2) 有効な要素数へ変換する
    size_t n = (size_t)count;
    int *values = NULL;
    int *copy = NULL;

    // (3) 必要バイト数を表せるかを調べる（copy も同じ int 配列なので，この検査で足りる）
    if (n > SIZE_MAX / sizeof *values) {
        fprintf(stderr, "size overflow\n");
        return 1;
    }

    // (4) 領域を確保し，失敗なら要素を使わず終了する
    values = malloc(n * sizeof *values);
    if (values == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }

    // (5) 値を書き込んでから合計を計算する
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        values[i] = (int)i + 1;
        sum += values[i];
    }
    printf("n=%zu sum=%lld mean=%.1f\n", n, sum, (double)sum / (double)n);

    // 独立したコピー：ポインタではなく要素をコピーするため，別の領域を確保する
    copy = malloc(n * sizeof *copy);
    if (copy == NULL) {
        fprintf(stderr, "allocation failed\n");
        free(values);   // 先に確保した values はこの経路でも解放する
        return 1;
    }
    // copy の先頭から順に，values を末尾から読んで入れる（values は読むだけなので元の順序のまま残る）
    for (size_t i = 0; i < n; ++i) {
        copy[i] = values[n - 1 - i];
    }

    printf("values:");
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", values[i]);
    }
    printf("\n");
    printf("copy:");
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", copy[i]);
    }
    printf("\n");

    // (6) 2 つの領域をそれぞれ解放する
    free(copy);
    copy = NULL;
    free(values);
    values = NULL;
    return 0;
}
