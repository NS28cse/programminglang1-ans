# 第10回 発展2 CheckValue: 本体は check_value.c。
# 別解の versions/store_values.c（値を全部配列に保存してから探す版）も，本体の tests/ と同じ引数・入力でテストする
softprac_add_program(CheckValue check_value.c)

softprac_add_variant(CheckValue versions/store_values.c store_values)
