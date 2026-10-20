// 第5回 課題1　別解：最大値の位置を持つ（Maximum / versions/max_index.c）
// 候補を値ではなく添字 best_index で持ち，a[best_index] と比べる。最後に a[best_index] を返す。
#include <stdio.h>

enum { COUNT = 5 };

int max_score(const int a[], int n);

int main(void)
{
    int scores[COUNT] = {72, 85, 60, 93, 80};
    int best = max_score(scores, COUNT);
    printf("max=%d\n", best);
    return 0;
}

// 契約: n は 1 以上で，a から n 個の要素を読めること。a の要素は書き換えない（const）。
int max_score(const int a[], int n)
{
    int best_index = 0;  // 添字 0 の要素を最初の候補にするので，比較は添字 1 から
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[best_index]) {
            best_index = i;  // 等しい値では更新しないので，最大値が複数あれば最初の位置が残る
        }
    }
    return a[best_index];  // 全要素を調べ終えてから，その位置の値を返す
}
