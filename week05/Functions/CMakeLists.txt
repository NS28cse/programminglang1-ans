# 第5回 課題4 Functions
# 本体に加えて，「境界の値で確認する」の表の 6 つの呼び出し（average と power の引数を書き換えた版を 3 つ），
# 範囲の端，result を 0 で初期化した誤りの版，戻り値を変数に保存する前の版をビルドしてテストする。
# 各版は先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(Functions functions.c)

softprac_add_variant(Functions functions.c a_0_0_p_2_0
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 境界の表の average(0.0f, 0.0f) と power(2, 0) に書き換えた版（0.0 と 1）。"
  "average(2.0f, 4.0f)" "average(0.0f, 0.0f)" "power(2, 5)" "power(2, 0)")

softprac_add_variant(Functions functions.c a_m4_2_p_5_1
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 境界の表の average(-4.0f, 2.0f) と power(5, 1) に書き換えた版（-1.0 と 5）。"
  "average(2.0f, 4.0f)" "average(-4.0f, 2.0f)" "power(2, 5)" "power(5, 1)")

softprac_add_variant(Functions functions.c a_1_2_p_5_5
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 境界の表の average(1.0f, 2.0f) と power(5, 5) に書き換えた版（1.5 と 3125）。"
  "average(2.0f, 4.0f)" "average(1.0f, 2.0f)" "power(2, 5)" "power(5, 5)")

softprac_add_variant(Functions functions.c a_m100_m100_p_1_0
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 範囲の端 average(-100.0f, -100.0f) と power(1, 0) に書き換えた版（-100.0 と 1）。"
  "average(2.0f, 4.0f)" "average(-100.0f, -100.0f)" "power(2, 5)" "power(1, 0)")

softprac_add_variant(Functions functions.c a_m100_100_p_1_5
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 範囲の端 average(-100.0f, 100.0f) と power(1, 5) に書き換えた版（0.0 と 1）。"
  "average(2.0f, 4.0f)" "average(-100.0f, 100.0f)" "power(2, 5)" "power(1, 5)")

softprac_add_variant(Functions functions.c a_100_100
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 範囲の端 average(100.0f, 100.0f) に書き換えた版（100.0。power は本体のまま 32）。"
  "average(2.0f, 4.0f)" "average(100.0f, 100.0f)")

softprac_add_variant(Functions functions.c result_0
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 誤りの例: power の result を 0 で初期化した版（power=0 になる）。"
  "int result = 1;  // 掛け算の単位元。exponent が 0 なら 1 のまま返す"
  "int result = 0;  // 誤り: 0 に何を掛けても 0 なので常に 0 を返す")
softprac_add_variant(Functions functions.c before_result
  "// 関数は main の後ろに定義し，main の前にプロトタイプ宣言を書く。"
  "// 「戻り値と表示を分ける」の変更前に書き換えた版（戻り値をそのまま printf に渡す。表示は本体と同じ）。"
  [=[    float result = average(2.0f, 4.0f);  // 戻り値を変数に保存してから表示する
    printf("average=%.1f\n", result);]=]
  [=[    printf("average=%.1f\n", average(2.0f, 4.0f));  // 戻り値をそのまま表示に使う]=])
