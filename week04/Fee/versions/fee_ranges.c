// 第4回 課題1　別解：各区分を下限と上限の両方で書き，条件を互いに重ならないようにする（Fee / versions/fee_ranges.c）
// どの条件も前の条件の結果に頼らないので，別々の if でも，並べる順番を変えても，真になるのは 1 つだけ．
#include <stdio.h>

int main(void)
{
    int age = 17;

    if (age < 0) {
        printf("invalid\n");
    }
    if (age >= 0 && age <= 5) {     // 0〜5 歳
        printf("0\n");
    }
    if (age >= 6 && age <= 17) {    // 6〜17 歳
        printf("500\n");
    }
    if (age >= 18) {                // 18 歳以上
        printf("1000\n");
    }
    return 0;
}
