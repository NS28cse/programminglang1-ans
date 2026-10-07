# 第12回 課題1・2 SplitCalc: ソースは自動の規則と同じ（main.c・calc.c・calc.h）
softprac_add_program(SplitCalc main.c calc.c calc.h)

# 課題1: 講義の 3 ファイルの版（課題2 で加えた subtract・calc_divide の呼び出しを除く）。add=3.5，multiply=3.0
softprac_add_variant(SplitCalc main.c lecture
  [=[    printf("subtract=%.1f\n", subtract(5.0, 2.0));
    double q = 99.0;  /* 失敗したときに保存先が変わらないことを確かめるための初期値 */
    int ok = calc_divide(6.0, 2.0, &q);
    printf("calc_divide(6.0, 2.0): ok=%d q=%.1f\n", ok, q);
]=] "")

# 課題2 の検証表（本体は subtract(5, 2) と calc_divide(6, 2)）。variants/tests/<ケース>.out
softprac_add_variant(SplitCalc main.c sub_0_0 "subtract(5.0, 2.0)" "subtract(0.0, 0.0)")
softprac_add_variant(SplitCalc main.c sub_2_5 "subtract(5.0, 2.0)" "subtract(2.0, 5.0)")
softprac_add_variant(SplitCalc main.c div_m6_2
  "calc_divide(6.0, 2.0): " "calc_divide(-6.0, 2.0): "
  "calc_divide(6.0, 2.0, &q)" "calc_divide(-6.0, 2.0, &q)")
softprac_add_variant(SplitCalc main.c div_0_2
  "calc_divide(6.0, 2.0): " "calc_divide(0.0, 2.0): "
  "calc_divide(6.0, 2.0, &q)" "calc_divide(0.0, 2.0, &q)")
# 0 で割る: 失敗（ok=0）で，q は初期値 99.0 のまま
softprac_add_variant(SplitCalc main.c div_6_0
  "calc_divide(6.0, 2.0): " "calc_divide(6.0, 0.0): "
  "calc_divide(6.0, 2.0, &q)" "calc_divide(6.0, 0.0, &q)")
