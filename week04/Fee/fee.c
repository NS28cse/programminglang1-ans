// 第4回 課題1 料金を分類する（Fee）
// 年齢 age から料金を表示する．負の年齢を最初に invalid として除き，残りを小さい区分から調べる．
#include <stdio.h>

int main(void)
{
    int age = 17;   // 入力の代わりの固定値（-1, 0, 5, 6, 17, 18 に変えて確かめる）

    if (age < 0) {
        printf("invalid\n");
    } else if (age <= 5) {      // 0〜5 歳
        printf("0\n");
    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）
        printf("500\n");
    } else {                    // 残りは 18 歳以上だけ
        printf("1000\n");
    }
    return 0;
}
