// 第11回 課題2: Student 配列の平均，構造体全体の交換，名前と点数による比較
// 引数なしなら Aki=80, Ren=70, Mio=90 の 3 人の平均。
// 「Students n」で平均に使う人数（1〜3），「Students n s1 s2 s3」で点数（0〜100）も変えられる
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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
// 文字列全体を min〜max の整数として読めたら 1
int parse_int(const char *text, int min, int max, int *value)
{
    char *end;
    errno = 0;
    long v = strtol(text, &end, 10);
    if (text == end || *end != '\0' || errno == ERANGE || v < min || v > max) {
        return 0;
    }
    *value = (int)v;
    return 1;
}
int main(int argc, char *argv[])
{
    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 90}};
    int n = COUNT;
    if (argc != 1 && argc != 2 && argc != 2 + COUNT) {
        fprintf(stderr, "usage: Students [n [score1 score2 score3]]\n");
        return 1;
    }
    if (argc >= 2 && !parse_int(argv[1], 1, COUNT, &n)) {
        fprintf(stderr, "n must be an integer from 1 to %d\n", COUNT);
        return 1;
    }
    for (int i = 0; i + 2 < argc; ++i) {
        if (!parse_int(argv[i + 2], 0, 100, &a[i].score)) {
            fprintf(stderr, "score must be an integer from 0 to 100\n");
            return 1;
        }
    }
    printf("average=%.1f\n", average(a, n));
    Student first = a[0]; // 交換前の 1 人目のコピー（名前の配列も含む）
    Student temp = a[0]; // 名前と点数を 1 人分まとめて交換する
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
