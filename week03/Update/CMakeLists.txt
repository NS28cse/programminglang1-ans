# 第3回 課題2 Update: 本体（x = 5）と，通常の代入の形・最初の x を 0，-2 にした版，
# 更新の順番を逆にした版，誤りの例（1 行の x = x + 3 * 2;）
softprac_add_program(Update update.c)

set(title "/* 第3回 課題2 前置・後置と複合代入（Update / update.c）")
set(header "${title}\n * 後置・前置のインクリメントの式の値と，複合代入 += と *= で更新した x を表示する。\n */")
set(update_lines
  "    /* その時点の x を順に更新する: 3を加算して保存し，さらに2倍して保存する */\n    x += 3;\n    x *= 2;\n")

softprac_add_variant(Update update.c plain_assignment
  "${header}"
  "${title}\n * 書き方を変えて比較する: 複合代入を通常の代入 x = x + 3; x = x * 2; に書き換えた版（同じ 20）。\n */"
  "x += 3" "x = x + 3"
  "x *= 2" "x = x * 2")
softprac_add_variant(Update update.c x_0
  "${header}"
  "${title}\n * 書き方を変えて比較する: 最初の x を 0 に書き換えた版。\n */"
  "int x = 5" "int x = 0")
softprac_add_variant(Update update.c x_minus2
  "${header}"
  "${title}\n * 書き方を変えて比較する: 最初の x を -2 に書き換えた版。\n */"
  "int x = 5" "int x = -2")
# 説明すること: x += 3; と x *= 2; の順番を入れ替える → 17
softprac_add_variant(Update update.c swapped_order
  "${header}"
  "${title}\n * 説明すること: x += 3; と x *= 2; の順番を逆にした版（final x=17 になる）。\n */"
  "${update_lines}"
  "    /* 先に2倍して保存し，その後3を加算して保存する */\n    x *= 2;\n    x += 3;\n")
# 誤りの例（採点のポイント）: 2 段階の更新を 1 行にする → * が先なので 13
softprac_add_variant(Update update.c wrong_one_line
  "${header}"
  "${title}\n * 誤りの例: 2 段階の更新を x = x + 3 * 2; の 1 行にした版（final x=13 になる）。\n */"
  "${update_lines}"
  "    /* 誤りの例: * が + より先に計算されるので x + 6 になる（(x + 3) * 2 ではない） */\n    x = x + 3 * 2;\n")
