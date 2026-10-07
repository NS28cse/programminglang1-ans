# 第9回 発展1 RaggedRows
# フォルダのソースは演習ページの表示（row0 sum=6, row1 sum=9, original=40）どおり。その他は別の版でテストする
#   swap_with_lengths … 反復処理の前に rows と lengths を一組で交換する断片を追加した版
#   means             … 交換前の全要素の平均と，行平均の単純な平均を表示する版
#   animal / letters  … 二重ポインタの別の使い方（versions/ の 2 つの例をそのままビルド）
softprac_add_program(RaggedRows ragged_rows.c)

set(loop_start "    for (int r = 0; r < 2; ++r) {")

softprac_add_variant(RaggedRows ragged_rows.c swap_with_lengths "    int **p = rows;
${loop_start}" [=[    int **p = rows;
    int *temp_row = rows[0];
    rows[0] = rows[1];
    rows[1] = temp_row;
    int temp_length = lengths[0];
    lengths[0] = lengths[1];
    lengths[1] = temp_length;
    for (int r = 0; r < 2; ++r) {]=])
softprac_add_variant(RaggedRows ragged_rows.c means "    p[1][0] = 40;" [=[    int total = 0;
    int count = 0;
    double sum_of_means = 0.0;
    for (int r = 0; r < 2; ++r) {
        int sum = 0;
        for (int c = 0; c < lengths[r]; ++c) {
            sum += p[r][c];
        }
        total += sum;
        count += lengths[r];
        sum_of_means += (double)sum / lengths[r];
    }
    printf("all elements: %d / %d = %.2f\n", total, count, (double)total / count);
    printf("mean of row means = %.2f\n", sum_of_means / 2);
    p[1][0] = 40;]=])
softprac_add_variant(RaggedRows versions/animal.c animal)
softprac_add_variant(RaggedRows versions/letters.c letters)
