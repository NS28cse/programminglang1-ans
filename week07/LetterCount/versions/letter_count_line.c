// 第7回 課題2　別解：1 行を配列へ読み込んでから数える（LetterCount / versions/letter_count_line.c）
// fgets で 1 行を配列に保存し，配列の先頭から改行または終端までの英字を数える。
#include <stdio.h>
int main(void)
{
    char line[1002]; // 入力は 1 行 1000 バイト以内。本文 1000 バイト＋改行＋終端まで入る容量にする
    int count = 0;
    // 1 文字も読めずに入力が終了したときは NULL。行がないので 0 個として表示する
    if (fgets(line, sizeof line, stdin) != NULL) {
        // 改行が入っていればそこで，改行なしで入力が終了したなら終端で止める
        for (size_t i = 0; line[i] != '\n' && line[i] != '\0'; ++i) {
            if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')) {
                ++count;
            }
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    printf("%d\n", count);
    return 0;
}
