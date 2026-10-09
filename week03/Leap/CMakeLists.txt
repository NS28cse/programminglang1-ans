# 第3回 課題4 Leap: 本体（2000 年）と，例外を含む年（1900，2024，2025），
# leap の式だけを講義の例題の 1 つの式にした版（4 年すべて），誤りの例（100 の例外を落とす）
softprac_add_program(Leap leap.c)

set(title "/* 第3回 課題4 うるう年の条件式（Leap / leap.c）")
set(header "${title}\n * うるう年の規則を 3 つの条件に分け，&& と || で組み合わせた式の値（0 か 1）で判定する。\n */")

foreach(y IN ITEMS 1900 2024 2025)
  softprac_add_variant(Leap leap.c year_${y}
    "${header}"
    "${title}\n * 例外を含む年で確認する: year を ${y} に書き換えた版。\n */"
    "year = 2000" "year = ${y}")
endforeach()

# 3 つの変数 div4・not_div100・div400 は表示のために残る。2000 は year をそのまま使う
foreach(y IN ITEMS 1900 2000 2024 2025)
  set(year_args "")
  if(NOT y EQUAL 2000)
    set(year_args "year = 2000" "year = ${y}")
  endif()
  softprac_add_variant(Leap leap.c one_expr_${y}
    "${header}"
    "${title}\n * leap の式だけを講義の例題の 1 つの式に置き換えた版（year = ${y}）。\n */"
    ${year_args}
    "(div4 && not_div100) || div400" "(year % 4 == 0 && year % 100 != 0) || year % 400 == 0")
endforeach()

# 誤りの例（採点のポイント）: 100 の例外を落とす → 1900 が 1 になる
softprac_add_variant(Leap leap.c wrong_no_100_rule_1900
  "${header}"
  "${title}\n * 誤りの例: 100 の例外を落とした式 year % 4 == 0 || year % 400 == 0 で 1900 年を判定する版（leap=1 になる）。\n */"
  "year = 2000" "year = 1900"
  "    /* (4で割り切れる かつ 100では割り切れない) または 400で割り切れる */\n    int leap = (div4 && not_div100) || div400;"
  "    /* 誤りの例: 100 の例外がない（4で割り切れる または 400で割り切れる）ので 1900 も 1 になる */\n    int leap = year % 4 == 0 || year % 400 == 0;")
