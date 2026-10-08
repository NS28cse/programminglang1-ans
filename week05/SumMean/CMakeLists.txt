# 第5回 発展 SumMean
# 本体に加えて，演習ページの {0}・n=1 と {100, 100, 100}・n=3，範囲の最大（100 が 5 個），
# 合計関数単独で n = 0 を渡した確認用の版をビルドしてテストする。
# 各版は先頭コメントの 2〜3 行目も版の説明に置き換え，行末コメントの桁もそろえる
softprac_add_program(SumMean summean.c)

softprac_add_variant(SumMean summean.c zero_n_1
  "// 合計を返す sum_array と，平均を計算して表示する main に役割を分ける。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n（1〜COUNT）を別に持つ。"
  "// 演習ページの {0}，n = 1 に書き換えた版（total=0 mean=0.0）。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n を別に持つ。"
  [=[    int scores[COUNT] = {72, 85, 60, 93, 80};  // 値は 0〜100
    int n = COUNT;                             // 平均で割るので 1 以上]=]
  [=[    int scores[COUNT] = {0};  // 値は 0〜100
    int n = 1;                // 平均で割るので 1 以上]=])

softprac_add_variant(SumMean summean.c hundred_n_3
  "// 合計を返す sum_array と，平均を計算して表示する main に役割を分ける。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n（1〜COUNT）を別に持つ。"
  "// 演習ページの {100, 100, 100}，n = 3 に書き換えた版（total=300 mean=100.0）。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n を別に持つ。"
  [=[    int scores[COUNT] = {72, 85, 60, 93, 80};  // 値は 0〜100
    int n = COUNT;                             // 平均で割るので 1 以上]=]
  [=[    int scores[COUNT] = {100, 100, 100};  // 値は 0〜100
    int n = 3;                            // 平均で割るので 1 以上]=])

softprac_add_variant(SumMean summean.c full_100
  "// 合計を返す sum_array と，平均を計算して表示する main に役割を分ける。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n（1〜COUNT）を別に持つ。"
  "// 範囲の最大 {100, 100, 100, 100, 100}，n = 5 に書き換えた版（total=500 mean=100.0）。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n を別に持つ。"
  [=[    int scores[COUNT] = {72, 85, 60, 93, 80};  // 値は 0〜100
    int n = COUNT;                             // 平均で割るので 1 以上]=]
  [=[    int scores[COUNT] = {100, 100, 100, 100, 100};  // 値は 0〜100
    int n = COUNT;                                  // 平均で割るので 1 以上]=])

# 合計関数単独なら n = 0 も受け付ける（0 を返す）ことの確認。平均は 0 で割るので計算も表示もしない
softprac_add_variant(SumMean summean.c sum_only_n_0
  "// 合計を返す sum_array と，平均を計算して表示する main に役割を分ける。\n// 配列は最大 COUNT 要素を用意し，実際に使う要素数 n（1〜COUNT）を別に持つ。"
  "// 合計関数単独で n = 0 を渡した確認用の版（total=0）。\n// 平均は 0 で割ることになるので計算も表示もしない。"
  [=[    int scores[COUNT] = {72, 85, 60, 93, 80};  // 値は 0〜100
    int n = COUNT;                             // 平均で割るので 1 以上]=]
  [=[    int scores[COUNT] = {72, 85, 60, 93, 80};  // 値は 0〜100
    int n = 0;                                 // sum_array 単独なら 0 も受け付ける]=]
  [=[    printf("total=%d mean=%.1f\n", total, (double)total / n);  // 整数除算を避ける]=]
  [=[    printf("total=%d\n", total);  // n が 0 なので平均は表示しない]=])
