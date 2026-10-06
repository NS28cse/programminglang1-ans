# 第9回 課題1 ReturnMaximum
# 本体に加えて，max_value の最大候補を 0 から始めた（誤った）版をビルドしてテストする
softprac_add_program(ReturnMaximum return_maximum.c)

softprac_add_variant(ReturnMaximum return_maximum.c best_zero "int best = a[0]" "int best = 0")
