# 第3回 課題1 TimeParts
# 本体（seconds = 3671）に加えて，「境界の値を試す」（seconds を 0，59，60，61 と上限 10000 に変える）版，
# 「説明すること」（seconds = 61 で右辺を seconds / 60 にする）版，誤りの例（3671 のまま seconds / 60）と，
# 確認問題 2・3 の比較用ソース（versions/division_types.c）をビルドしてテストする。
# 各版は先頭コメントを版の説明に置き換え，除算の行のコメントも書き換え後のコードに合わせる
softprac_add_program(TimeParts time_parts.c)

set(header "/* 第3回 課題1 秒を分と秒へ分解する（TimeParts） */")

# 境界の値（0，59，60，61）と入力範囲の上限（10000）
foreach(s IN ITEMS 0 59 60 61 10000)
  softprac_add_variant(TimeParts time_parts.c seconds_${s}
    "${header}"
    "/* 第3回 課題1 境界の値を試す: seconds を ${s} に書き換えた版 */"
    "seconds = 3671" "seconds = ${s}")
endforeach()

# 右辺を整数同士の除算にしたときの除算の行（コメントも書き換え後のコードに合わせる）
set(div_double
  "    /* 60.0 で割るので double で除算する（60 だと整数除算の結果が保存される） */\n    double decimal_minutes = seconds / 60.0;")
# seconds = 61 で，decimal_minutes の右辺を整数同士の除算にする（1.00 になる）
softprac_add_variant(TimeParts time_parts.c int_division_61
  "${header}"
  "/* 第3回 課題1 説明すること: seconds = 61 で右辺を seconds / 60（整数除算）にした版（1.00 になる） */"
  "seconds = 3671" "seconds = 61"
  "${div_double}"
  "    /* 整数除算にした版: int 同士の除算 61 / 60 = 1 が double の 1.0 に変換されて保存される */\n    double decimal_minutes = seconds / 60;")
# 誤りの例（README の採点のポイント）: 元の 3671 のまま右辺を seconds / 60 にする → 61.00
softprac_add_variant(TimeParts time_parts.c int_division_3671
  "${header}"
  "/* 第3回 課題1 誤りの例: seconds = 3671 のまま右辺を seconds / 60（整数除算）にした版（61.00 になる） */"
  "${div_double}"
  "    /* 誤りの例: int 同士の除算 3671 / 60 = 61 が double の 61.0 に変換されて保存される */\n    double decimal_minutes = seconds / 60;")

# 確認問題 2・3: 7 / 2 と 7 / 2.0，double x = 7 / 2; の比較（README に載せた結果をテストする）
softprac_add_variant(TimeParts versions/division_types.c division_types)
