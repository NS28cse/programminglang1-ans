// 第13回 発展2 変更1　定義を外す（_SharedCountNoDef / counter.c）
// SharedCount の counter.c から int total = 0; の定義だけを外した版。全ファイルに extern 宣言しかないため，
// total の実体がなく，コンパイルは通るがリンクで「未解決の外部シンボル」になる（意図的なリンクエラー）。
#include "counter.h"
void add_count(void)
{
    ++total;
}
