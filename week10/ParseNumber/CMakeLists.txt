# 第10回 課題2 ParseNumber: 本体は講義の parse_number.c。
# 「複数の数値を合計するなら」の断片へ置き換えた版（sum）もビルドしてテストする。先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(ParseNumber parse_number.c)

softprac_add_variant(ParseNumber parse_number.c sum
  [[   講義の parse_number.c。引数の整数 1 個（0〜100）を strtol で検査して表示する */]]
  [[   講義の parse_number.c を合計版にしたもの。引数の整数（各 0〜100，1〜10 個）を検査して合計を表示する */]]
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
]]
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
]])
