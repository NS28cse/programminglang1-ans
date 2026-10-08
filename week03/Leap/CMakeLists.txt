# 第3回 課題4 Leap
# 本体（2000 年）に加えて，「例外を含む年で確認する」（1900，2024，2025）版，
# leap の式だけを講義の例題の 1 つの式に置き換えた版（4 年すべて）と，誤りの例（100 の例外を落とす）をビルドしてテストする。
# 各版は先頭コメントを版の説明に置き換え，誤りの例は leap の行のコメントも書き換え後のコードに合わせる
softprac_add_program(Leap leap.c)

set(header "/* 第3回 課題4 うるう年の条件式（Leap） */")

foreach(y IN ITEMS 1900 2024 2025)
  softprac_add_variant(Leap leap.c year_${y}
    "${header}"
    "/* 第3回 課題4 例外を含む年で確認する: year を ${y} に書き換えた版 */"
    "year = 2000" "year = ${y}")
endforeach()

# leap の式だけを講義の例題と同じ 1 つの式に置き換えても，4 年すべてで同じ結果になる
# （3 つの変数 div4・not_div100・div400 は表示のために残る。2000 は year をそのまま使う）
foreach(y IN ITEMS 1900 2000 2024 2025)
  set(year_args "")
  if(NOT y EQUAL 2000)
    set(year_args "year = 2000" "year = ${y}")
  endif()
  softprac_add_variant(Leap leap.c one_expr_${y}
    "${header}"
    "/* 第3回 課題4 leap の式だけを講義の例題の 1 つの式に置き換えた版（year = ${y}） */"
    ${year_args}
    "(div4 && not_div100) || div400" "(year % 4 == 0 && year % 100 != 0) || year % 400 == 0")
endforeach()

# 誤りの例（README の採点のポイント）: 100 の例外を落とす → 1900 が 1 になる
softprac_add_variant(Leap leap.c wrong_no_100_rule_1900
  "${header}"
  "/* 第3回 課題4 誤りの例: 100 の例外を落とした式 year % 4 == 0 || year % 400 == 0 で 1900 年を判定する版（leap=1 になる） */"
  "year = 2000" "year = 1900"
  "    /* (4で割り切れる かつ 100では割り切れない) または 400で割り切れる */\n    int leap = (div4 && not_div100) || div400;"
  "    /* 誤りの例: 100 の例外がない（4で割り切れる または 400で割り切れる）ので 1900 も 1 になる */\n    int leap = year % 4 == 0 || year % 400 == 0;")
