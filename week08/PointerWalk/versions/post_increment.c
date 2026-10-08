/*
 * 第8回 確認問題4 の確かめ（PointerWalk の書き換え版 post_increment としてテストする）
 * (*p)++ は指す先の値を 1 増やし（p は動かない），*p++ は *(p++) で p 自体を次の要素へ進める．
 * どちらも式の値は変更前のもの．配列 v の範囲内だけを読み書きする．
 */
#include <stdio.h>
int main(void)
{
    int v[3] = {10, 20, 30};
    int *p = v;
    int r1 = (*p)++;
    printf("(*p)++: value=%d v[0]=%d p_is_v0=%d\n", r1, v[0], p == &v[0]);
    int r2 = *p++;
    printf("*p++:   value=%d v[0]=%d p_is_v1=%d\n", r2, v[0], p == &v[1]);
    return 0;
}
