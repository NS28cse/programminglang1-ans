// 第2回 課題2 型と表示の対応（Profile / profile.c）
// 整数は int と %d，小数は double と %f，1 文字は char と %c を対応させる
#include <stdio.h>

int main(void)
{
    int count = 3;
    double price = 125.5;
    char grade = 'B';               // 1 文字はシングルクォートで囲む
    double total = count * price;   // int と double の積は double になる

    // %.2f は表示する桁数の指定であり，変数の値は変えない
    printf("count=%d price=%.2f grade=%c\n", count, price, grade);
    printf("total=%.2f\n", total);
    return 0;
}
