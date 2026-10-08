# 第10回 課題3 Binary
# 本体は講義の binary.c（41 00 42 0A）。演習ページの小問を variant としてビルドしてテストする（期待値: variants/tests/<版>.*）
#   utf8_a: data を UTF-8 の「あ」と LF（E3 81 82 0A）へ置き換えた版
#   show_n: 読み取った個数 n を printf で追加表示する版
softprac_add_program(Binary binary.c)

softprac_add_variant(Binary binary.c utf8_a
  [[（講義の binary.c） */]]
  [[（講義の binary.c の data を UTF-8 の「あ」と LF へ置き換えた版） */]]
  [[    /* 途中に 00 を含むので文字列ではない。個数は sizeof data で扱う */
    const unsigned char data[] = {0x41, 0x00, 0x42, 0x0A};]]
  [[    /* ソースに日本語を直接書かずに，UTF-8 の「あ」（E3 81 82）と LF をバイト列で指定する（BOM は付けない） */
    const unsigned char data[] = {0xE3, 0x81, 0x82, 0x0A};]])
softprac_add_variant(Binary binary.c show_n
  [[（講義の binary.c） */]]
  [[（講義の binary.c に，読み取った個数 n の表示を追加した版） */]]
  [[    for (size_t i = 0; i < n; ++i) {]]
  [[    printf("n=%zu\n", n);   /* size=1 なので n は読めたバイト数 */
    for (size_t i = 0; i < n; ++i) {]])
