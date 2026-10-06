# 第10回 課題2 ParseNumber
# 本体（フォルダのソース）は「複数の数値を合計するなら」の断片へ置き換えた最終版。
# 置き換える前の講義の parse_number.c（1 個の整数を検査する版）も single としてビルドし，検証表のケースをテストする
#   期待値: variants/tests/single--<ケース>.*
softprac_add_program(ParseNumber parse_number.c)

softprac_add_variant(ParseNumber parse_number.c single
  [[/* 第10回 課題2 ParseNumber: 引数の整数（各 0〜100，1〜10 個）を検査して合計を表示する
   講義の parse_number.c の検査・変換部分を「複数の数値を合計するなら」の断片へ置き換えた最終版 */]]
  [[/* 第10回 課題2 ParseNumber（置き換え前の版）: 引数の整数 1 個（0〜100）を検査して表示する（講義の parse_number.c） */]]
  [[    if (argc < 2 || argc > 11) {
        fprintf(stderr, "expected 1 to 10 integers\n");
        return 1;
    }
    /* 各値は 0〜100，最大 10 個なので合計は 1000 以下で long の範囲内 */
    long total = 0;
    for (int i = 1; i < argc; ++i) {
        char *end;
        errno = 0;
        long value = strtol(argv[i], &end, 10);
        if (end == argv[i] || *end != '\0' || errno == ERANGE ||
            value < 0 || value > 100) {
            fprintf(stderr, "invalid integer\n");
            return 1;
        }
        total += value;
    }
    printf("%ld\n", total);
]]
  [[    if (argc != 2) {
        fprintf(stderr, "usage: ParseNumber integer\n");
        return 1;
    }
    char *end;
    errno = 0;
    long value = strtol(argv[1], &end, 10);
    if (argv[1] == end || *end != '\0' || errno == ERANGE ||
        value < 0 || value > 100) {
        fprintf(stderr, "expected an integer from 0 to 100\n");
        return 1;
    }
    printf("%ld\n", value);
]])
