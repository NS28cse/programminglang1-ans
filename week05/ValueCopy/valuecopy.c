// 第5回 課題3　値渡しを確認する（ValueCopy / valuecopy.c）
// 演習ページのプログラムに，最初の呼び出しの後の int z = increment(x); を追加した最終版。
// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。
#include <stdio.h>

int increment(int x)
{
    x = x + 1;  // 変わるのは仮引数（コピー）だけ
    return x;
}

int main(void)
{
    int x = 10;
    int y = increment(x);
    int z = increment(x);  // x は 10 のままなので，z も 11
    printf("%d %d %d\n", x, y, z);
    return 0;
}
