# 第7回 課題1 Echo
# 本体は講義の echo.c。演習ページの 2 つの書き換えと，採点のポイントの誤りの例 2 つを版としてテストする
#   slash    : putchar(ch) の前に putchar('/') とその戻り値の確認を加えた版
#   visible  : putchar とその失敗処理を，改行を見える形で表示する printf に置き換えた版
#   no_parens: （誤り）while (ch = getchar() != EOF) と括弧を省いた版（ch には比較結果 1 が入る）
#   char_ch  : （誤り）getchar の戻り値を char で受けた版（char が符号付きなら 0xFF で止まる）
# 期待値は variants/tests/<版>--<入力の名前>.*
softprac_add_program(Echo echo.c)

set(head "// 講義の echo.c。getchar で読んだ 1 バイトを，EOF になるまで putchar でそのまま書き出す。")

softprac_add_variant(Echo echo.c slash
  "${head}"
  "// putchar(ch) の前に putchar('/') とその戻り値の確認を加えた版（改行も含む各文字の前に / が付く）。"
  [=[        if (putchar(ch) == EOF) {]=]
  [=[        if (putchar('/') == EOF) { // 各文字（改行も含む）の前に / を出す
            fprintf(stderr, "output error\n");
            return 1;
        }
        if (putchar(ch) == EOF) {]=])

softprac_add_variant(Echo echo.c visible
  "${head}"
  "// putchar とその失敗処理を，改行を見える形で表示する printf に置き換えた版。"
  [=[        if (putchar(ch) == EOF) {
            fprintf(stderr, "output error\n");
            return 1;
        }]=]
  [=[        if (ch == '\n') { // 改行は new line，それ以外は character=文字 と表示する
            printf("new line\n");
        } else {
            printf("character=%c\n", ch);
        }]=])

# 誤りの例 1: 条件式の中の代入なので GCC/Clang は -Wparentheses，MSVC は C4706 を出す。誤りの動作を確かめるため，この版だけ抑止する
softprac_add_variant(Echo echo.c no_parens
  "${head}"
  "// よくある誤りの例: while (ch = getchar() != EOF) と括弧を省いた版（ch には比較結果 1 が入る）。"
  [=[    while ((ch = getchar()) != EOF) {]=]
  [=[    while (ch = getchar() != EOF) { // （誤り）!= が先に評価され，ch には比較結果の 1 が入る]=])
target_compile_options(Echo_no_parens PRIVATE $<IF:$<C_COMPILER_ID:MSVC>,/wd4706,-Wno-parentheses>)

# 誤りの例 2: MSVC は int から char への代入に C4244 を出すので，この版だけ抑止する。
# char の符号は処理系定義なので，結果を固定するため GCC/Clang では -fsigned-char を付ける（MSVC の char は既定で符号付き）
softprac_add_variant(Echo echo.c char_ch
  "${head}"
  "// よくある誤りの例: getchar の戻り値を char で受けた版（char が符号付きなら 0xFF のバイトで止まる）。"
  [=[    int ch; // EOF と 256 通りのバイト値を区別するため char ではなく int で受ける]=]
  [=[    char ch; // （誤り）char では 0xFF のバイトと EOF を区別できない（符号付きなら 0xFF が -1 になる）]=])
target_compile_options(Echo_char_ch PRIVATE $<IF:$<C_COMPILER_ID:MSVC>,/wd4244,-fsigned-char>)
