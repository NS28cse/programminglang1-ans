// 第11回 発展3: sizeof と offsetof で Record の配置（パディング）を観察する
// 結果は処理系・配置設定に依存する。x64 の GCC・Clang・MSVC（既定）と macOS arm64 では size=12 tag=0 count=4 flag=8
#include <stdio.h>
#include <stddef.h>
typedef struct {
    char tag;
    int count;
    char flag;
} Record;
int main(void)
{
    printf("size=%zu tag=%zu count=%zu flag=%zu\n",
           sizeof(Record), offsetof(Record, tag),
           offsetof(Record, count), offsetof(Record, flag));
    return 0;
}
