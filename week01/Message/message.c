// 第1回 課題2　改行と特殊な文字（Message / message.c）
// \n は改行，\" は二重引用符，\\ はバックスラッシュ（エスケープシーケンス）。
// % は printf の書式の規則により %% と書く。
#include <stdio.h>

int main(void)
{
    printf("My first C program\n");
    printf("\n");                       // 2 行目の空行（\n だけを表示する）
    printf("She said, \"Hello!\"\n");
    printf("Backslash: \\\n");          // \\ で \ を 1 文字，続く \n で改行
    printf("Progress: 100%%\n");        // 最後の行の末尾にも改行を入れる
    return 0;
}
