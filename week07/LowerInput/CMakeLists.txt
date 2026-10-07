# 第7回 課題1 LowerInput
# 本体に加えて，次の版をテストする。期待値は variants/tests/<版>--<入力>.*
#   strict: よくある誤り「範囲を > / < で判定する」版（端の 'A'・'Z' が変換されない）
#   status: 課題4 のプログラム A（処理状況を stderr へ出す小文字化フィルタ）。stdout はデータだけになる
#   ready : status にさらに stdout へ "Ready" と改行を出す版（課題4 問5。下流の B はこれも数える）
softprac_add_program(LowerInput lower_input.c)

softprac_add_variant(LowerInput lower_input.c strict
  "ch >= 'A' && ch <= 'Z'" "ch > 'A' && ch < 'Z'")

softprac_add_variant(LowerInput lower_input.c status
  [=[    int ch;
]=]
  [=[    int ch;
    fprintf(stderr, "A: start\n");
]=]
  [=[    return 0;
]=]
  [=[    fprintf(stderr, "A: done\n");
    return 0;
]=])

softprac_add_variant(LowerInput lower_input.c ready
  [=[    int ch;
]=]
  [=[    int ch;
    fprintf(stderr, "A: start\n");
    printf("Ready\n");
]=]
  [=[    return 0;
]=]
  [=[    fprintf(stderr, "A: done\n");
    return 0;
]=])
