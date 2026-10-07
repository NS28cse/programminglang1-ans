// 第9回 課題2　表示順を変更する（Names / names.c）
// ポインタ配列の要素（ポインタ値）を交換する。文字列本体はコピーも変更もしない。
// 表の他の呼び出し・-city の表示・変更可能な配列の例は CMakeLists.txt の variant でテストする。
#include <stdio.h>

// names[i] と names[j] のポインタ値を交換する。i, j は 0〜2（同じ添字でもよい）。
// 仮引数 const char *names[] は const char **names と同じ型
void swap_names(const char *names[], int i, int j)
{
    const char *temp = names[i];
    names[i] = names[j];
    names[j] = temp;
}

int main(void)
{
    const char *names[] = {"Tokyo", "Osaka", "Nagoya"};
    swap_names(names, 0, 2);
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", names[i]);
    }
    return 0;
}
