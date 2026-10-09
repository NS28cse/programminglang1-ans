# 第10回 課題3 ByteOrder（演習ページの「別の main」。プロジェクト名は解答で付けた）
# 本体は講義の断片どおり value = 1 で，演習ページの期待する表示（サイズ 2，01 00）だけを出す。小問は書き換えた版でテストする
#   value_0x1234: 値を 0x1234 へ変更した版（34 12）
#   bits_of_byte: 演習ページの「1 バイトを 2 進数表示する」断片を return の前に足した版（00000001）
# 各版は先頭コメントの 2 行目を版の説明に置き換える（置換前の文字列は行全体）
softprac_add_program(ByteOrder byte_order.c)

set(desc [[   講義の観察用断片（unsigned short value = 1）を別の main にし，unsigned short のメモリ上のバイト順を観察する */]])

softprac_add_variant(ByteOrder byte_order.c value_0x1234
  "${desc}"
  [[   講義の観察用断片を別の main にし，値を 0x1234 へ変更した版（34 12 になる） */]]
  "    unsigned short value = 1;"
  "    unsigned short value = 0x1234;")
softprac_add_variant(ByteOrder byte_order.c bits_of_byte
  "${desc}"
  [[   講義の観察用断片を別の main にし，演習ページの 1 バイトを 2 進数表示する断片（00000001）を最後に足した版 */]]
  "    return 0;"
  [[    /* 1 バイトの中は上位ビット（bit 7）から表示する */
    unsigned char byte = 1;
    for (int bit = 7; bit >= 0; --bit) {
        putchar((byte & (1u << bit)) != 0 ? '1' : '0');
    }
    putchar('\n');
    return 0;]])
