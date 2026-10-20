# 第13回 課題1・2 Dynamic
# 本体は起動引数の個数で動的配列を作り，合計・平均と逆順を表示する。課題1・2の確認用の版をテストする
softprac_add_program(Dynamic dynamic.c)

# 課題1「追跡表を作る」：初期化と集計のループで i，values[i]，sum を表示する版（n=3）
softprac_add_variant(Dynamic dynamic.c trace
  [=[// 課題2として，同じ領域の中で配列を逆順に並べ替えて表示してから解放する。]=]
  [=[// 課題1の追跡表のために，初期化と集計のループの各反復で i，values[i]，sum を表示する版（逆順の処理は同じ）。]=]
  [=[        sum += values[i];
]=]
  [=[        sum += values[i];
        printf("i=%zu values[i]=%d sum=%lld\n", i, values[i], sum);   // 追跡表の確認用
]=])

# 課題2の表「交換する添字の組」：交換するたびに組を表示する版（n=1，2，5）
# n=1 では n/2 = 0 でループが 0 回なので交換の行が出ず，本体の one_1 と同じ出力になる
softprac_add_variant(Dynamic dynamic.c swap_pairs
  [=[// 課題2として，同じ領域の中で配列を逆順に並べ替えて表示してから解放する。]=]
  [=[// 課題2として同じ領域の中で逆順にするとき，交換する添字の組を表示する版。]=]
  [=[        values[n - 1 - i] = temp;
]=]
  [=[        values[n - 1 - i] = temp;
        printf("swap values[%zu] <-> values[%zu]\n", i, n - 1 - i);   // 交換の組の確認用
]=])

# 課題2の考察「全要素について交換すると元の順序へ戻る」：i < n / 2 を i < n に変えた版
softprac_add_variant(Dynamic dynamic.c swap_all
  [=[// 課題2として，同じ領域の中で配列を逆順に並べ替えて表示してから解放する。]=]
  [=[// 課題2の逆順の処理を全要素の交換に変えた版（考察）。各組を 2 回交換するので元の順序に戻る。]=]
  [=[    // 課題2：先頭と末尾から組にして n/2 組だけ交換する（奇数個の中央の要素は動かさない）
    for (size_t i = 0; i < n / 2; ++i) {]=]
  [=[    // 考察の確認：全要素について交換する（各組を 2 回交換するので元の順序に戻る）
    for (size_t i = 0; i < n; ++i) {]=])
