// 第4回 発展 switch と if を比較する（YearGroup）の switch 版
// school_year が 1 か 2 なら lower years，3 か 4 なら upper years，それ以外なら invalid を表示する．
#include <stdio.h>

int main(void)
{
    int school_year = 1;    // 入力の代わりの固定値（0〜5 に変えて確かめる）

    switch (school_year) {
    case 1:                 // 処理を書かずに次の case へ続け，1 と 2 で同じ処理を共有する
    case 2:
        printf("lower years\n");
        break;              // これがないと次の case の文へ続けて実行する（フォールスルー）
    case 3:
    case 4:
        printf("upper years\n");
        break;
    default:
        printf("invalid\n");
        break;
    }
    return 0;
}
