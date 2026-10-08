// 第11回 課題2: Student 配列の平均と，構造体全体の代入による 1 人分の交換
#include <stdio.h>
enum { COUNT = 3 };
typedef struct {
    char name[16];
    int score;
} Student;
// a は Student 配列の先頭へのポインタ（3 人分がコピーされるのではない）。
// 1 <= n <= 3 で，n 人分のデータがあることを呼び出し側が約束する
double average(const Student a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i].score;
    }
    return (double)sum / n; // 整数どうしの割り算にしない
}
int main(void)
{
    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 90}}; // 点数は 0〜100
    int n = 3; // 平均に使う人数（1〜3）。4 や 0 にはしない
    printf("average=%.1f\n", average(a, n));
    // 名前と点数を 1 人分まとめて交換する
    Student temp = a[0];
    a[0] = a[2];
    a[2] = temp;
    for (int i = 0; i < COUNT; ++i) {
        printf("%s %d\n", a[i].name, a[i].score);
    }
    printf("average after swap=%.1f\n", average(a, n));
    return 0;
}
