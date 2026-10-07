# 第7回 発展 Typing
# 本体（大文字・小文字を区別しない最終版）に加えて，次の版をテストする。期待値は variants/tests/<版>--<入力>.*
#   case_sensitive: 比較を ch == target[position] に戻した「大文字・小文字を区別する版」
#   advance_on_match: よくある誤り「一致したときだけ position を進める」版（位置がずれて得点が変わる）
softprac_add_program(Typing typing.c)

softprac_add_variant(Typing typing.c case_sensitive
  "lower(ch) == lower(target[position])" "ch == target[position]")

softprac_add_variant(Typing typing.c advance_on_match
  [=[            ++score;
        }
        ++position;
]=]
  [=[            ++score;
            ++position;
        }
]=])
