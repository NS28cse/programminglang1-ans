# 第3回 課題3 Conditions: 本体（score = 75，d = 0）と，score・d を 1 項目ずつ変えた版（条件の境界を試す）
softprac_add_program(Conditions conditions.c)

set(title "/* 第3回 課題3 範囲の判定と短絡評価（Conditions / conditions.c）")
set(header "${title}\n * score が 0〜100 の範囲内かを && と || で判定し，&& の短絡評価で 0 による除算を防ぐ。\n */")

# score を -1，0，100，101 に変える（d は 0 のまま）
foreach(pair IN ITEMS "minus1|-1" "0|0" "100|100" "101|101")
  string(REPLACE "|" ";" pair "${pair}")
  list(GET pair 0 name)
  list(GET pair 1 value)
  softprac_add_variant(Conditions conditions.c score_${name}
    "${header}"
    "${title}\n * 条件の境界を試す: score を ${value} に書き換えた版（d は 0 のまま）。\n */"
    "score = 75" "score = ${value}")
endforeach()
# score は 75 のまま，d を 3，6 に変える
foreach(d IN ITEMS 3 6)
  softprac_add_variant(Conditions conditions.c d_${d}
    "${header}"
    "${title}\n * 条件の境界を試す: d を ${d} に書き換えた版（score は 75 のまま。&& の右側も評価される）。\n */"
    "int d = 0" "int d = ${d}")
endforeach()
