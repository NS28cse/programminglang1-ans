# 第3回 課題5（発展） Flags
# 本体に加えて，「ビット列で確かめる」（最初の flags を 0u，7u に変える）版と，
# 「説明すること」（同じ権限を 2 回セットする。OR と加算）版をビルドしてテストする
softprac_add_program(Flags flags.c)

softprac_add_variant(Flags flags.c start_0 "flags = 1u" "flags = 0u")
softprac_add_variant(Flags flags.c start_7 "flags = 1u" "flags = 7u")
# 書く権限のセットを 2 行続けて行う（OR 版と，OR の代わりに加算を使う版）
softprac_add_variant(Flags flags.c set_twice_or
  "    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */"
  "    flags |= write_mask;\n    flags |= write_mask;")
softprac_add_variant(Flags flags.c set_twice_add
  "    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */"
  "    flags += write_mask;\n    flags += write_mask;")
