# 第8回 課題2 MinMax
# 本体は演習ページの配列 {7, -2, 9, 0} の版。演習ページの各確認は一部を書き換えた版としてテストする
#   trace         … 各要素を読み終えた時点の *low と *high を表示する（「候補の変化を追跡する」の表）
#   single_5 など … main の配列を検証表の配列に変え，呼び出しの n も合わせる
#   same_address / overlap … 契約違反の確認（ファイル末尾）
softprac_add_program(MinMax min_max.c)

# 本体の先頭コメントの説明の行。書き換えた版ではその後ろに版の説明を加える
set(head " * 配列の最小値と最大値を，2 つの出力先ポインタ low，high へ書き込む関数 min_max を作り，結果を表示する．")

set(trace_line [=[        printf("read %d: *low=%d *high=%d\n", a[i], *low, *high);
]=])
softprac_add_variant(MinMax min_max.c trace
  "${head}" "${head}
 * 各要素を読み終えた時点の *low と *high を表示する版（候補の変化の追跡表）．"
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
foreach(spec "single_5;{5};1" "same_3;{3, 3, 3};3" "all_negative;{-8, -2, -5};3" "five_elements;{7, 2, 10, 3, 5};5")
  list(GET spec 0 tag)
  list(GET spec 1 array)
  list(GET spec 2 n)
  softprac_add_variant(MinMax min_max.c ${tag}
    "${head}" "${head}
 * main の配列を検証表の ${array} に変え，呼び出しの n も ${n} に合わせた版．"
    "{7, -2, 9, 0}" "${array}" "min_max(data, 4" "min_max(data, ${n}")
endforeach()

# 契約違反の確認（範囲外・寿命切れではないので動作は定義されている。結果が壊れることを示す）
#   same_address … low と high へ同じアドレスを渡す（最小値でも最大値でもない 0 が残る）
#   overlap      … 入力配列の要素 data[1] を出力先にする（未読の入力 -2 が上書きされる）
set(call_and_print [=[    min_max(data, 4, &low, &high);   /* 要素数を変えたら n も合わせる */
    printf("min=%d max=%d\n", low, high);]=])
softprac_add_variant(MinMax min_max.c same_address
  "${head}" "${head}
 * 関数の前の契約にわざと違反し，low と high へ同じアドレスを渡す確認用の版．
 * 1 つの箱に最小と最大の更新が重なり，最小値でも最大値でもない値が残る．"
  "    int high;
" ""
  "${call_and_print}"
  [=[    min_max(data, 4, &low, &low);
    printf("same address: low=%d\n", low);]=])
softprac_add_variant(MinMax min_max.c overlap
  "${head}" "${head}
 * 関数の前の契約にわざと違反し，入力配列の要素 data[1] を出力先にする確認用の版．
 * 最初の *low = a[0] で未読の入力が上書きされ，結果も配列も壊れる．"
  "    int low;   /* min_max が書き込んだ後に初めて読む */
" ""
  "${call_and_print}"
  [=[    min_max(data, 4, &data[1], &high);
    printf("overlap: min=%d max=%d data={%d, %d, %d, %d}\n", data[1], high, data[0], data[1], data[2], data[3]);]=])
