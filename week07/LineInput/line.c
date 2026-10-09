// 第7回 課題3　行の容量（LineInput / line.c）
// 講義の line.c。1 行を char line[32] へ読み込み，本文の長さと内容を表示する。
// 本文が 31 バイトを超えた行と，1 行も読めなかった場合は stderr へ診断を出して終了コード 1 で終わる。
#include <stdio.h>
#include <string.h>
int main(void)
{
    char line[32]; // 本文は最大 31 バイト＋終端（改行まで入るのは本文 30 バイト以下）
    printf("Text: ");
    fflush(stdout); // 改行のない入力案内を先に送り出す
    if (fgets(line, sizeof line, stdin) == NULL) {
        // 1 文字も読めずに入力が終了した（または読み取りエラー）
        fprintf(stderr, "No line read.\n");
        return 1;
    }
    size_t n = strlen(line); // fgets の成功を確認した後なので終端がある
    if (n > 0 && line[n - 1] == '\n') {
        line[--n] = '\0'; // 改行を終端に置き換え，本文の長さにする
    } else {
        // 改行が入らなかった: ちょうど 31 バイトか，超過か，改行なしで終了したか
        int ch;
        int extra = 0; // 改行・EOF 以外の文字が残っていたら 1
        while ((ch = getchar()) != '\n' && ch != EOF) {
            extra = 1;
        }
        if (extra) {
            fprintf(stderr, "Line too long.\n");
            return 1;
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        return 1;
    }
    printf("length=%zu text=%s\n", n, line);
    return 0;
}
