// 第13回 課題2　別解：両端を指す 2 つのポインタを内側へ進めて交換する（Dynamic / versions/reverse_pointers.c）
// 交換の回数を n/2 と数える代わりに，先頭側と末尾側の位置が出会ったら止める。添字 n - 1 - i の計算も要らない。
// 走査には別のポインタ変数 left と right を使い，values 自身は先頭を指したまま動かさない。
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

    // 課題2：left は先頭，right は最後の要素（n は 1 以上なので values + n - 1 は確保した範囲内）を指す
    int *left = values;
    int *right = values + n - 1;
    while (left < right) {          // 出会ったら終わる（奇数個なら中央で left == right になり，交換しない）
        int temp = *left;
        *left = *right;
        *right = temp;
        ++left;
        --right;
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
