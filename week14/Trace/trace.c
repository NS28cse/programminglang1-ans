/* 第14回 課題2 再帰の復帰順（Trace）
 * 講義の trace.c。n は引数で変えられる（引数なしなら講義と同じ 3）。例: Trace 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* 0〜n の合計を返す。n は 0〜100 を前提とする（最大 5050 は int に収まる） */
int sum_to(int n)
{
    printf("enter %d\n", n);           /* 呼び出し時: 再帰より前なので 3,2,1,0 の順 */
    if (n == 0) {
        printf("leave 0: 0\n");
        return 0;
    }
    int result = n + sum_to(n - 1);    /* 子が戻るまで result の初期化は終わらない */
    printf("leave %d: %d\n", n, result); /* 復帰時: 0,1,2,3 の順 */
    return result;
}

int main(int argc, char *argv[])
{
    long input = 3;
    if (argc > 2) {
        fprintf(stderr, "usage: Trace [n]\n");
        return 1;
    }
    if (argc == 2) {
        char *end;
        errno = 0;
        input = strtol(argv[1], &end, 10);
        if (argv[1] == end || *end != '\0' || errno == ERANGE) {
            input = -1;                /* 整数でなければ下の範囲検査で拒否する */
        }
    }
    /* sum_to へ負数や 101 以上を渡さない（enter は表示されない） */
    if (input < 0 || input > 100) {
        fputs("n must be 0..100\n", stderr);
        return 1;
    }
    int n = (int)input;
    int result = sum_to(n);
    printf("sum=%d\n", result);
    return 0;
}
