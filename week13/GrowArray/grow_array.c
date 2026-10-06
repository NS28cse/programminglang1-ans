// 第13回 発展1　calloc と realloc で配列を拡張する（GrowArray / grow_array.c）
// 起動引数 old_n new_n（各 1〜1000）を受け取り，old_n 要素を calloc して 0 を確認してから 1〜old_n を代入する。
// その後 realloc で new_n 要素へ変更し，増えた部分だけを old_n+1〜new_n で初期化して表示する。
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define MAX_COUNT 1000

// text 全体を 10 進の long へ変換できれば *out に保存して 1，できなければ 0 を返す（*out は変更しない）
static int parse_long(const char *text, long *out)
{
    char *end;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (text == end || *end != '\0' || errno == ERANGE) {
        return 0;
    }
    *out = value;
    return 1;
}

// p[0]〜p[n-1] を「label: 値 値 ...」の形で 1 行に表示する（配列は借りるだけ）
static void print_array(const char *label, const int *p, size_t n)
{
    printf("%s:", label);
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", p[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: GrowArray old_n new_n (1..1000)\n");
        return 1;
    }
    long old_count, new_count;
    if (!parse_long(argv[1], &old_count) || !parse_long(argv[2], &new_count)) {
        fprintf(stderr, "counts must be integers\n");
        return 1;
    }

    // 最初の確保の前に old_n を検査する（ここで失敗しても解放するものはない）
    if (old_count < 1 || old_count > MAX_COUNT) {
        fprintf(stderr, "old_n must be 1..1000\n");
        return 1;
    }
    size_t old_n = (size_t)old_count;
    int *p = calloc(old_n, sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    print_array("calloc", p, old_n);    // calloc は全ビット 0 なので int はすべて 0
    for (size_t i = 0; i < old_n; ++i) {
        p[i] = (int)i + 1;
    }
    print_array("before", p, old_n);

    // realloc の前に新しい個数とバイト数を検査する。ここからの失敗では元の領域を解放して終わる
    if (new_count < 1 || new_count > MAX_COUNT) {
        fprintf(stderr, "new_n must be 1..1000\n");
        free(p);
        return 1;
    }
    size_t new_n = (size_t)new_count;
    if (new_n > SIZE_MAX / sizeof *p) {
        fprintf(stderr, "size overflow\n");
        free(p);
        return 1;
    }

    // 結果は別の変数で受け取り，成功するまで p を上書きしない
    int *next = realloc(p, new_n * sizeof *p);
    if (next == NULL) {
        fprintf(stderr, "reallocation failed\n");
        free(p);                        // 失敗時も元の領域は有効なので解放する
        return 1;
    }
    p = next;                           // 成功後は返されたポインタだけを使う
    next = NULL;

    // 増えた部分 p[old_n]〜p[new_n-1] は未初期化なので，読む前に代入する（縮小時は 0 回）
    for (size_t i = old_n; i < new_n; ++i) {
        p[i] = (int)i + 1;
    }
    print_array("after", p, new_n);

    free(p);
    p = NULL;
    return 0;
}
