// 第11回 発展3: sizeof と offsetof で Record の配置（パディング）を観察する
// 結果は処理系・配置設定に依存する（Windows x64 の MSVC 既定では size=12 tag=0 count=4 flag=8）
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
    // メンバのサイズの単純な合計と比べると，隙間（パディング）の合計が分かる
    printf("members=%zu+%zu+%zu=%zu\n", sizeof(char), sizeof(int), sizeof(char),
           sizeof(char) + sizeof(int) + sizeof(char));
    return 0;
}
