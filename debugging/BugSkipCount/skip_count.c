// デバッグ題材: 3 の倍数を飛ばす（第4回）
// 1 から n までの整数のうち 3 の倍数でないものを 1 行に 1 つ表示し，最後にその個数を表示する。
#include <stdio.h>

int main(void)
{
    int n = 10;
    int count = 0;
    int i = 1;

    while (i <= n) {
        if (i % 3 == 0) {
            continue;
        }
        printf("%d\n", i);
        ++count;
        ++i;
    }
    printf("count=%d\n", count);
    return 0;
}
