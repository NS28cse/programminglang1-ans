// 第5回 課題3 の検証用（ValueCopyCases / valuecopy_cases.c）
// 演習ページの独立した実験を，それぞれ別のブロックで行う。
// 各ブロックの x は別の局所変数なので，どの実験も初期値から始まる。
#include <stdio.h>

int increment(int x)
{
    x = x + 1;
    return x;
}

int main(void)
{
    {
        int x = 10;
        int y = increment(x);
        printf("original x=10: %d %d\n", x, y);
    }
    {
        int x = 0;
        int y = increment(x);
        printf("original x=0: %d %d\n", x, y);
    }
    {
        int x = -1;
        int y = increment(x);
        printf("original x=-1: %d %d\n", x, y);
    }
    {
        int x = 10;
        increment(x);  // 戻り値 11 は使われずに捨てられる
        printf("increment(x); -> x=%d\n", x);
    }
    {
        int x = 10;
        int y = increment(x);
        printf("int y = increment(x); -> x=%d y=%d\n", x, y);
    }
    {
        int x = 10;
        x = increment(x);  // 戻り値を代入したので main の x が変わる
        printf("x = increment(x); -> x=%d\n", x);
    }
    {
        int x = 10;
        int y = increment(x);
        int z = increment(x);
        printf("add z: x=%d y=%d z=%d\n", x, y, z);
    }
    {
        int x = 10;
        x = increment(x);
        x = increment(x);
        printf("x = increment(x); twice -> x=%d\n", x);
    }
    return 0;
}
