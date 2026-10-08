# 第7回 課題4 Formats
# 本体に加えて，n を 123456 に，base の初期値を八進 0764u・十六進 0x1f4u に変えた版をテストする。
# 各版は先頭行と書き換えた行のコメントも版の説明に置き換える
softprac_add_program(Formats formats.c)

softprac_add_variant(Formats formats.c n_123456
  [=[// 第7回 課題4: printf の幅・精度・基数・長さ修飾子を確かめる（入力は待たない）]=]
  [=[// 第7回 課題4: n を 123456 に変えた版（%5d でも 6 桁すべて表示）]=]
  [=[    int n = 3;]=]
  [=[    int n = 123456; // 幅 5 より桁が多いが，幅は最小値なので切り詰めない]=])
softprac_add_variant(Formats formats.c base_octal
  [=[// 第7回 課題4: printf の幅・精度・基数・長さ修飾子を確かめる（入力は待たない）]=]
  [=[// 第7回 課題4: base を 0764u に変えた版（出力は同じ）]=]
  [=[    unsigned int base = 500u;]=]
  [=[    unsigned int base = 0764u; // 八進の 764 = 十進の 500]=])
softprac_add_variant(Formats formats.c base_hex
  [=[// 第7回 課題4: printf の幅・精度・基数・長さ修飾子を確かめる（入力は待たない）]=]
  [=[// 第7回 課題4: base を 0x1f4u に変えた版（出力は同じ）]=]
  [=[    unsigned int base = 500u;]=]
  [=[    unsigned int base = 0x1f4u; // 十六進の 1f4 = 十進の 500]=])
