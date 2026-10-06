// 第5回 課題1 の検証用（MaximumCases / maximum_cases.c）
// 演習ページの「異なる配列で確かめる」の表の配列をまとめて max_score に渡し，結果を表示する。
// max_score は Maximum/maximum.c と同じもの。
#include <stdio.h>

int max_score(const int a[], int n);
void print_case(const int a[], int n);

int main(void)
{
    int original[5] = {72, 85, 60, 93, 80};
    int zero[1] = {0};
    int same[3] = {60, 60, 60};
    int first[3] = {100, 20, 30};
    int last[3] = {20, 30, 100};

    print_case(original, 5);
    print_case(zero, 1);
    print_case(same, 3);
    print_case(first, 3);
    print_case(last, 3);
    return 0;
}

// 配列の内容・渡す n・max_score の戻り値を 1 行に表示する
void print_case(const int a[], int n)
{
    printf("{");
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", a[i]);
    }
    printf("} n=%d max=%d\n", n, max_score(a, n));
}

// 契約: n は 1 以上で，a から n 個の要素を読めること
int max_score(const int a[], int n)
{
    int best = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > best) {
            best = a[i];
        }
    }
    return best;
}
