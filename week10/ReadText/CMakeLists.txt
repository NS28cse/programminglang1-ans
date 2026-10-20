# 第10回 課題1 ReadText: 本体は講義の read_text.c。
# 別解の versions/read_lines.c（fgets で配列へまとめて読み，fputs で表示する版）も，本体の tests/ と同じ引数・入力でテストする
softprac_add_program(ReadText read_text.c)

softprac_add_variant(ReadText versions/read_lines.c read_lines)
