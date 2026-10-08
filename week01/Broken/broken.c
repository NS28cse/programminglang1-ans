#include <stdio.h>

int main(void)
{
    printf("I fixed the error!\n");     // 文の終わりに ; を追加した
    return 0;
}

// 第1回 課題3　エラーメッセージを読んで修正する（Broken / broken.c，修正後）
// 修正前は 5 行目の printf の呼び出しの末尾に ; がなく，C2143 などの構文エラーになった。
// 修正前のコードは ../_Broken/broken.c（ビルドしない）を参照。
// 行番号を演習ページのコード（1〜7 行目）と一致させるため，このコメントは末尾に置いた。
