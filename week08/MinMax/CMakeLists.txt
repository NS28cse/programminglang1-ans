# 第8回 課題2 MinMax
# フォルダのソースは配列 {7, -2, 9, 0} の最終版。演習ページの各確認は一部を書き換えた版としてテストする
#   trace         … 各要素を読み終えた時点の *low と *high を表示する（「候補の変化を追跡する」の表）
#   single_5 など … main の配列を検証表の配列に変え，呼び出しの n も合わせる
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
