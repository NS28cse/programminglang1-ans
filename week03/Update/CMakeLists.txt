# 第3回 課題2 Update
# 本体に加えて，「書き方を変えて比較する」版と，「説明すること」（順番を逆にする）版をビルドしてテストする
softprac_add_program(Update update.c)

# 複合代入を通常の代入の形へ書き換える（同じ結果になる）
softprac_add_variant(Update update.c plain_assignment
  "x += 3" "x = x + 3"
  "x *= 2" "x = x * 2")
# 最初の x を 0，-2 に変える
softprac_add_variant(Update update.c x_0 "int x = 5" "int x = 0")
softprac_add_variant(Update update.c x_minus2 "int x = 5" "int x = -2")
# x += 3; と x *= 2; の順番を入れ替える（17 になる）
softprac_add_variant(Update update.c swapped_order
  "    x += 3;\n    x *= 2;\n" "    x *= 2;\n    x += 3;\n")
# 誤りの例（README の採点のポイント）: 2 段階の更新を x = x + 3 * 2; の 1 行にする → * が先なので 13
softprac_add_variant(Update update.c wrong_one_line
  "    x += 3;\n    x *= 2;\n" "    x = x + 3 * 2;\n")
