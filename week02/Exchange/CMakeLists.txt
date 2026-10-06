# 第2回 課題3 Exchange
# 本体に加えて，「別の値でも確認する」（a = -3, b = 8 と a = 5, b = 5）版をビルドしてテストする
softprac_add_program(Exchange exchange.c)

softprac_add_variant(Exchange exchange.c a_m3_b_8 "int a = 10" "int a = -3" "int b = 20" "int b = 8")
softprac_add_variant(Exchange exchange.c a_5_b_5 "int a = 10" "int a = 5" "int b = 20" "int b = 5")
