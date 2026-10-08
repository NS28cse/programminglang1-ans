# 第7回 発展 Typing
# 本体（大文字・小文字を区別しない最終版）に加えて，次の版をテストする。期待値は variants/tests/<版>--<入力>.*
#   case_sensitive: 比較を ch == target[position] に変えた「大文字・小文字を区別する版」
#   advance_on_match: よくある誤り「一致したときだけ position を進める」版（位置がずれて得点が変わる）
# 各版は先頭行とコメントも版の説明に置き換える
softprac_add_program(Typing typing.c)

softprac_add_variant(Typing typing.c case_sensitive
  [=[// 第7回 発展: タイピングの採点（同じ位置の文字を大文字・小文字を区別せずに比較する）]=]
  [=[// 第7回 発展: タイピングの採点（大文字・小文字を区別する版。比較を ch == target[position] に変えた）]=]
  [=[// ASCII の英大文字だけを小文字にする。EOF を除いた後の値を渡す]=]
  [=[// ASCII の英大文字だけを小文字にする。EOF を除いた後の値を渡す（この版では使わない）]=]
  [=[        if (position < length && lower(ch) == lower(target[position])) {]=]
  [=[        if (position < length && ch == target[position]) { // 大文字・小文字を区別して比較する]=])

softprac_add_variant(Typing typing.c advance_on_match
  [=[// 第7回 発展: タイピングの採点（同じ位置の文字を大文字・小文字を区別せずに比較する）]=]
  [=[// 第7回 発展: よくある誤りの例（一致したときだけ position を進める版。位置がずれて得点が変わる）]=]
  [=[    size_t position = 0;            // 次に読む文字の位置（入力するたびに進む）]=]
  [=[    size_t position = 0;            // （誤り）一致したときだけ進む]=]
  [=[            ++score;
        }
        ++position;
]=]
  [=[            ++score;
            ++position; // （誤り）if の中へ移した
        }
]=])
