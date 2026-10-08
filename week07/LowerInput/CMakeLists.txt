# 第7回 課題1 LowerInput
# 本体に加えて，次の版をテストする。期待値は variants/tests/<版>--<入力>.*
#   strict: よくある誤り「範囲を > / < で判定する」版（端の 'A'・'Z' が変換されない）
#   status: 課題4 のプログラム A（処理状況を stderr へ出す小文字化フィルタ）。stdout はデータだけになる
#   ready : status にさらに stdout へ "Ready" と改行を出す版（課題4 問5。下流の B はこれも数える）
# 各版は先頭行とコメントも版の説明に置き換える
softprac_add_program(LowerInput lower_input.c)

softprac_add_variant(LowerInput lower_input.c strict
  [=[// 第7回 課題1: 小文字化フィルタ（ASCII の英大文字だけを小文字にして出力する）]=]
  [=[// 第7回 課題1: よくある誤りの例（小文字化フィルタの範囲を > と < で判定した版。端の 'A'・'Z' が変換されない）]=]
  [=[        // EOF を除いた後なので ch は実際に読んだ 1 バイト。範囲内だけを変換する]=]
  [=[        // （誤り）> と < で判定しているので端の 'A'・'Z' が変換されない]=]
  [=[        if (ch >= 'A' && ch <= 'Z') {]=]
  [=[        if (ch > 'A' && ch < 'Z') {]=])

softprac_add_variant(LowerInput lower_input.c status
  [=[// 第7回 課題1: 小文字化フィルタ（ASCII の英大文字だけを小文字にして出力する）]=]
  [=[// 第7回 課題4: プログラム A（小文字化し，処理状況を stderr へ出す版）]=]
  [=[    int ch;
]=]
  [=[    int ch;
    fprintf(stderr, "A: start\n"); // 処理状況は stderr へ（stdout のデータに混ざらない）
]=]
  [=[    return 0;
]=]
  [=[    fprintf(stderr, "A: done\n");
    return 0;
]=])

softprac_add_variant(LowerInput lower_input.c ready
  [=[// 第7回 課題1: 小文字化フィルタ（ASCII の英大文字だけを小文字にして出力する）]=]
  [=[// 第7回 課題4: プログラム A（小文字化し，処理状況を stderr へ出し，さらに stdout へ Ready と改行を出す版）]=]
  [=[    int ch;
]=]
  [=[    int ch;
    fprintf(stderr, "A: start\n"); // 処理状況は stderr へ（stdout のデータに混ざらない）
    printf("Ready\n");             // stdout へ出すので，データと一緒に下流の B に数えられる
]=]
  [=[    return 0;
]=]
  [=[    fprintf(stderr, "A: done\n");
    return 0;
]=])
