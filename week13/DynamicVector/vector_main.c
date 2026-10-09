// 第13回 発展3　不透明な Vector の生成と解放（DynamicVector / vector_main.c）
// x，y，result の 3 つを所有し，どこで失敗しても cleanup で 3 つとも後始末する。
// 演習ページの「添字と保存先の検査」の断片（範囲外の添字 2 で vector_get が失敗し，out が 99.0 のまま）も含む。
#include "vector.h"
#include <stdio.h>

int main(void)
{
    // 所有ポインタは最初に NULL にしておき，未作成のものも cleanup へ渡せるようにする
    Vector *x = NULL;
    Vector *y = NULL;
    Vector *result = NULL;
    int status = 1;     // 失敗を表す 1。すべて成功したときだけ 0 にする
    double first, second;
    double out = 99.0;
    int ok;

    x = vector_create(1.0, 2.0);
    if (x == NULL) {
        fputs("allocation failed\n", stderr);
        goto cleanup;
    }
    y = vector_create(3.0, 4.0);
    if (y == NULL) {
        fputs("allocation failed\n", stderr);
        goto cleanup;
    }
    result = vector_axpy(2.0, x, y);
    if (result == NULL) {
        fputs("allocation failed\n", stderr);
        goto cleanup;
    }
    if (!vector_get(result, 0, &first) ||
        !vector_get(result, 1, &second)) {
        fputs("invalid access\n", stderr);
        goto cleanup;
    }
    printf("result=%.1f %.1f\n", first, second);

    // 添字と保存先の検査：有効な添字は 0 と 1。2 は範囲外なので 0 が返り，out は初期値のまま
    ok = vector_get(result, 2, &out);
    printf("ok=%d out=%.1f\n", ok, out);
    status = 0;

cleanup:
    // 生成と逆の順に解放する。&x を渡すので，解放後は呼び出し元の x なども NULL になる
    vector_destroy(&result);
    vector_destroy(&y);
    vector_destroy(&x);
    return status;
}
