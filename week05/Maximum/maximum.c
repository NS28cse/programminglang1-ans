// 第5回 課題1　最大の点数（Maximum / maximum.c）
// 配列の最大値を返す関数 max_score を作り，main で戻り値を表示する。
#include <stdio.h>

enum { COUNT = 5 };

int max_score(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int best = max_score(scores, COUNT);  // 要素数は自動では伝わらないので COUNT を渡す
    printf("max=%d\n", best);
    return 0;
}

// 契約: n は 1 以上で，a から n 個の要素を読めること。a の要素は書き換えない（const）。
int max_score(const int a[], int n)
{
    int best = a[0];  // 候補を最初の要素で初期化するので，比較は添字 1 から
    for (int i = 1; i < n; ++i) {
        if (a[i] > best) {
            best = a[i];
        }
    }
    return best;  // 全要素を調べ終えてから返す
}
