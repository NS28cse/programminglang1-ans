# 第9回 課題3 MatrixMean
# フォルダのソースは行平均を表示する最終版（元の配列，rows=ROWS）。表の入力などは書き換えた版でテストする
#   rows1 / rows0         … print_means に渡す rows を 1，0 にした版
#   low_high / fraction   … 配列を {0,0,0},{100,100,100} / {1,1,2},{2,2,3} にした版
#   int_division          … fraction の配列で (double) を外した（整数除算の）版
#   array_param           … 仮引数を int a[][COLS] と書いた版（出力は本体と同じ）
#   sizeof_check          … main で sizeof の式を確認する版（バイト数は処理系依存なので式との比較と商を表示）
#   overall / overall_rows0 … 全体平均を返す関数を追加した版（rows=2 と rows=0）
softprac_add_program(MatrixMean matrix.c)

set(init "{{1, 2, 3}, {4, 5, 6}}")
set(call "    print_means(a, ROWS);")
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
    if (overall_mean(a, ROWS_ARG, &mean)) {
        printf("overall mean=%.2f\n", mean);
    } else {
        printf("overall mean: undefined\n");
    }
    return 0;]=])
string(REPLACE "ROWS_ARG" "ROWS" overall_call_2 "${overall_call}")
string(REPLACE "ROWS_ARG" "0" overall_call_0 "${overall_call}")

softprac_add_variant(MatrixMean matrix.c rows1 "${call}" "    print_means(a, 1);")
softprac_add_variant(MatrixMean matrix.c rows0 "${call}" "    print_means(a, 0);")
softprac_add_variant(MatrixMean matrix.c low_high "${init}" "{{0, 0, 0}, {100, 100, 100}}")
softprac_add_variant(MatrixMean matrix.c fraction "${init}" "{{1, 1, 2}, {2, 2, 3}}")
softprac_add_variant(MatrixMean matrix.c int_division "${init}" "{{1, 1, 2}, {2, 2, 3}}"
  "double mean = (double)total / COLS;" "double mean = total / COLS;")
softprac_add_variant(MatrixMean matrix.c array_param "void print_means(int (*a)[COLS], int rows)" "void print_means(int a[][COLS], int rows)")
softprac_add_variant(MatrixMean matrix.c sizeof_check "    return 0;" [=[    printf("sizeof a == 2 * COLS * sizeof(int): %d\n", sizeof a == 2 * COLS * sizeof(int));
    printf("sizeof a[0] == COLS * sizeof(int): %d\n", sizeof a[0] == COLS * sizeof(int));
    printf("sizeof a / sizeof a[0] = %zu\n", sizeof a / sizeof a[0]);
    printf("sizeof a[0] / sizeof a[0][0] = %zu\n", sizeof a[0] / sizeof a[0][0]);
    return 0;]=])
softprac_add_variant(MatrixMean matrix.c overall "int main(void)" "${overall_func}" "    return 0;" "${overall_call_2}")
softprac_add_variant(MatrixMean matrix.c overall_rows0 "int main(void)" "${overall_func}" "    return 0;" "${overall_call_0}")
