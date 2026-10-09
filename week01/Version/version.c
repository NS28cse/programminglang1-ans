// 第1回 課題4　ソースファイルと実行ファイル（Version / version.c）
// 手順3 の後の内容で，"Version B" を表示する（手順1 では "Version A" を表示する）。
// 保存だけでは Version.exe は変わらず，再ビルド後に Version B と表示される。
#include <stdio.h>

int main(void)
{
    printf("Version B\n");
    return 0;
}
