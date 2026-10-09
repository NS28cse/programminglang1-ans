// 第9回 発展1　長さが異なる行を扱う（RaggedRows / versions/animal.c）
// 二重ポインタの別の使い方1: p が指すのはポインタ変数 animal の1個だけ（p を進めない）。
#include <stdio.h>
int main(void)
{
    const char *animal = "dog";
    const char **p = &animal;
    printf("%s\n", *p);
    *p = "cat";  // animal の指す先が変わる。"dog" の文字は変わらない
    printf("%s\n", animal);
    return 0;
}
