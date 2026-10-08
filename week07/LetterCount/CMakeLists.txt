# 第7回 課題2 LetterCount
# 本体に加えて，よくある誤り「英字を 'A'〜'z' の 1 つの範囲で判定する」版をテストする
# （'[' '\' ']' '^' '_' '`' まで数えてしまうことを示す）。期待値は variants/tests/one_range--<入力>.*
# 先頭行と判定の行のコメントも誤りの例の説明に置き換える
softprac_add_program(LetterCount letter_count.c)

softprac_add_variant(LetterCount letter_count.c one_range
  [=[// 第7回 課題2: 1 行（改行または EOF まで）に含まれる ASCII 英字の個数を数える]=]
  [=[// 第7回 課題2: よくある誤りの例（英字を 'A'〜'z' の 1 範囲で判定し，[ \ ] ^ _ ` も数える版）]=]
  [=[        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {]=]
  [=[        if (ch >= 'A' && ch <= 'z') { // （誤り）'Z' と 'a' の間の記号 6 個も英字として数える]=])
