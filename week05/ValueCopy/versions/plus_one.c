// 第5回 確認問題5　戻り値を使うか（ValueCopy / versions/plus_one.c）
// 講義の plus_one で，戻り値を使わない・別の変数に保存する・同じ変数へ代入する，の 3 通りを比べる。
#include <stdio.h>

int plus_one(int value)
{
    value += 1;  // 変わるのは仮引数（コピー）だけ
    return value;
}

int main(void)
{
    int b = 10;
    plus_one(b);  // 戻り値 11 は捨てられ，b は 10 のまま
    printf("b=%d\n", b);
    int c = plus_one(b);
    printf("b=%d c=%d\n", b, c);
    b = plus_one(b);  // 戻り値を代入したので b が 11 になる
    printf("b=%d\n", b);
    return 0;
}
