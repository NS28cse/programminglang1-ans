# 第9回 発展1 RaggedRows
# フォルダのソースは演習ページの表示（row0 sum=6, row1 sum=9, original=40）どおり。その他は別の版でテストする
#   swap_with_lengths … 反復処理の前に rows と lengths を一組で交換する断片を追加した版
#   means             … 交換前の全要素の平均と，行平均の単純な平均を表示する版
#   animal / letters  … 二重ポインタの別の使い方（versions/ の 2 つの例をそのままビルド）
# 置換する版は先頭コメント（1〜3 行目）を版の説明に置き換え，書き換えた行のコメントも書き換え後のコードに合わせる。
# 置換前の文字列は行末のコメントまで含めた行全体にする
softprac_add_program(RaggedRows ragged_rows.c)

set(header [=[// 第9回 発展1　長さが異なる行を扱う（RaggedRows / ragged_rows.c）
// 配列本体（row0, row1），先頭を集めたポインタ配列（rows），長さの配列（lengths）の3種類を区別する。
// 長さも一緒に交換する版・平均の比較・二重ポインタの別の使い方は CMakeLists.txt の variant でテストする。]=])
set(p_line "    int **p = rows;")
set(write_line "    p[1][0] = 40;  // p[1] は row1 を指すので row1[0] が変わる")

softprac_add_variant(RaggedRows ragged_rows.c swap_with_lengths
  "${header}"
  "// 第9回 発展1　書き換え版 swap_with_lengths: 反復処理の前に，rows と lengths を一組で交換する断片を追加した版（RaggedRows）\n// 行と長さの対応が保たれるので row0 sum=9，row1 sum=6。交換後の p[1] は row0 を指すので original（row1[0]）は 4 のまま。"
  "${p_line}"
  [=[    int **p = rows;
    int *temp_row = rows[0];  // 行の先頭アドレスを交換する（行の内容は動かない）
    rows[0] = rows[1];
    rows[1] = temp_row;
    int temp_length = lengths[0];  // 長さも一組で交換する
    lengths[0] = lengths[1];
    lengths[1] = temp_length;]=]
  "${write_line}"
  "    p[1][0] = 40;  // 交換後の p[1] は row0 を指すので row0[0] が変わり，row1[0] は 4 のまま")
softprac_add_variant(RaggedRows ragged_rows.c means
  "${header}"
  "// 第9回 発展1　書き換え版 means: 全要素の平均と，行平均の単純な平均を表示する断片を p[1][0] = 40; の前に追加した版（RaggedRows）\n// 行の長さが違うので，全要素の平均（15 / 5 = 3.00）と行平均の平均（(2 + 4.5) / 2 = 3.25）は一致しない。"
  "${write_line}"
  [=[    int total = 0;     // 全要素の和
    int count = 0;     // 全要素の個数
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
    p[1][0] = 40;  // p[1] は row1 を指すので row1[0] が変わる]=])
softprac_add_variant(RaggedRows versions/animal.c animal)
softprac_add_variant(RaggedRows versions/letters.c letters)
