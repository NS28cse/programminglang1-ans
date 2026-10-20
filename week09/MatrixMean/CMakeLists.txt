# 第9回 課題3 MatrixMean: 本体は行平均を表示し，元の配列で rows=ROWS。表の入力などは書き換えた版でテストする
#   rows1 / rows0         … print_means に渡す rows を 1，0 にした版
#   low_high / fraction   … 配列を {0,0,0},{100,100,100} / {1,1,2},{2,2,3} にした版
#   int_division          … fraction の配列で (double) を外した（整数除算の）版
#   array_param           … 仮引数を int a[][COLS] と書いた版（出力が本体と同じことを確かめるケース）
#   sizeof_check          … main で sizeof の式を確認する版（バイト数は処理系依存なので式との比較と商を表示）
#   overall / overall_rows0 … 全体平均を返す関数を追加した版（rows=2 と rows=0）
# 各版は先頭コメントの 2 行目を版の説明に置き換え，書き換えた行のコメントも合わせる（置換前の文字列は行全体）
softprac_add_program(MatrixMean matrix.c)

set(desc [=[// 2行3列の二次元配列（値は0〜100，列数は COLS=3 に固定）を関数へ渡し，行ごとの平均を表示する。]=])
set(init "    int a[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}};")
set(init_fraction "    int a[ROWS][COLS] = {{1, 1, 2}, {2, 2, 3}};  // 行平均が割り切れない値")
set(call "    print_means(a, ROWS);")
set(main_line "int main(void)")
set(return_line "    return 0;")
set(overall_func [=[// 全要素の平均を *mean へ書いて1を返す。rows<=0 は平均が定義できないので0を返す（*mean は変更しない）
int overall_mean(int (*a)[COLS], int rows, double *mean)
{
    if (rows <= 0) { return 0; }
    double sum = 0.0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < COLS; ++c) {
            sum += a[r][c];
        }
    }
    *mean = sum / ((double)rows * COLS);
    return 1;
}
int main(void)]=])
set(overall_call [=[    double mean = 0.0;
    if (overall_mean(a, ROWS_ARG, &mean)) {  // 0 が返ったら mean は使わない
        printf("overall mean=%.2f\n", mean);
    } else {
        printf("overall mean: undefined\n");
    }
    return 0;]=])
string(REPLACE "ROWS_ARG" "ROWS" overall_call_2 "${overall_call}")
string(REPLACE "ROWS_ARG" "0" overall_call_0 "${overall_call}")

# rows を 1，0 にする
softprac_add_variant(MatrixMean matrix.c rows1
  "${desc}"
  "// print_means に渡す rows を 1 にした版。\n// 先頭の 1 行だけを処理するので row0 だけを表示する。"
  "${call}" "    print_means(a, 1);  // 先頭の 1 行だけ")
softprac_add_variant(MatrixMean matrix.c rows0
  "${desc}"
  "// print_means に渡す rows を 0 にした版。\n// 処理する行がないので何も表示しない。"
  "${call}" "    print_means(a, 0);  // rows=0 なので何も表示しない")

# 表の入力: 値の両端 0 と 100，割り切れない平均，整数除算
softprac_add_variant(MatrixMean matrix.c low_high
  "${desc}"
  "// 配列を値の両端 {0, 0, 0}, {100, 100, 100} にした版。"
  "${init}" "    int a[ROWS][COLS] = {{0, 0, 0}, {100, 100, 100}};  // 値の両端 0 と 100")
softprac_add_variant(MatrixMean matrix.c fraction
  "${desc}"
  "// 配列を {1, 1, 2}, {2, 2, 3} にした版。\n// 行平均が割り切れない（4/3 と 7/3）ので，%.2f で 1.33 と 2.33 になる。"
  "${init}" "${init_fraction}")
softprac_add_variant(MatrixMean matrix.c int_division
  "${desc}"
  "// 誤りの例: 配列を {1, 1, 2}, {2, 2, 3} にし，(double)total / COLS の (double) を外した版。\n// int 同士の除算になり，行平均は 1.00 と 2.00（小数部分が失われる）。"
  "${init}" "${init_fraction}"
  "        double mean = (double)total / COLS;  // total / COLS だと整数除算になり小数部分が失われる"
  "        double mean = total / COLS;  // 誤りの例: int 同士の除算で小数部分が失われる")

# 仮引数を int a[][COLS] と書く（int (*a)[COLS] と同じ型なので出力も本体と同じ）
softprac_add_variant(MatrixMean matrix.c array_param
  "${desc}"
  "// print_means の仮引数を int a[][COLS] と書いた版。\n// 仮引数の int a[][COLS] は int (*a)[COLS] に調整されるので，出力は本体と同じ。"
  "// a は「int が COLS 個の行」へのポインタ。関数内の sizeof a はポインタの大きさなので行数は rows で受け取る"
  "// a[][COLS] と書いても a は「int が COLS 個の行」へのポインタ。関数内の sizeof a はポインタの大きさなので行数は rows で受け取る"
  "void print_means(int (*a)[COLS], int rows)"
  "void print_means(int a[][COLS], int rows)")

# main で sizeof の式を確認する（バイト数は処理系依存なので，式との比較（1 = 成り立つ）と商を表示）
softprac_add_variant(MatrixMean matrix.c sizeof_check
  "${desc}"
  "// main の最後で sizeof の式を確認する版。\n// バイト数は処理系依存なので，式との比較（1 なら成り立つ）と，行数・列数を表す商を表示する。"
  "${return_line}"
  [=[    // main の a は配列なので，sizeof a は配列全体の大きさ
    printf("sizeof a == 2 * COLS * sizeof(int): %d\n", sizeof a == 2 * COLS * sizeof(int));
    printf("sizeof a[0] == COLS * sizeof(int): %d\n", sizeof a[0] == COLS * sizeof(int));
    printf("sizeof a / sizeof a[0] = %zu\n", sizeof a / sizeof a[0]);           // 行数
    printf("sizeof a[0] / sizeof a[0][0] = %zu\n", sizeof a[0] / sizeof a[0][0]);  // 列数
    return 0;]=])

# 全体平均を返す関数 overall_mean を追加する（rows=ROWS と rows=0）
softprac_add_variant(MatrixMean matrix.c overall
  "${desc}"
  "// 全体平均を返す関数 overall_mean を追加し，rows=ROWS で呼ぶ版。\n// 行平均の表示に続けて，全 6 要素の平均 overall mean=3.50 を表示する。"
  "${main_line}" "${overall_func}"
  "${return_line}" "${overall_call_2}")
softprac_add_variant(MatrixMean matrix.c overall_rows0
  "${desc}"
  "// 全体平均を返す関数 overall_mean を追加し，rows=0 で呼ぶ版。\n// 要素がなく平均が定義できないので overall_mean は 0 を返し，undefined と表示する。"
  "${main_line}" "${overall_func}"
  "${return_line}" "${overall_call_0}")
