# 第10回 課題1 LineLengths: 本体は講義の line_lengths.c。
# 別解の versions/count_chars.c（fgetc で 1 文字ずつ数え，行を配列に保存しない版）も，本体の tests/ と同じ引数・入力でテストする
softprac_add_program(LineLengths line_lengths.c)

softprac_add_variant(LineLengths versions/count_chars.c count_chars)
