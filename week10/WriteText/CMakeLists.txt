# 第10回 課題4 WriteText
# 本体（フォルダのソース）はモードを "a"（追記）へ変えた最終版。
# 最初に実行する "w"（上書き）の版と，表の "wx"（新規作成のみ）の版もビルドしてテストする
softprac_add_program(WriteText write_text.c)

include("${CMAKE_CURRENT_LIST_DIR}/../_cmake/Week10Variant.cmake")
set(mode_a [[fopen("scores.txt", "a")]])
set(mode_w [[fopen("scores.txt", "w")]])
set(mode_wx [[fopen("scores.txt", "wx")]])
week10_add_variant(WriteText write_text.c mode_w mode_a mode_w)
week10_add_variant(WriteText write_text.c mode_wx mode_a mode_wx)
