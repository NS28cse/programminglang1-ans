# 第9回 課題4 SwapRows: 本体は 2 行目と 3 行目を交換する。各ケースは書き換えた版でテストする
#   same_row         … swap_rows(names, 1, 1); にした版（変わらない）
#   twice            … swap_rows(names, 1, 2); を 2 回呼ぶ版（元に戻る）
#   empty_fukui      … 初期値の "fukui" を "" にした版
#   row_start        … 交換前に 2 行目の開始位置を保存し，交換後に比べる版
#   until_terminator … fukui の終端までの 6 個だけを交換する（誤った）版
#   fukuiawa         … fukui の 5 文字だけを 2 行目へ上書きし，終端を書かない（誤った）版
# 各版は先頭コメントの 2 行目を版の説明に置き換え，書き換えた行のコメントも合わせる（置換前の文字列は行全体）
softprac_add_program(SwapRows swap_rows.c)

set(desc [=[// 3行9列の文字配列で，2行目と3行目の9個の char をすべて交換する。行の開始位置は変わらず，保存された内容が入れ替わる。]=])
set(call "    swap_rows(names, 1, 2);")
set(func_comment [=[// 行 i と行 j の WIDTH 個の char を1個ずつ交換する。i, j は 0〜ROWS-1（同じ行でもよい）。
// 終端や初期化で0になった残りも含めて固定幅全体を交換するので，長さの違う文字列でも正しく入れ替わる]=])
set(swap_loop [=[    for (int c = 0; c < WIDTH; ++c) {
        char temp = names[i][c];
        names[i][c] = names[j][c];
        names[j][c] = temp;
    }]=])

softprac_add_variant(SwapRows swap_rows.c same_row
  "${desc}"
  "// swap_rows(names, 1, 2); を swap_rows(names, 1, 1); にした版。\n// 同じ行どうしの交換なので，after: は before: と同じになる。"
  "${call}" "    swap_rows(names, 1, 1);  // 同じ行: 何も変わらない")
softprac_add_variant(SwapRows swap_rows.c twice
  "${desc}"
  "// swap_rows(names, 1, 2); を 2 回続けて呼ぶ版。\n// 2 回目で内容が元に戻るので，after: は before: と同じになる。"
  "${call}" "    swap_rows(names, 1, 2);\n    swap_rows(names, 1, 2);  // 2 回目: 元に戻る")
softprac_add_variant(SwapRows swap_rows.c empty_fukui
  "${desc}"
  "// 3 行目の初期値 \"fukui\" を空文字列 \"\" にした版。\n// 3 行目は 9 個すべて 0 なので，交換後は 2 行目が空文字列，3 行目が ishikawa になる。"
  [=[    char names[ROWS][WIDTH] = {"toyama", "ishikawa", "fukui"};]=]
  [=[    char names[ROWS][WIDTH] = {"toyama", "ishikawa", ""};  // 3 行目は空文字列（9 個すべて 0）]=])
softprac_add_variant(SwapRows swap_rows.c row_start
  "${desc}"
  "// 交換前に 2 行目の開始位置 names[1] を row1 に保存し，交換後に比べる版。\n// 内容を交換しても行の開始位置は変わらないので row1 == names[1] は 1 で，row1 の先には交換後の fukui がある。"
  "${call}"
  [=[    char *row1 = names[1];  // 交換前の 2 行目の開始位置
    swap_rows(names, 1, 2);]=]
  "    return 0;"
  [=[    printf("row1 == names[1]: %d, row1 = %s\n", row1 == names[1], row1);  // 位置は同じで内容が変わった
    return 0;]=])
softprac_add_variant(SwapRows swap_rows.c until_terminator
  "${desc}"
  "// 誤りの例: swap_rows で WIDTH 個ではなく fukui の終端までの 6 個だけを交換する版。\n// ishikawa の 7〜9 個目（w a と終端）が 2 行目に残るので，2 行目は fukui の後ろに w a が残り，3 行目は ishika になる。"
  "${func_comment}"
  "// 誤りの例: fukui の終端までの 6 個だけ交換する（wa が移らない）\n// 7〜9 個目は交換しないので，2 行目は f u k u i 0 w a 0（表示は fukui），3 行目は ishika になる"
  [=[    for (int c = 0; c < WIDTH; ++c) {
        char temp = names[i][c];]=]
  [=[    for (int c = 0; c < 6; ++c) {  // 誤りの例: WIDTH 個ではなく 6 個だけ
        char temp = names[i][c];]=])
softprac_add_variant(SwapRows swap_rows.c fukuiawa
  "${desc}"
  "// 誤りの例: swap_rows で交換せず，行 j の 5 文字だけを行 i へ上書きする版。\n// 終端を書かないので 2 行目は ishikawa の a w a と終端が残って fukuiawa になり，3 行目は fukui のまま。"
  "${func_comment}"
  "// 誤りの例: 5 文字だけ上書きし終端を書かない（fukuiawa になる）\n// 交換もしないので行 j は変わらない"
  "${swap_loop}"
  [=[    for (int c = 0; c < 5; ++c) { names[i][c] = names[j][c]; }  // 誤りの例: 5 文字だけ上書きする]=])
