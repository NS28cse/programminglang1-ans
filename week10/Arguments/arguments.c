/* 第10回 課題2 Arguments: 引数を順に表示し，北陸3県の名前があれば最後に hokuriku! を 1 回だけ表示する */
#include <stdio.h>
#include <string.h>
enum { PREFECTURE_COUNT = 3 };
int is_hokuriku(const char *name);
int main(int argc, char *argv[])
{
    int found = 0;   /* 何個一致しても表示は 1 回なので，フラグにまとめる */
    for (int i = 1; i < argc; ++i) {   /* argv[0] はプログラム名なので 1 から */
        printf("arg%d=%s\n", i, argv[i]);
        if (is_hokuriku(argv[i])) {
            found = 1;
        }
    }
    if (found) {
        printf("hokuriku!\n");
    }
    return 0;
}
/* name が toyama・ishikawa・fukui のどれかと一致すれば 1（大文字小文字は区別する） */
int is_hokuriku(const char *name)
{
    const char *prefectures[PREFECTURE_COUNT] = {"toyama", "ishikawa", "fukui"};
    for (int i = 0; i < PREFECTURE_COUNT; ++i) {
        /* == はアドレスの比較になるので，内容は strcmp で比べる */
        if (strcmp(name, prefectures[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
