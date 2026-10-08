// 第4回 課題2 偶数の合計（EvenSum）の while 版（比較用）
// for の初期化をループの前へ，更新を本体の最後へ移した．
#include <stdio.h>

int main(void)
{
    int n = 10;
    int sum = 0;

    int i = 1;                  // for の初期化
    while (i <= n) {            // for の継続条件
        if (i % 2 == 0) {
            sum += i;
        }
        ++i;                    // for の更新（本体の最後）
    }
    printf("%d\n", sum);
    return 0;
}
