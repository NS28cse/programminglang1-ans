# 第7回 発展 Typing
# 本体（大文字・小文字を区別しない最終版）に加えて，比較を ch == target[position] に戻した
# 「大文字・小文字を区別する版」をテストする
softprac_add_program(Typing typing.c)

foreach(case case_exact case_mixed case_partial)
  softprac_add_variant(Typing typing.c ${case}
    "lower(ch) == lower(target[position])" "ch == target[position]")
endforeach()
