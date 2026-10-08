# 第3回 課題2 Update
# 本体（x = 5）に加えて，「書き方を変えて比較する」（通常の代入の形，最初の x を 0，-2）版，
# 「説明すること」（x += 3; と x *= 2; の順番を逆にする）版と，誤りの例（1 行の x = x + 3 * 2;）をビルドしてテストする。
# 各版は先頭コメントを版の説明に置き換え，更新の順序を変えた版は更新の行のコメントも書き換え後のコードに合わせる
softprac_add_program(Update update.c)

set(header "/* 第3回 課題2 前置・後置と複合代入（Update） */")
set(update_lines
  "    /* その時点の x を順に更新する: 3を加算して保存し，さらに2倍して保存する */\n    x += 3;\n    x *= 2;\n")

# 複合代入を通常の代入の形へ書き換える（同じ結果になる）
softprac_add_variant(Update update.c plain_assignment
  "${header}"
  "/* 第3回 課題2 書き方を変えて比較する: 複合代入を通常の代入 x = x + 3; x = x * 2; に書き換えた版（同じ 20） */"
  "x += 3" "x = x + 3"
  "x *= 2" "x = x * 2")
# 最初の x を 0，-2 に変える
softprac_add_variant(Update update.c x_0
  "${header}"
  "/* 第3回 課題2 書き方を変えて比較する: 最初の x を 0 に書き換えた版 */"
  "int x = 5" "int x = 0")
softprac_add_variant(Update update.c x_minus2
  "${header}"
  "/* 第3回 課題2 書き方を変えて比較する: 最初の x を -2 に書き換えた版 */"
  "int x = 5" "int x = -2")
# x += 3; と x *= 2; の順番を入れ替える（17 になる）
softprac_add_variant(Update update.c swapped_order
  "${header}"
  "/* 第3回 課題2 説明すること: x += 3; と x *= 2; の順番を逆にした版（final x=17 になる） */"
  "${update_lines}"
  "    /* 順番を逆にした版: 先に2倍して保存し，その後3を加算して保存する */\n    x *= 2;\n    x += 3;\n")
# 誤りの例（README の採点のポイント）: 2 段階の更新を x = x + 3 * 2; の 1 行にする → * が先なので 13
softprac_add_variant(Update update.c wrong_one_line
  "${header}"
  "/* 第3回 課題2 誤りの例: 2 段階の更新を x = x + 3 * 2; の 1 行にした版（final x=13 になる） */"
  "${update_lines}"
  "    /* 誤りの例: * が + より先に計算されるので x + 6 になる（(x + 3) * 2 ではない） */\n    x = x + 3 * 2;\n")
