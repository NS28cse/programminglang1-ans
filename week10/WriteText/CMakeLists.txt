# 第10回 課題4 WriteText
# 本体は最初に作るモード "w"（上書き）の版。モードだけを変えた版をビルドしてテストする
#   mode_a: "a"（追記）  mode_wx: "wx"（新規作成のみ）  期待値: variants/tests/<版>--<ケース>.*
softprac_add_program(WriteText write_text.c)

softprac_add_variant(WriteText write_text.c mode_a
  [[fopen("scores.txt", "w")]] [[fopen("scores.txt", "a")]])
softprac_add_variant(WriteText write_text.c mode_wx
  [[fopen("scores.txt", "w")]] [[fopen("scores.txt", "wx")]])
