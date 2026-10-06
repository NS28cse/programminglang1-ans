# 第7回 課題4 Formats
# 本体に加えて，n を 123456 に，base の初期値を八進 0764u・十六進 0x1f4u に変えた版をテストする
softprac_add_program(Formats formats.c)

softprac_add_variant(Formats formats.c n_123456 "int n = 3" "int n = 123456")
softprac_add_variant(Formats formats.c base_octal "500u" "0764u")
softprac_add_variant(Formats formats.c base_hex "500u" "0x1f4u")
