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
# 誤りの例（README の採点のポイント）: クリアに論理否定 ! を使う → flags 全体が 0 になる
softprac_add_variant(Flags flags.c wrong_clear_not "flags &= ~read_mask" "flags &= !read_mask")
# 誤りの例: クリアに XOR を使う → 読む権限が 0 のとき（初期値 0u）に逆に 1 になる
softprac_add_variant(Flags flags.c wrong_clear_xor_start_0
  "flags = 1u" "flags = 0u"
  "flags &= ~read_mask" "flags ^= read_mask")
