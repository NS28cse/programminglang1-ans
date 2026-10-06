// 第9回 課題2　表示順を変更する（Names / names.c）
// ポインタ配列の要素（ポインタ値）を交換する。表の3ケースはそれぞれ初期状態の別の配列で試す。文字列本体はコピーも変更もしない。
#include <stdio.h>
#include <string.h>

enum { COUNT = 3 };

/* names[i] と names[j] のポインタ値を交換する。i, j は 0〜COUNT-1（同じ添字でもよい）。
   仮引数 const char *names[] は const char **names と同じ型 */
void swap_names(const char *names[], int i, int j)
{
    const char *temp = names[i];
    names[i] = names[j];
    names[j] = temp;
}

void print_names(const char *names[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%s\n", names[i]);
    }
}

int main(void)
{
    const char *names[] = {"Tokyo", "Osaka", "Nagoya"};
    swap_names(names, 0, 2);
    printf("swap_names(names, 0, 2):\n");
    print_names(names, COUNT);

    const char *same[] = {"Tokyo", "Osaka", "Nagoya"};
    swap_names(same, 1, 1);
    printf("swap_names(same, 1, 1):\n");
    print_names(same, COUNT);

    const char *twice[] = {"Tokyo", "Osaka", "Nagoya"};
    swap_names(twice, 0, 2);
    swap_names(twice, 0, 2);
    printf("swap_names(twice, 0, 2) x2:\n");
    print_names(twice, COUNT);

    /* -city は表示に付けただけで，文字列本体は変わらない */
    for (int i = 0; i < COUNT; ++i) {
        printf("%s-city\n", names[i]);
    }
    for (int i = 0; i < COUNT; ++i) {
        printf("%s %zu\n", names[i], strlen(names[i]));
    }

    /* 文字を変更するときは，変更可能な char 配列を用意してそれを指す */
    char city0[] = "Tokyo";
    char city1[] = "Osaka";
    char *editable[] = {city0, city1};
    editable[0][0] = 't';
    printf("%s %s\n", city0, editable[0]);
    return 0;
}
