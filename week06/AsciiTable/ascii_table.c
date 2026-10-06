// 第6回 課題2 補足：ASCIIの印字可能な範囲（AsciiTable / ascii_table.c）
// 0〜31 と 127 は制御用なので表示しない。32 はスペースなのでコロンの後ろは見えない。
#include <stdio.h>
int main(void)
{
    for (int code = 32; code <= 126; ++code) {
        printf("%3d : %c\n", code, code);
    }
    return 0;
}
