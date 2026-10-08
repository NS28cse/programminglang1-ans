/*
 * 第8回 課題2 MinMax: 最小値と最大値を 2 つの出力先ポインタへ書き込む
 * 契約（呼び出し側の責任）:
 *   - n は 1 以上で，a から少なくとも n 要素を読める
 *   - low と high は互いに異なる有効な int を指し，a の要素とも重ならない
 */
#include <stdio.h>
void min_max(const int *a, int n, int *low, int *high)
{
    /* 0 ではなく最初の要素で両候補を初期化する（全部が負の配列でも正しい） */
    *low = a[0];
    *high = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < *low) {
            *low = a[i];
        }
        if (a[i] > *high) {
            *high = a[i];
        }
    }
}
int main(void)
{
    int data[] = {7, -2, 9, 0};
    int low;   /* min_max が書き込んだ後に初めて読む */
    int high;
    min_max(data, 4, &low, &high);   /* 要素数を変えたら n も合わせる */
    printf("min=%d max=%d\n", low, high);
    return 0;
}
