// 第9回 課題1　見つからない場合（FindMax / double_pointer.c。講義の例題そのもの）
// 演習ページの書き換え（n の変更・同点・失敗時・二重ポインタの断片）は CMakeLists.txt の variant でテストする。
#include <stdio.h>
// 最大要素の場所を *out へ書き，成功なら1，n<=0 なら0を返す。
// 契約: out には書き込み可能な int * 変数のアドレスを渡す。n は実際の要素数以下（関数側では検査できない）。
int find_max(int a[], int n, int **out)
{
    *out = NULL;  // 失敗したときに以前の結果を残さない
    if (n <= 0) { return 0; }
    int *best = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > *best) { best = &a[i]; }  // > なので，同点なら最初の要素のまま
    }
    *out = best;
    return 1;
}
int main(void)
{
    int a[] = {7, 12, 4};
    int *answer = NULL;
    if (find_max(a, 3, &answer)) {  // *answer を使うのは成功したときだけ
        printf("max=%d\n", *answer);
        *answer = 99;
    }
    printf("a[1]=%d\n", a[1]);
    const char *names[] = {"red", "green", "blue"};
    const char *temp = names[0];
    names[0] = names[2];
    names[2] = temp;
    for (int i = 0; i < 3; ++i) { printf("%s\n", names[i]); }
    return 0;
}
