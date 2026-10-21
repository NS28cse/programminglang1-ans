/*
 * 第8回 課題2　別解：候補を局所変数に持ち，最後に 1 回ずつ書き込む（MinMax / versions/min_max_local.c）
 * 走査の間は関数内の lo，hi を更新し，全要素を読み終えてから *low と *high へ書き込む．
 */
#include <stdio.h>
/*
 * 契約（呼び出し側の責任）:
 *   - n は 1 以上で，a から少なくとも n 要素を読める
 *   - low と high は互いに異なる有効な int を指し，a の要素とも重ならない
 */
void min_max(const int *a, int n, int *low, int *high)
{
    int lo = a[0];   /* 0 ではなく最初の要素で両候補を初期化する */
    int hi = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < lo) {
            lo = a[i];
        }
        if (a[i] > hi) {
            hi = a[i];
        }
    }
    /* 出力先へ書くのは読み終えた後の 1 回ずつだけ */
    *low = lo;
    *high = hi;
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
