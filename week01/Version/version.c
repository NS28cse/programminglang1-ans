// 第1回 課題4　ソースファイルと実行ファイル（Version / version.c，最終版）
// 手順1 では "Version A" を表示する版を作り，手順3 で "Version B" に変更して保存する。
// 保存だけでは Version.exe は変わらず，再ビルド後に Version B と表示される。
#include <stdio.h>

int main(void)
{
    printf("Version B\n");
    return 0;
}
