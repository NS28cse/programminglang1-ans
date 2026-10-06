// 第9回 課題1　最大要素の場所を二重ポインタで返す（FindMax / double_pointer.c をもとにした最終版）
// 前半は講義の double_pointer.c と同じ。後半で演習の表（n の変更・同点・失敗時の出力・二重ポインタの代入）を順に試す。
#include <stdio.h>

/* 最大要素の場所を *out へ書き，成功なら1，n<=0 なら0を返す。
   契約: out には書き込み可能な int * 変数のアドレスを渡す。n は実際の要素数以下（関数側では検査できない）。 */
int find_max(int a[], int n, int **out)
{
    *out = NULL;  /* 失敗したときに以前の結果を残さない */
    if (n <= 0) { return 0; }
    int *best = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > *best) { best = &a[i]; }  /* > なので，同点なら最初の要素のまま */
    }
    *out = best;
    return 1;
}

/* 検索範囲の表：毎回 {7, 12, 4} の新しい配列で n だけを変えて試す */
void try_n(int n)
{
    int a[] = {7, 12, 4};
    int *answer = NULL;
    printf("n=%d: ", n);
    if (find_max(a, n, &answer)) {
        printf("found a[%td]=%d\n", answer - a, *answer);
        *answer = 99;  /* 成功したときだけ *answer を使う */
    } else {
        printf("not found, answer==NULL is %d\n", answer == NULL);
    }
    printf("  a = {%d, %d, %d}\n", a[0], a[1], a[2]);
}

/* 同点の扱い：{12, 12, 4} では最初の a[0] が選ばれる */
void try_tie(void)
{
    int a[] = {12, 12, 4};
    int *answer = NULL;
    if (find_max(a, 3, &answer)) {
        printf("tie: found a[%td]=%d\n", answer - a, *answer);
        printf("first=%d\n", answer == &a[0]);
    }
}

/* 失敗時に古い結果を残さない：answer を &a[1] にしてから n=0 で呼ぶ */
void try_stale(void)
{
    int a[] = {7, 12, 4};
    int *answer = &a[1];
    int ok = find_max(a, 0, &answer);
    printf("stale: return=%d answer==NULL is %d\n", ok, answer == NULL);
}

/* 二重ポインタの代入を追う：pp は最後まで p を指す */
void trace_double_pointer(void)
{
    int x = 10, y = 30;
    int *p = &x;
    int **pp = &p;
    **pp = 20;   /* p が指す x を変更 */
    printf("%d %d %d\n", x, y, p == &x);
    *pp = &y;    /* p 自身（指す先）を変更 */
    **pp = 40;   /* 今度は y を変更 */
    printf("%d %d %d\n", x, y, p == &y);
}

int main(void)
{
    int a[] = {7, 12, 4};
    int *answer = NULL;
    if (find_max(a, 3, &answer)) {
        printf("max=%d\n", *answer);
        *answer = 99;
    }
    printf("a[1]=%d\n", a[1]);
    const char *names[] = {"red", "green", "blue"};
    const char *temp = names[0];
    names[0] = names[2];
    names[2] = temp;
    for (int i = 0; i < 3; ++i) { printf("%s\n", names[i]); }

    try_n(3);
    try_n(1);
    try_n(0);
    try_n(-1);
    try_tie();
    try_stale();
    trace_double_pointer();
    return 0;
}
