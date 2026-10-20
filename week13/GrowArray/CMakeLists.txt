# 第13回 発展1 GrowArray
# 本体は old_n = 3，new_n = 5。「境界を調べる」の表の組は old_n，new_n を書き換えた版としてテストする
softprac_add_program(GrowArray grow_array.c)

# grow_array_variant(<ケース名> <old_n> <new_n> <書き換えた版の先頭コメントに入れる確認内容>)
function(grow_array_variant case old_n new_n note)
  softprac_add_variant(GrowArray grow_array.c ${case}
    [=[// old_n = 3 要素を calloc して 0 を確認してから 1〜old_n を代入し，realloc で new_n = 5 要素へ拡張して，
// 増えた部分だけを old_n+1〜new_n で初期化して表示する。境界の表の組は old_n，new_n の値を書き換えて試す。]=]
    "// (old_n, new_n) = (${old_n}, ${new_n}) に書き換えた版。\n// ${note}"
    "size_t old_n = 3;" "size_t old_n = ${old_n};"
    "size_t new_n = 5;" "size_t new_n = ${new_n};")
endfunction()

# 演習ページの境界の表の組
grow_array_variant(same_3_to_3 3 3 "境界の表の組。同じ個数でも realloc 成功後は返されたポインタを使い，追加の初期化は 0 回。")
grow_array_variant(shrink_3_to_1 3 1 "境界の表の組。縮小して先頭の 1 だけが有効になる。")
grow_array_variant(grow_1_to_4 1 4 "境界の表の組。1 を保持し，2，3，4 を追加して初期化する。")
grow_array_variant(new_zero_3_to_0 3 0 "境界の表の組。new_n の範囲外なので，realloc せずに確保済みの領域を解放してエラー終了する。")
grow_array_variant(old_zero_0_to_5 0 5 "境界の表の組。old_n の範囲外なので，calloc の前（最初の確保前）にエラー終了する。")
grow_array_variant(new_over_3_to_1001 3 1001 "境界の表の組。new_n の上限違反なので，realloc せずに元の領域を解放して終了する。")
# 表にない追加の組
grow_array_variant(old_over_1001_to_5 1001 5 "表にない追加の組。old_n の上限違反なので，calloc の前（最初の確保前）にエラー終了する。")
grow_array_variant(grow_1_to_1000 1 1000 "表にない追加の組。上限 1000 まで拡張し，2〜1000 を初期化する。")
