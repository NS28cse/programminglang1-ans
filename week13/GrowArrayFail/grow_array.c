// 第13回 発展1「realloc の失敗を模擬する」（GrowArrayFail / grow_array.c）
// GrowArray のコピーで，realloc の呼び出しを試験用の try_resize（simulate_failure = 1）に置き換えたもの。
// 再確保に失敗しても元の領域が残っていること（p[0] が 1 のまま）を確かめてから解放して終了する。
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

// 試験用の再確保関数：simulate_failure が 1 なら realloc を呼ばずに NULL を返す（元の領域はそのまま）
static void *try_resize(void *old, size_t bytes)
{
    const int simulate_failure = 1;
    if (simulate_failure) {
        return NULL;
    }
    return realloc(old, bytes);
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
    print_array("calloc", p, old_n);
    for (size_t i = 0; i < old_n; ++i) {
        p[i] = (int)i + 1;
    }
    print_array("before", p, old_n);

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

    int *next = try_resize(p, new_n * sizeof *p);
    if (next == NULL) {
        // 再確保が失敗した経路だけで元の領域を読む：p はまだ有効で，p[0] は 1 のまま
        fprintf(stderr, "reallocation failed\n");
        printf("p[0]=%d\n", p[0]);     // free する直前に表示する
        free(p);
        return 1;
    }
    p = next;
    next = NULL;

    for (size_t i = old_n; i < new_n; ++i) {
        p[i] = (int)i + 1;
    }
    print_array("after", p, new_n);

    free(p);
    p = NULL;
    return 0;
}
