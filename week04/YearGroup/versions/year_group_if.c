// 第4回 発展 switch と if を比較する（YearGroup）の if・else if・else 版（比較用）
// switch 版と同じ区分を == と || の条件で書き，if・else if・else で 1 つだけ選ぶ．
#include <stdio.h>

int main(void)
{
    int school_year = 1;

    if (school_year == 1 || school_year == 2) {
        printf("lower years\n");
    } else if (school_year == 3 || school_year == 4) {
        printf("upper years\n");
    } else {
        printf("invalid\n");
    }
    return 0;
}
