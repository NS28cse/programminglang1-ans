// 第4回 確認問題8 講義の goto の例（YearGroup / versions/goto_done.c）
// n が 3 になったら，for の直後にあるラベル done へ移動する（この回の課題では goto を使わない）．
#include <stdio.h>

int main(void)
{
    for (int n = 0; n < 5; ++n) {
        if (n == 3) {
            goto done;
        }
        printf("%d\n", n);
    }
done:
    printf("done\n");
    return 0;
}
