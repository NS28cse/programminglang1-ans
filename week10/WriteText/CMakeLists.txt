# 第10回 課題4 WriteText: 本体はモード "w"（上書き）。モードだけを変えた版をビルドしてテストする
#   mode_a: "a"（追記）  mode_wx: "wx"（新規作成のみ）。先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(WriteText write_text.c)

softprac_add_variant(WriteText write_text.c mode_a
  [[（モード "w"：何回実行しても 3 行） */]]
  [[（モード "a"：実行するたびに 3 行ずつ増える） */]]
  [[    /* w: ファイルがなければ作り，あれば開いた時点で以前の内容を消す（a なら末尾へ追記する） */
    FILE *fp = fopen("scores.txt", "w");]]
  [[    /* a: ファイルがなければ作り，あれば以前の内容を残して末尾へ追記する */
    FILE *fp = fopen("scores.txt", "a");]])
softprac_add_variant(WriteText write_text.c mode_wx
  [[（モード "w"：何回実行しても 3 行） */]]
  [[（モード "wx"：scores.txt が既にあれば開くのに失敗する） */]]
  [[    /* w: ファイルがなければ作り，あれば開いた時点で以前の内容を消す（a なら末尾へ追記する） */
    FILE *fp = fopen("scores.txt", "w");]]
  [[    /* wx: ファイルがなければ新しく作り，あれば開くのに失敗する（既存の内容を保護する） */
    FILE *fp = fopen("scores.txt", "wx");]])
