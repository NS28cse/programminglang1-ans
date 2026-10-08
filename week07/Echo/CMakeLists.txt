# 第7回 課題1 Echo
# 本体（講義の echo.c）に加えて，演習ページの 2 つの書き換えをした版と，採点のポイントの誤りの例 2 つをテストする
#   slash    : putchar(ch) の前に putchar('/') とその戻り値の確認を加えた版
#   visible  : putchar とその失敗処理を，改行を見える形で表示する printf に置き換えた版
#   no_parens: （誤り）while (ch = getchar() != EOF) と括弧を省いた版（ch には比較結果 1 が入る）
#   char_ch  : （誤り）getchar の戻り値を char で受けた版（char が符号付きなら 0xFF で止まる）
# 期待値は variants/tests/<版>--<入力の名前>.*。各版は先頭行とコメントも版の説明に置き換える
softprac_add_program(Echo echo.c)

softprac_add_variant(Echo echo.c slash
  [=[// 第7回 課題1: 入力をそのまま出力する（講義の echo.c）]=]
  [=[// 第7回 課題1: putchar(ch) の前に putchar('/') と戻り値の確認を加えた版（講義の echo.c を変更）]=]
  [=[        if (putchar(ch) == EOF) {]=]
  [=[        if (putchar('/') == EOF) { // 追加: 各文字（改行も含む）の前に / を出す
            fprintf(stderr, "output error\n");
            return 1;
        }
        if (putchar(ch) == EOF) {]=])

softprac_add_variant(Echo echo.c visible
  [=[// 第7回 課題1: 入力をそのまま出力する（講義の echo.c）]=]
  [=[// 第7回 課題1: putchar を，改行を見える形で表示する printf に一時的に置き換えた版（講義の echo.c を変更）]=]
  [=[        if (putchar(ch) == EOF) {
            fprintf(stderr, "output error\n");
            return 1;
        }]=]
  [=[        if (ch == '\n') { // 置き換え: 改行は new line，それ以外は character=文字 と表示する
            printf("new line\n");
        } else {
            printf("character=%c\n", ch);
        }]=])

# 誤りの例 1: 括弧を省くと != が先に評価され，ch には比較結果 1 が入る（ab と Enter で 0x01 が 3 バイト出る）。
# 条件式の中の代入なので GCC/Clang は -Wparentheses，MSVC は C4706 の警告を出し，警告をエラーにする設定では
# ビルドが止まる。この版は誤りの動作を確かめるためのものなので，この版だけその警告を抑止する
softprac_add_variant(Echo echo.c no_parens
  [=[// 第7回 課題1: 入力をそのまま出力する（講義の echo.c）]=]
  [=[// 第7回 課題1: よくある誤りの例（while (ch = getchar() != EOF) と括弧を省いた版。ch には比較結果 1 が入る）]=]
  [=[    while ((ch = getchar()) != EOF) {]=]
  [=[    while (ch = getchar() != EOF) { // （誤り）!= が先に評価され，ch には比較結果の 1 が入る]=])
target_compile_options(Echo_no_parens PRIVATE $<IF:$<C_COMPILER_ID:MSVC>,/wd4706,-Wno-parentheses>)

# 誤りの例 2: char で受けると，char が符号付きの環境ではバイト 0xFF が -1 になり EOF と等しくなって途中で止まる
# （ab 0xFF cd と改行を与えると ab だけ出る）。char の符号は処理系定義なので，結果を固定するため
# GCC/Clang では -fsigned-char を付ける（MSVC の char は既定で符号付き）。
# MSVC は int から char への代入に C4244 を出すので，この版だけ抑止する（GCC/Clang の -Wall -Wextra では警告なし）
softprac_add_variant(Echo echo.c char_ch
  [=[// 第7回 課題1: 入力をそのまま出力する（講義の echo.c）]=]
  [=[// 第7回 課題1: よくある誤りの例（getchar の戻り値を char で受けた版。char が符号付きなら 0xFF で止まる）]=]
  [=[    int ch; // EOF と 256 通りのバイト値を区別するため char ではなく int で受ける]=]
  [=[    char ch; // （誤り）char では 0xFF のバイトと EOF を区別できない（符号付きなら 0xFF が -1 になる）]=])
target_compile_options(Echo_char_ch PRIVATE $<IF:$<C_COMPILER_ID:MSVC>,/wd4244,-fsigned-char>)
