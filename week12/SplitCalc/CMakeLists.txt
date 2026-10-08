# 第12回 課題1・2 SplitCalc: ソースは自動の規則と同じ（main.c・calc.c・calc.h）
softprac_add_program(SplitCalc main.c calc.c calc.h)

# 各版の先頭コメント（本体の説明）を，その版の説明に置き換えるための文字列
set(sc_comment "計算関数を呼び出す側．main はこのファイルだけに置く")

# 課題1: 講義の 3 ファイルの版（課題2 で加えた subtract・calc_divide の呼び出しを除く）。add=3.5，multiply=3.0
softprac_add_variant(SplitCalc main.c lecture
  [=[    printf("subtract=%.1f\n", subtract(5.0, 2.0));
    double q = 99.0;  /* 失敗したときに保存先が変わらないことを確かめるための初期値 */
    int ok = calc_divide(6.0, 2.0, &q);
    printf("calc_divide(6.0, 2.0): ok=%d q=%.1f\n", ok, q);
]=] ""
  "${sc_comment}" "課題1 の講義の版（課題2 で加えた subtract・calc_divide の呼び出しを除いた版）")

# 課題2 の検証表（本体は subtract(5, 2) と calc_divide(6, 2)）。variants/tests/<ケース>.out
softprac_add_variant(SplitCalc main.c sub_0_0
  "subtract(5.0, 2.0)" "subtract(0.0, 0.0)"
  "${sc_comment}" "課題2 の検証表: subtract を 0 と 0 で呼ぶ版")
softprac_add_variant(SplitCalc main.c sub_2_5
  "subtract(5.0, 2.0)" "subtract(2.0, 5.0)"
  "${sc_comment}" "課題2 の検証表: subtract を 2 と 5 で呼ぶ版")
softprac_add_variant(SplitCalc main.c div_m6_2
  "calc_divide(6.0, 2.0): " "calc_divide(-6.0, 2.0): "
  "calc_divide(6.0, 2.0, &q)" "calc_divide(-6.0, 2.0, &q)"
  "${sc_comment}" "課題2 の検証表: calc_divide を -6 と 2 で呼ぶ版")
softprac_add_variant(SplitCalc main.c div_0_2
  "calc_divide(6.0, 2.0): " "calc_divide(0.0, 2.0): "
  "calc_divide(6.0, 2.0, &q)" "calc_divide(0.0, 2.0, &q)"
  "${sc_comment}" "課題2 の検証表: calc_divide を 0 と 2 で呼ぶ版")
# 0 で割る: 失敗（ok=0）で，q は初期値 99.0 のまま
softprac_add_variant(SplitCalc main.c div_6_0
  "calc_divide(6.0, 2.0): " "calc_divide(6.0, 0.0): "
  "calc_divide(6.0, 2.0, &q)" "calc_divide(6.0, 0.0, &q)"
  "${sc_comment}" "課題2 の検証表: calc_divide を 6 と 0 で呼ぶ版（失敗し，q は 99.0 のまま）")
