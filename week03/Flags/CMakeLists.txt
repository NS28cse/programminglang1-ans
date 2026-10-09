# 第3回 課題5（発展） Flags: 本体（flags = 1u）と，最初の flags を変えた版，同じ権限を 2 回セットする版（OR と加算），
# 誤りの例（クリアに ! や ^ を使う），比較用ソース（versions/）
softprac_add_program(Flags flags.c)

set(title "/* 第3回 課題5（発展） 権限フラグ（Flags / flags.c）")
set(header "${title}\n * unsigned int の各ビットを権限として使い，マスクでセット・クリア・反転して，権限の有無を調べる。\n */")
set(start_line "    unsigned int flags = 1u;            /* 初期値: 読む権限だけ */")
set(set_line "    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */")
set(clear_line "    flags &= ~read_mask;  /* クリア: 対象ビットだけ0のマスクと AND */")

softprac_add_variant(Flags flags.c start_0
  "${header}"
  "${title}\n * ビット列で確かめる: 最初の flags を 0u（権限なし）に書き換えた版。\n */"
  "${start_line}"
  "    unsigned int flags = 0u;            /* 初期値: 権限なし（000） */")
softprac_add_variant(Flags flags.c start_7
  "${header}"
  "${title}\n * ビット列で確かめる: 最初の flags を 7u（3 つの権限すべて）に書き換えた版。\n */"
  "${start_line}"
  "    unsigned int flags = 7u;            /* 初期値: 3つの権限すべて（111） */")
# 書く権限のセットを 2 行続けて行う（OR と，OR の代わりに加算）
softprac_add_variant(Flags flags.c set_twice_or
  "${header}"
  "${title}\n * 説明すること: 書く権限を OR で 2 回続けてセットする版（1 回のときと同じ 3）。\n */"
  "${set_line}"
  "    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */\n    flags |= write_mask;  /* 2回目: 既に1なので変わらない */")
softprac_add_variant(Flags flags.c set_twice_add
  "${header}"
  "${title}\n * 説明すること: 書く権限を OR の代わりに加算で 2 回続けてセットする版（桁上がりして 5 になる）。\n */"
  "${set_line}"
  "    flags += write_mask;  /* 加算でセット: 001 + 010 = 011 */\n    flags += write_mask;  /* 2回目: 011 + 010 = 101 と桁上がりする */")
# 誤りの例（採点のポイント）: クリアに論理否定 ! を使う → flags 全体が 0 になる
softprac_add_variant(Flags flags.c wrong_clear_not
  "${header}"
  "${title}\n * 誤りの例: 読む権限のクリアに論理否定 ! を使った版（flags 全体が 0 になる）。\n */"
  "${clear_line}"
  "    flags &= !read_mask;  /* 誤りの例: !read_mask は論理否定で 0 なので，flags 全体が 0 になる */")
# 誤りの例: クリアに XOR を使う → 読む権限が 0 のとき（初期値 0u）に逆に 1 になる
softprac_add_variant(Flags flags.c wrong_clear_xor_start_0
  "${header}"
  "${title}\n * 誤りの例: 最初の flags を 0u にし，読む権限のクリアに XOR を使った版（逆に 1 になる）。\n */"
  "${start_line}"
  "    unsigned int flags = 0u;            /* 初期値: 権限なし（000） */"
  "${clear_line}"
  "    flags ^= read_mask;   /* 誤りの例: XOR は反転なので，読む権限が 0 だと逆に 1 になる */")

# 説明すること: 1u + 1u と 1u | 1u
softprac_add_variant(Flags versions/or_vs_add.c or_vs_add)
# 確認問題 7: 4u & 2u と 4u && 2u
softprac_add_variant(Flags versions/and_vs_logical_and.c and_vs_logical_and)
