# 第10回 課題4 WriteText
# 本体（フォルダのソース）はモードを "a"（追記）へ変えた最終版。
# 最初に実行する "w"（上書き）の版と，表の "wx"（新規作成のみ）の版もビルドしてテストする
#   期待値: variants/tests/mode_w--<ケース>.*，variants/tests/mode_wx--<ケース>.*
softprac_add_program(WriteText write_text.c)

softprac_add_variant(WriteText write_text.c mode_w
  [[fopen("scores.txt", "a")]] [[fopen("scores.txt", "w")]])
softprac_add_variant(WriteText write_text.c mode_wx
  [[fopen("scores.txt", "a")]] [[fopen("scores.txt", "wx")]])
