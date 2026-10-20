# 第7回 課題2 LetterCount
# よくある誤り「英字を 'A'〜'z' の 1 つの範囲で判定する」版をテストする
# （'[' '\' ']' '^' '_' '`' まで数えてしまう）。期待値は variants/tests/one_range--<入力>.*
softprac_add_program(LetterCount letter_count.c)

softprac_add_variant(LetterCount letter_count.c one_range
  "// 1 行（改行または EOF まで）に含まれる ASCII 英字の個数を表示する。"
  "// よくある誤りの例: 英字を 'A'〜'z' の 1 つの範囲で判定し，[ \\ ] ^ _ ` も数える版。"
  [=[        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {]=]
  [=[        if (ch >= 'A' && ch <= 'z') { // （誤り）'Z' と 'a' の間の記号 6 個も英字として数える]=])

# 別解: 1 行を fgets で配列へ読み込んでから数える版（本体と同じ入力で試す。期待値は variants/tests/line_array--<入力>.*）
softprac_add_variant(LetterCount versions/letter_count_line.c line_array)
# 別解の配列の容量を 100 にした誤りの例（1 行 1000 バイトの上限に足りず，先頭の 99 バイトしか数えない）
softprac_add_variant(LetterCount versions/letter_count_line.c line_array_100
  "// fgets で 1 行を配列に保存し，配列の先頭から改行または終端までの英字を数える。"
  "// よくある誤りの例: 1 行を読み込む配列の容量を 100 にした版（長い行は先頭の 99 バイトしか数えない）。"
  [=[    char line[1002]; // 入力は 1 行 1000 バイト以内。本文 1000 バイト＋改行＋終端まで入る容量にする]=]
  [=[    char line[100]; // （誤り）1 行 1000 バイトの上限に足りない。99 バイトを超えた分は読まれない]=])
