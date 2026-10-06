// 第13回 発展1「realloc の失敗を模擬する」（GrowArrayFail / grow_array.c）
// GrowArray のコピー。realloc の呼び出しだけを試験用の try_resize に置き換え（simulate_failure = 1），
// 再確保に失敗しても元の領域が残っていること（p[0] が 1 のまま）を確かめてから解放して終了する。
// 正常版は GrowArray フォルダに残してある。
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

// 試験用の再確保関数：simulate_failure が 1 なら realloc を呼ばずに NULL を返す（元の領域はそのまま）
static void *try_resize(void *old, size_t bytes)
{
    const int simulate_failure = 1;
    if (simulate_failure) {
        return NULL;
    }
    return realloc(old, bytes);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: GrowArrayFail old_n new_n (1..1000)\n");
        return 1;
    }
    long old_count, new_count;
    if (!parse_long(argv[1], &old_count) || !parse_long(argv[2], &new_count)) {
        fprintf(stderr, "counts must be integers\n");
        return 1;
    }

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
    print_array("calloc", p, old_n);
    for (size_t i = 0; i < old_n; ++i) {
        p[i] = (int)i + 1;
    }
    print_array("before", p, old_n);

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

    int *next = try_resize(p, new_n * sizeof *p);
    if (next == NULL) {
        // 再確保が失敗した経路だけで元の領域を読む：p はまだ有効で，p[0] は 1 のまま
        printf("p[0]=%d\n", p[0]);
        fprintf(stderr, "reallocation failed\n");
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
