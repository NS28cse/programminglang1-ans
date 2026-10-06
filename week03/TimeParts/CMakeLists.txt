# 第3回 課題1 TimeParts
# 本体に加えて，「境界の値を試す」（seconds を 0，59，60，61 に変える）版と，
# 「説明すること」（右辺を seconds / 60 にする）版をビルドしてテストする
softprac_add_program(TimeParts time_parts.c)

softprac_add_variant(TimeParts time_parts.c seconds_0 "seconds = 3671" "seconds = 0")
softprac_add_variant(TimeParts time_parts.c seconds_59 "seconds = 3671" "seconds = 59")
softprac_add_variant(TimeParts time_parts.c seconds_60 "seconds = 3671" "seconds = 60")
softprac_add_variant(TimeParts time_parts.c seconds_61 "seconds = 3671" "seconds = 61")
# 参考: 入力範囲の上限
softprac_add_variant(TimeParts time_parts.c seconds_10000 "seconds = 3671" "seconds = 10000")
# seconds = 61 で，decimal_minutes の右辺を整数同士の除算にする（1.00 になる）
softprac_add_variant(TimeParts time_parts.c int_division_61
  "seconds = 3671" "seconds = 61"
  "seconds / 60.0" "seconds / 60")
