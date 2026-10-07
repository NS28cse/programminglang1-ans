# 第9回 課題4 SwapRows
# フォルダのソースは 2行目と3行目を交換する最終版。各ケースは書き換えた版でテストする
#   same_row         … swap_rows(names, 1, 1); にした版（変わらない）
#   twice            … swap_rows(names, 1, 2); を 2 回呼ぶ版（元に戻る）
#   empty_fukui      … 初期値の "fukui" を "" にした版
#   row_start        … 交換前に 2 行目の開始位置を保存し，交換後に比べる版
#   until_terminator … fukui の終端までの 6 個だけを交換する（誤った）版
#   fukuiawa         … fukui の 5 文字だけを 2 行目へ上書きし，終端を書かない（誤った）版
softprac_add_program(SwapRows swap_rows.c)

set(call "    swap_rows(names, 1, 2);")
set(swap_loop [=[    for (int c = 0; c < WIDTH; ++c) {
        char temp = names[i][c];
        names[i][c] = names[j][c];
        names[j][c] = temp;
    }]=])

softprac_add_variant(SwapRows swap_rows.c same_row "${call}" "    swap_rows(names, 1, 1);")
softprac_add_variant(SwapRows swap_rows.c twice "${call}" "${call}
${call}")
softprac_add_variant(SwapRows swap_rows.c empty_fukui [=["fukui"}]=] [=[""}]=])
softprac_add_variant(SwapRows swap_rows.c row_start "${call}" [=[    char *row1 = names[1];
    swap_rows(names, 1, 2);]=] "    return 0;" [=[    printf("row1 == names[1]: %d, row1 = %s\n", row1 == names[1], row1);
    return 0;]=])
softprac_add_variant(SwapRows swap_rows.c until_terminator [=[c < WIDTH; ++c) {
        char temp]=] [=[c < 6; ++c) {
        char temp]=])
softprac_add_variant(SwapRows swap_rows.c fukuiawa "${swap_loop}" [=[    for (int c = 0; c < 5; ++c) { names[i][c] = names[j][c]; }]=])
