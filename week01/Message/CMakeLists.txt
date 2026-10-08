# 第1回 課題2 Message
# 本体に加えて，次の 2 つの版をビルドしてテストする（各版は先頭コメントの 1 行目も版の説明に置き換える）
# - backslash_n_only: 説明すること（\n は 2 文字として表示されるか）の比較として，
#   Backslash の行を \\n（\ と n の 2 文字，改行なし）にした誤りの例
# - blank_line_in_first: 空行を 1 行目の printf の \n\n で作る別の書き方（出力は本体と同じ）
softprac_add_program(Message message.c)

softprac_add_variant(Message message.c backslash_n_only
  [=[// 第1回 課題2　改行と特殊な文字（Message / message.c）]=]
  [=[// 第1回 課題2　改行と特殊な文字（Message / message.c，誤りの例: Backslash の行を \\n にした版）]=]
  [=[    printf("Backslash: \\\n");          // \\ で \ を 1 文字，続く \n で改行]=]
  [=[    printf("Backslash: \\n");           // 誤りの例: \\n は \ と n の 2 文字になり，改行されない]=])

softprac_add_variant(Message message.c blank_line_in_first
  [=[// 第1回 課題2　改行と特殊な文字（Message / message.c）]=]
  [=[// 第1回 課題2　改行と特殊な文字（Message / message.c，空行を 1 行目の \n\n で作る版。出力は本体と同じ）]=]
  [=[    printf("My first C program\n");
    printf("\n");                       // 2 行目の空行（\n だけを表示する）]=]
  [=[    printf("My first C program\n\n");   // \n を 2 つ続けて，1 行目の改行と 2 行目の空行を作る]=])
