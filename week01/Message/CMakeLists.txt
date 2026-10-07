# 第1回 課題2 Message
# 本体に加えて，説明すること（\n は 2 文字として表示されるか）の比較として，
# Backslash の行を \\n（\ と n の 2 文字，改行なし）にした誤りの例をビルドしてテストする
softprac_add_program(Message message.c)

softprac_add_variant(Message message.c backslash_n_only
  [[printf("Backslash: \\\n");]] [[printf("Backslash: \\n");]])
