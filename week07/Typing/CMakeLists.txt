# 第7回 発展 Typing
# 本体（大文字・小文字を区別しない最終版）に加えて，比較を ch == target[position] に戻した
# 「大文字・小文字を区別する版」をテストする。期待値は variants/tests/case_sensitive--<入力の名前>.*
softprac_add_program(Typing typing.c)

softprac_add_variant(Typing typing.c case_sensitive
  "lower(ch) == lower(target[position])" "ch == target[position]")
