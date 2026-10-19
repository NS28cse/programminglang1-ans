// デバッグ題材: 動的配列（第13回）
// 起動引数で受け取った個数 n（1〜1000）だけ int を動的に確保し，1〜n を書き込んで，
// 各要素と合計を表示してから解放する。
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: BugMallocSize count (1..1000)\n");
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

    size_t n = (size_t)count;
    int *values = malloc(n);
    if (values == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < n; ++i) {
        values[i] = (int)i + 1;
    }
    long long sum = 0;
    printf("values:");
    for (size_t i = 0; i < n; ++i) {
        printf(" %d", values[i]);
        sum += values[i];
    }
    printf("\nsum=%lld\n", sum);

    free(values);
    return 0;
}
