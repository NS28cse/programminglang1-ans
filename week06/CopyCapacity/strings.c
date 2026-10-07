// 第6回 発展 容量の境界（CopyCapacity / strings.c）。講義の strings.c そのもの
// 演習で copy の容量を 4，3 に変えた版は CMakeLists.txt の variant でテストする。
// 容量 3 では "cat" と終端の4要素が入らないので，条件が偽になりコピー自体を行わない。
#include <stdio.h>
#include <string.h>
int main(void)
{
    char word[16] = "cat";
    char copy[16] = {0};
    size_t length = strlen(word);
    // 終端用の1要素を残せるとき（length + 1 <= sizeof copy）だけコピーする
    if (length < sizeof copy) {
        for (size_t i = 0; i <= length; ++i) {
            copy[i] = word[i];
        }
    }
    word[0] = 'C';
    printf("%s %s\n", word, copy);
    printf("length=%zu capacity=%zu\n", strlen(word), sizeof word);
    printf("equal=%d\n", strcmp(word, copy) == 0);
    int total = 7, count = 2;
    printf("mean=%.1f\n", (double)total / count);
    return 0;
}
