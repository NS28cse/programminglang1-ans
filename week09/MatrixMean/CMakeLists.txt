# 第9回 課題3 MatrixMean
# 本体に加えて，(double) を外した整数除算の版と，仮引数を int a[][COLS] と書いた版をビルドしてテストする
softprac_add_program(MatrixMean matrix.c)

softprac_add_variant(MatrixMean matrix.c int_division "double mean = (double)total / COLS" "double mean = total / COLS")
softprac_add_variant(MatrixMean matrix.c array_param "void print_means(int (*a)[COLS], int rows)" "void print_means(int a[][COLS], int rows)")
