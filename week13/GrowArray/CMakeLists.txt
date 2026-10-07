# 第13回 発展1 GrowArray
# 本体（old_n = 3，new_n = 5）に加えて，「境界を調べる」の表の組を old_n，new_n を書き換えた版としてビルドしてテストする
softprac_add_program(GrowArray grow_array.c)

function(grow_array_variant case old_n new_n)
  softprac_add_variant(GrowArray grow_array.c ${case}
    [=[// old_n = 3 要素を calloc して 0 を確認してから 1〜old_n を代入し，realloc で new_n = 5 要素へ拡張して，]=]
    "// 境界の表の組 (old_n, new_n) = (${old_n}, ${new_n}) に書き換えた版。old_n 要素を calloc して 1〜old_n を代入し，realloc で new_n 要素へ変更して，"
    "size_t old_n = 3;" "size_t old_n = ${old_n};"
    "size_t new_n = 5;" "size_t new_n = ${new_n};")
endfunction()

grow_array_variant(same_3_to_3 3 3)               # 同じ個数でも成功後は返されたポインタを使う
grow_array_variant(shrink_3_to_1 3 1)             # 先頭の 1 だけが有効
grow_array_variant(grow_1_to_4 1 4)               # 1 を保持し，2，3，4 を追加
grow_array_variant(new_zero_3_to_0 3 0)           # 確保済み領域を解放してエラー終了
grow_array_variant(old_zero_0_to_5 0 5)           # 最初の確保前にエラー終了
grow_array_variant(new_over_3_to_1001 3 1001)     # 上限違反で，元の領域を解放して終了
grow_array_variant(old_over_1001_to_5 1001 5)     # old_n の上限違反（確保前に終了）
grow_array_variant(grow_1_to_1000 1 1000)         # 上限まで拡張
