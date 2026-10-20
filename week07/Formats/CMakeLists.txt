# 第7回 課題4 Formats
# 本体は演習ページのコード。n を 123456 に，base の初期値を八進 0764u・十六進 0x1f4u に変えた版をテストする
softprac_add_program(Formats formats.c)

set(head "// 演習ページのコード。printf の幅・精度・基数・長さ修飾子による表示を確かめる（入力は待たない）。")

softprac_add_variant(Formats formats.c n_123456
  "${head}"
  "// n を 123456 に変えた版（%5d でも 6 桁すべて表示される）。"
  [=[    int n = 3;]=]
  [=[    int n = 123456; // 幅 5 より桁が多いが，幅は最小値なので切り詰めない]=])
softprac_add_variant(Formats formats.c base_octal
  "${head}"
  "// base を八進の 0764u に変えた版（十進の 500 と同じ値なので出力は変わらない）。"
  [=[    unsigned int base = 500u;]=]
  [=[    unsigned int base = 0764u; // 八進の 764 = 十進の 500]=])
softprac_add_variant(Formats formats.c base_hex
  "${head}"
  "// base を十六進の 0x1f4u に変えた版（十進の 500 と同じ値なので出力は変わらない）。"
  [=[    unsigned int base = 500u;]=]
  [=[    unsigned int base = 0x1f4u; // 十六進の 1f4 = 十進の 500]=])
