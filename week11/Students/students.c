// 第11回 課題2: Student 配列の平均，構造体全体の交換，名前と点数による比較
#include <stdio.h>
#include <string.h>
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
// 名前（文字列の内容）と点数がともに一致すれば同じ学生とみなす
int same_student(Student left, Student right)
{
    return strcmp(left.name, right.name) == 0 &&
           left.score == right.score;
}
int main(void)
{
    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 90}}; // 点数は 0〜100
    int n = 3; // 平均に使う人数（1〜3）。4 や 0 にはしない
    printf("average=%.1f\n", average(a, n));
    Student first = a[0]; // 交換前の 1 人目のコピー（名前の配列も含む）
    // 名前と点数を 1 人分まとめて交換する
    Student temp = a[0];
    a[0] = a[2];
    a[2] = temp;
    for (int i = 0; i < COUNT; ++i) {
        printf("%s %d\n", a[i].name, a[i].score);
    }
    printf("average after swap=%.1f\n", average(a, n));
    printf("same as first: a[0]=%d a[2]=%d\n",
           same_student(first, a[0]), same_student(first, a[2]));
    return 0;
}
