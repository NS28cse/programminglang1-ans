# 第9回 課題1 ReturnMaximum
# フォルダのソースは演習ページの表示（before=12 12, after=12 99）どおり。書き換えは variant でテストする
#   negative    … 配列を {-7, -12, -4} にした版
#   pointer_n0  … 場所を返す版だけ n を 0 にした版（何も表示しない）
#   best_zero   … {-7, -12, -4} で，max_value の最大候補を 0 から始めた（誤った）版
softprac_add_program(ReturnMaximum return_maximum.c)

softprac_add_variant(ReturnMaximum return_maximum.c negative "{7, 12, 4}" "{-7, -12, -4}")
softprac_add_variant(ReturnMaximum return_maximum.c pointer_n0 "max_pointer(a, 3)" "max_pointer(a, 0)")
softprac_add_variant(ReturnMaximum return_maximum.c best_zero "{7, 12, 4}" "{-7, -12, -4}" "int best = a[0];" "int best = 0;")
