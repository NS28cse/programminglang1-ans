# 第8回 課題2 MinMax
# フォルダのソースは配列 {7, -2, 9, 0} の最終版。演習ページの各確認は一部を書き換えた版としてテストする
#   trace         … 各要素を読み終えた時点の *low と *high を表示する（「候補の変化を追跡する」の表）
#   single_5 など … main の配列を検証表の配列に変え，呼び出しの n も合わせる
#   same_address / overlap … 契約違反の確認（ファイル末尾）
softprac_add_program(MinMax min_max.c)

set(trace_line [=[        printf("read %d: *low=%d *high=%d\n", a[i], *low, *high);
]=])
softprac_add_variant(MinMax min_max.c trace
  [=[    *high = a[0];
]=]
  [=[    *high = a[0];
    printf("read %d: *low=%d *high=%d\n", a[0], *low, *high);
]=]
  [=[            *high = a[i];
        }
]=]
  "            *high = a[i];
        }
${trace_line}")
softprac_add_variant(MinMax min_max.c single_5 "{7, -2, 9, 0}" "{5}" "min_max(data, 4" "min_max(data, 1")
softprac_add_variant(MinMax min_max.c same_3 "{7, -2, 9, 0}" "{3, 3, 3}" "min_max(data, 4" "min_max(data, 3")
softprac_add_variant(MinMax min_max.c all_negative "{7, -2, 9, 0}" "{-8, -2, -5}" "min_max(data, 4" "min_max(data, 3")
softprac_add_variant(MinMax min_max.c five_elements "{7, -2, 9, 0}" "{7, 2, 10, 3, 5}" "min_max(data, 4" "min_max(data, 5")

# 契約違反の確認（範囲外・寿命切れではないので動作は定義されている。結果が壊れることを示す）
#   same_address … low と high へ同じアドレスを渡す（最小値でも最大値でもない 0 が残る）
#   overlap      … 入力配列の要素 data[1] を出力先にする（未読の入力 -2 が上書きされる）
set(call_and_print [=[    min_max(data, 4, &low, &high);   /* 要素数を変えたら n も合わせる */
    printf("min=%d max=%d\n", low, high);]=])
softprac_add_variant(MinMax min_max.c same_address
  "    int high;
" ""
  "${call_and_print}"
  [=[    min_max(data, 4, &low, &low);
    printf("same address: low=%d\n", low);]=])
softprac_add_variant(MinMax min_max.c overlap
  "    int low;   /* min_max が書き込んだ後に初めて読む */
" ""
  "${call_and_print}"
  [=[    min_max(data, 4, &data[1], &high);
    printf("overlap: min=%d max=%d data={%d, %d, %d, %d}\n", data[1], high, data[0], data[1], data[2], data[3]);]=])
