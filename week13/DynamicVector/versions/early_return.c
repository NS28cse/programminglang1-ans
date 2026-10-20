// 第13回 発展3　別解：失敗した場所ごとに，作成済みのものを解放して return する（DynamicVector / versions/early_return.c）
// goto と cleanup を使わず，各失敗箇所でそこまでに作成した Vector を逆順に解放してから終了する。
// 失敗箇所が増えるたびに解放の列が長くなり，return を足すときに解放を書き忘れやすい。
#include "vector.h"
#include <stdio.h>

int main(void)
{
    double first, second;
    double out = 99.0;

    Vector *x = vector_create(1.0, 2.0);
    if (x == NULL) {
        fputs("allocation failed\n", stderr);
        return 1;                       // まだ何も所有していないので解放は不要
    }
    Vector *y = vector_create(3.0, 4.0);
    if (y == NULL) {
        fputs("allocation failed\n", stderr);
        vector_destroy(&x);             // 作成済みの x だけを解放する
        return 1;
    }
    Vector *result = vector_axpy(2.0, x, y);
    if (result == NULL) {
        fputs("allocation failed\n", stderr);
        vector_destroy(&y);             // 作成済みの y，x を解放する
        vector_destroy(&x);
        return 1;
    }
    if (!vector_get(result, 0, &first) ||
        !vector_get(result, 1, &second)) {
        fputs("invalid access\n", stderr);
        vector_destroy(&result);        // 3 つとも作成済み
        vector_destroy(&y);
        vector_destroy(&x);
        return 1;
    }
    printf("result=%.1f %.1f\n", first, second);

    // 添字と保存先の検査：有効な添字は 0 と 1。2 は範囲外なので 0 が返り，out は初期値のまま
    int ok = vector_get(result, 2, &out);
    printf("ok=%d out=%.1f\n", ok, out);

    // 正常に終わる経路でも，生成と逆の順に 3 つを解放する
    vector_destroy(&result);
    vector_destroy(&y);
    vector_destroy(&x);
    return 0;
}
