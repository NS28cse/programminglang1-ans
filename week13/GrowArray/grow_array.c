// 第13回 発展1　calloc と realloc で配列を拡張する（GrowArray / grow_array.c）
// old_n = 3 要素を calloc して 0 を確認してから 1〜old_n を代入し，realloc で new_n = 5 要素へ拡張して，
// 増えた部分だけを old_n+1〜new_n で初期化して表示する。境界の表の組は old_n，new_n の値を書き換えて試す。
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum { MAX_COUNT = 1000 };

// p[0]〜p[n-1] を「label: 値 値 ...」の形で 1 行に表示する（配列は借りるだけ）
static void print_array(const char *label, const int *p, size_t n)
{
    printf("%s:", label);
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", p[i]);
    }
    printf("\n");
}

int main(void)
{
    size_t old_n = 3;   // 元の個数（境界の表の値に書き換えて試す）
    size_t new_n = 5;   // 変更後の個数

    // 最初の確保の前に old_n を検査する（ここで失敗しても解放するものはない）
    if (old_n == 0 || old_n > MAX_COUNT) {
        fprintf(stderr, "old_n must be 1..%d\n", MAX_COUNT);
        return 1;
    }
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
    if (new_n == 0 || new_n > MAX_COUNT) {
        fprintf(stderr, "new_n must be 1..%d\n", MAX_COUNT);
        free(p);
        return 1;
    }
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
