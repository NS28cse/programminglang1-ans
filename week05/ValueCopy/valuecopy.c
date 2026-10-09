// 第5回 課題3　値渡しを確認する（ValueCopy / valuecopy.c）
// 演習ページのプログラムそのもの。increment に x を渡し，main の x と戻り値 y を表示する。
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
    printf("%d %d\n", x, y);
    return 0;
}
