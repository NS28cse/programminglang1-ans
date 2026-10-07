# 第7回 課題2 LetterCount
# 本体に加えて，よくある誤り「英字を 'A'〜'z' の 1 つの範囲で判定する」版をテストする
# （'[' '\' ']' '^' '_' '`' まで数えてしまうことを示す）。期待値は variants/tests/one_range--<入力>.*
softprac_add_program(LetterCount letter_count.c)

softprac_add_variant(LetterCount letter_count.c one_range
  "(ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')" "ch >= 'A' && ch <= 'z'")
