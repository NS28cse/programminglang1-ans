# 第3回 課題1 TimeParts: 本体（seconds = 3671）と，境界の値（0，59，60，61，上限 10000），
# 右辺を整数除算にした版（seconds = 61 と，誤りの例の 3671），確認問題 2・3 の比較用ソース（versions/）
softprac_add_program(TimeParts time_parts.c)

set(title "/* 第3回 課題1 秒を分と秒へ分解する（TimeParts / time_parts.c）")
set(header "${title}\n * seconds を整数の除算と余りで分と秒に分け，60.0 で割った小数の分も表示する。\n */")

foreach(s IN ITEMS 0 59 60 61 10000)
  softprac_add_variant(TimeParts time_parts.c seconds_${s}
    "${header}"
    "${title}\n * 境界の値を試す: seconds を ${s} に書き換えた版。\n */"
    "seconds = 3671" "seconds = ${s}")
endforeach()

set(div_double
  "    /* 60.0 で割るので double で除算する（60 だと整数除算の結果が保存される） */\n    double decimal_minutes = seconds / 60.0;")
# 説明すること: seconds = 61 で右辺を seconds / 60 にする → 1.00
softprac_add_variant(TimeParts time_parts.c int_division_61
  "${header}"
  "${title}\n * 説明すること: seconds = 61 で右辺を seconds / 60（整数除算）にした版（1.00 になる）。\n */"
  "seconds = 3671" "seconds = 61"
  "${div_double}"
  "    /* 整数除算: int 同士の除算 61 / 60 = 1 が double の 1.0 に変換されて保存される */\n    double decimal_minutes = seconds / 60;")
# 誤りの例（採点のポイント）: 3671 のまま右辺を seconds / 60 にする → 61.00
softprac_add_variant(TimeParts time_parts.c int_division_3671
  "${header}"
  "${title}\n * 誤りの例: seconds = 3671 のまま右辺を seconds / 60（整数除算）にした版（61.00 になる）。\n */"
  "${div_double}"
  "    /* 誤りの例: int 同士の除算 3671 / 60 = 61 が double の 61.0 に変換されて保存される */\n    double decimal_minutes = seconds / 60;")

# 確認問題 2・3: 7 / 2 と 7 / 2.0，double x = 7 / 2;
softprac_add_variant(TimeParts versions/division_types.c division_types)
