// 第13回 発展2　変更1（_SharedCountNoDef / counter.c）：意図的なリンクエラー（ビルドしない）
// int total = 0; の定義だけを外した。全ファイルに extern 宣言しかないため，total の実体がなく
// コンパイルは通るがリンクで「未解決の外部シンボル」になる。
#include "counter.h"
void add_count(void)
{
    ++total;
}
