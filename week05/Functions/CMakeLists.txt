# 第5回 課題4 Functions
# 本体に加えて，「境界の値で確認する」の表の 6 つの呼び出し（average と power の引数を書き換えた版を 3 つ），
# 範囲の端，result を 0 で初期化した誤りの版，戻り値を変数に保存する前の版をビルドしてテストする
softprac_add_program(Functions functions.c)

softprac_add_variant(Functions functions.c a_0_0_p_2_0   "average(2.0f, 4.0f)" "average(0.0f, 0.0f)"  "power(2, 5)" "power(2, 0)")
softprac_add_variant(Functions functions.c a_m4_2_p_5_1  "average(2.0f, 4.0f)" "average(-4.0f, 2.0f)" "power(2, 5)" "power(5, 1)")
softprac_add_variant(Functions functions.c a_1_2_p_5_5   "average(2.0f, 4.0f)" "average(1.0f, 2.0f)"  "power(2, 5)" "power(5, 5)")
softprac_add_variant(Functions functions.c a_m100_m100_p_1_0 "average(2.0f, 4.0f)" "average(-100.0f, -100.0f)" "power(2, 5)" "power(1, 0)")
softprac_add_variant(Functions functions.c a_m100_100_p_1_5  "average(2.0f, 4.0f)" "average(-100.0f, 100.0f)"  "power(2, 5)" "power(1, 5)")
softprac_add_variant(Functions functions.c a_100_100     "average(2.0f, 4.0f)" "average(100.0f, 100.0f)")
softprac_add_variant(Functions functions.c result_0      "int result = 1;" "int result = 0;")
softprac_add_variant(Functions functions.c before_result
  [=[    float result = average(2.0f, 4.0f);  // 戻り値を変数に保存してから表示する
    printf("average=%.1f\n", result);]=]
  [=[    printf("average=%.1f\n", average(2.0f, 4.0f));]=])
