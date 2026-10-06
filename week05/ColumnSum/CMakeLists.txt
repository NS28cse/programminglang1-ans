# 第5回 課題2 ColumnSum
# 本体に加えて，table を {{1, 1, 1}, {2, 2, 2}} と {{0}} に変えた版と，
# sum の初期化を二重ループ全体の前へ移した誤りの版（5，12，21 の累積になる）をビルドしてテストする
softprac_add_program(ColumnSum arrays.c)

softprac_add_variant(ColumnSum arrays.c ones "{{1, 2, 3}, {4, 5, 6}}" "{{1, 1, 1}, {2, 2, 2}}")
softprac_add_variant(ColumnSum arrays.c zero "{{1, 2, 3}, {4, 5, 6}}" "{{0}}")
softprac_add_variant(ColumnSum arrays.c sum_outside
  [=[    for (int col = 0; col < 3; ++col) {
        int sum = 0;  // 列が変わるたびに 0 から数え直す
]=]
  [=[    int sum = 0;  // 誤り: 二重ループ全体の前で 1 回だけ初期化
    for (int col = 0; col < 3; ++col) {
]=])
