/* 第3回 課題5（発展） 権限フラグ（Flags） */
#include <stdio.h>

int main(void)
{
    /* ビット操作は符号なしの unsigned int で行う。シフト数は0〜2だけ */
    unsigned int read_mask = 1u << 0;   /* ビット0: 読む権限 */
    unsigned int write_mask = 1u << 1;  /* ビット1: 書く権限 */
    unsigned int exec_mask = 1u << 2;   /* ビット2: 実行する権限 */
    unsigned int flags = 1u;            /* 初期値: 読む権限だけ */
    printf("start=%u\n", flags);

    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */
    printf("set write=%u\n", flags);

    flags &= ~read_mask;  /* クリア: 対象ビットだけ0のマスクと AND */
    printf("clear read=%u\n", flags);

    flags ^= exec_mask;   /* 反転: XOR で対象ビットだけ反転する */
    printf("toggle exec=%u\n", flags);

    /* & は != より優先順位が低いので，(flags & exec_mask) を括弧で囲む */
    int can_exec = (flags & exec_mask) != 0;
    printf("exec=%d\n", can_exec);
    return 0;
}
