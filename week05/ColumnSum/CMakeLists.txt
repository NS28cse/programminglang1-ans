# 第5回 課題2 ColumnSum
# 本体に加えて，table を {{1, 1, 1}, {2, 2, 2}} と {{0}} に変えた版と，
# sum の初期化を二重ループ全体の前へ移した誤りの版（5，12，21 の累積になる）をビルドしてテストする。
# 各版は先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(ColumnSum arrays.c)

softprac_add_variant(ColumnSum arrays.c ones
  "// 講義の arrays.c を変更し，二次元配列の行ごとの合計の代わりに列ごとの合計を表示する。"
  "// table を {{1, 1, 1}, {2, 2, 2}} に書き換えた版（各列が 3）。"
  "{{1, 2, 3}, {4, 5, 6}}" "{{1, 1, 1}, {2, 2, 2}}")
softprac_add_variant(ColumnSum arrays.c zero
  "// 講義の arrays.c を変更し，二次元配列の行ごとの合計の代わりに列ごとの合計を表示する。"
  "// table を {{0}}（全要素 0）に書き換えた版（各列が 0）。"
  "{{1, 2, 3}, {4, 5, 6}}" "{{0}}")
softprac_add_variant(ColumnSum arrays.c sum_outside
  "// 講義の arrays.c を変更し，二次元配列の行ごとの合計の代わりに列ごとの合計を表示する。"
  "// 誤りの例: sum の初期化を二重ループ全体の前へ移した版（5，12，21 の累積になる）。"
  [=[    // 外側を列（0〜2），内側を行（0〜1）にする。添字は常に table[行][列] の順
    for (int col = 0; col < 3; ++col) {
        int sum = 0;  // 列が変わるたびに 0 から数え直す
]=]
  [=[    int sum = 0;  // 誤り: 二重ループ全体の前で 1 回だけ初期化
    // 外側を列（0〜2），内側を行（0〜1）にする。添字は常に table[行][列] の順
    for (int col = 0; col < 3; ++col) {
]=])
