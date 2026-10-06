# 第8回 課題2 MinMax
# 本体に加えて，main の配列を検証表の配列へ書き換え，呼び出しの n も合わせた版をテストする
softprac_add_program(MinMax min_max.c)

softprac_add_variant(MinMax min_max.c single_5 "{7, -2, 9, 0}" "{5}"
                     "min_max(data, 4" "min_max(data, 1" "report(data, 4)" "report(data, 1)")
softprac_add_variant(MinMax min_max.c same_3 "{7, -2, 9, 0}" "{3, 3, 3}"
                     "min_max(data, 4" "min_max(data, 3" "report(data, 4)" "report(data, 3)")
softprac_add_variant(MinMax min_max.c all_negative "{7, -2, 9, 0}" "{-8, -2, -5}"
                     "min_max(data, 4" "min_max(data, 3" "report(data, 4)" "report(data, 3)")
softprac_add_variant(MinMax min_max.c five_elements "{7, -2, 9, 0}" "{7, 2, 10, 3, 5}"
                     "min_max(data, 4" "min_max(data, 5" "report(data, 4)" "report(data, 5)")
