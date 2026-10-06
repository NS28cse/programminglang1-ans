/* 第3回 課題2 前置・後置と複合代入（Update） */
#include <stdio.h>

int main(void)
{
    int x = 5;
    int before = x++;  /* 式の値は増加前の x。次の文へ進む前に x は1増えている */
    int after = ++x;   /* 式の値は増加後の x */
    /* 更新と表示は別の文に分ける（printf の引数で x++ や ++x を使わない） */
    printf("before=%d after=%d x=%d\n", before, after, x);

    /* その時点の x を順に更新する: 3を加算して保存し，さらに2倍して保存する */
    x += 3;
    x *= 2;
    printf("final x=%d\n", x);
    return 0;
}
