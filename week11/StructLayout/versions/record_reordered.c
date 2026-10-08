// 第11回 発展3 比較用: Record のメンバを tag，flag，count の順に並べ替えた版（char 2 つを並べると隙間が減る）
// 結果は処理系・配置設定に依存する。x64 の GCC・Clang・MSVC（既定）と macOS arm64 では size=8 tag=0 flag=1 count=4
#include <stdio.h>
#include <stddef.h>
typedef struct {
    char tag;
    char flag; // tag の直後の 1 バイトに置ける
    int count; // 4 の倍数の位置に置くため，flag の後に 2 バイトの隙間が入る
} Record;
int main(void)
{
    printf("size=%zu tag=%zu flag=%zu count=%zu\n",
           sizeof(Record), offsetof(Record, tag),
           offsetof(Record, flag), offsetof(Record, count));
    return 0;
}
