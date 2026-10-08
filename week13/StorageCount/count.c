// 第13回 発展2　static 変数の寿命を確かめる（StorageCount / count.c）
// 関数内の static int count は静的記憶期間を持ち，プログラム開始前に 1 度だけ 0 に初期化される。
// そのため呼び出しの間も値が保持され，1，2，3 と表示される。ヒープは使わないので free もしない。
#include <stdio.h>

// 関数の前の static は内部リンケージ（この .c の中だけで使う関数）を表す
static int next_count(void)
{
    static int count = 0;   // この static は静的記憶期間（名前は関数内だけで使える）
    ++count;
    return count;
}

int main(void)
{
    for (int i = 0; i < 3; ++i) {
        printf("%d\n", next_count());
    }
    return 0;
}
