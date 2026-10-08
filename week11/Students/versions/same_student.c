// 第11回 課題2 名前を比較する（確認用）: 交換前の 1 人目のコピー first を，交換後の a[0]・a[2] と same_student で比べる
#include <stdio.h>
#include <string.h>
enum { COUNT = 3 };
typedef struct {
    char name[16];
    int score;
} Student;
// 名前（文字列の内容）と点数がともに一致すれば同じ学生とみなす（left == right とは書けない）
int same_student(Student left, Student right)
{
    return strcmp(left.name, right.name) == 0 &&
           left.score == right.score;
}
int main(void)
{
    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 90}};
    Student first = a[0]; // 交換前の 1 人目のコピー（名前の配列も含む）
    // 名前と点数を 1 人分まとめて交換する
    Student temp = a[0];
    a[0] = a[2];
    a[2] = temp;
    for (int i = 0; i < COUNT; ++i) {
        printf("%s %d\n", a[i].name, a[i].score);
    }
    // first と a[2] は別の保存場所だが，内容（名前と点数）が同じなので 1
    printf("same as first: a[0]=%d a[2]=%d\n",
           same_student(first, a[0]), same_student(first, a[2]));
    return 0;
}
