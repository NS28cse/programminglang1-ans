// デバッグ題材: 点数から評価を決める（第5回）
// 配列の各点数（0〜100）について評価を表示する。80 以上は A，70 以上は B，60 以上は C，60 未満は D。
#include <stdio.h>

enum { COUNT = 6 };

char grade(int score);

int main(void)
{
    int scores[COUNT] = {95, 80, 74, 60, 59, 0};
    for (int i = 0; i < COUNT; ++i) {
        printf("%3d: %c\n", scores[i], grade(scores[i]));
    }
    return 0;
}

// 範囲: score は 0〜100
char grade(int score)
{
    if (score >= 60) {
        return 'C';
    } else if (score >= 70) {
        return 'B';
    } else if (score >= 80) {
        return 'A';
    }
    return 'D';
}
