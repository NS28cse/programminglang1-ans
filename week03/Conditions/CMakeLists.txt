# 第3回 課題3 Conditions
# 本体（score = 75，d = 0）に加えて，「条件の境界を試す」版（score を -1，0，100，101 に，d を 3，6 に 1 項目ずつ変える）をビルドしてテストする。
# 各版は先頭コメントを版の説明に置き換える
softprac_add_program(Conditions conditions.c)

set(header "/* 第3回 課題3 範囲の判定と短絡評価（Conditions） */")

# score を -1，0，100，101 に変える（d は 0 のまま）
foreach(pair IN ITEMS "minus1|-1" "0|0" "100|100" "101|101")
  string(REPLACE "|" ";" pair "${pair}")
  list(GET pair 0 name)
  list(GET pair 1 value)
  softprac_add_variant(Conditions conditions.c score_${name}
    "${header}"
    "/* 第3回 課題3 条件の境界を試す: score を ${value} に書き換えた版（d は 0 のまま） */"
    "score = 75" "score = ${value}")
endforeach()
# score を 75 に戻して，d を 3，6 に変える
foreach(d IN ITEMS 3 6)
  softprac_add_variant(Conditions conditions.c d_${d}
    "${header}"
    "/* 第3回 課題3 条件の境界を試す: d を ${d} に書き換えた版（score は 75 のまま。&& の右側も評価される） */"
    "int d = 0" "int d = ${d}")
endforeach()
