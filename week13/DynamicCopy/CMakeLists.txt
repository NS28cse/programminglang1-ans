# 第13回 課題2「追加：独立したコピー」DynamicCopy
# copy の確保に失敗した経路（先に確保した values を解放して終了する）を版としてテストする。
# 確保を NULL に置き換えるだけなので，実際のメモリ不足は起こさない。
softprac_add_program(DynamicCopy dynamic.c)

softprac_add_variant(DynamicCopy dynamic.c copy_alloc_fail
  [=[// Dynamic と同じ検査で values を確保・初期化した後，別の領域 copy を確保して要素をコピーし，
// copy だけを逆順にして両方を表示する。所有する領域は values と copy の 2 つ。]=]
  [=[// Dynamic と同じ検査で values を確保・初期化した後，copy の確保を NULL に置き換えて失敗を模擬した版。
// 先に確保した values を解放してから終了する。]=]
  [=[    // 独立したコピー：ポインタではなく要素をコピーするため，別の領域を確保する
    copy = malloc(n * sizeof *copy);]=]
  [=[    // 試験用：copy の確保失敗を模擬する（実際には確保しない）
    copy = NULL;]=])
