# 第3回 課題5（発展） Flags
# 本体（flags = 1u）に加えて，「ビット列で確かめる」（最初の flags を 0u，7u に変える）版，
# 「説明すること」（同じ権限を 2 回セットする。OR と加算）版，誤りの例（クリアに ! や ^ を使う）と，
# 比較用ソース（versions/ の 1u + 1u と 1u | 1u，4u & 2u と 4u && 2u）をビルドしてテストする。
# 各版は先頭コメントを版の説明に置き換え，書き換えた行のコメントも書き換え後のコードに合わせる
softprac_add_program(Flags flags.c)

set(header "/* 第3回 課題5（発展） 権限フラグ（Flags） */")
set(start_line "    unsigned int flags = 1u;            /* 初期値: 読む権限だけ */")
set(set_line "    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */")
set(clear_line "    flags &= ~read_mask;  /* クリア: 対象ビットだけ0のマスクと AND */")

softprac_add_variant(Flags flags.c start_0
  "${header}"
  "/* 第3回 課題5（発展） ビット列で確かめる: 最初の flags を 0u（権限なし）に書き換えた版 */"
  "${start_line}"
  "    unsigned int flags = 0u;            /* 初期値: 権限なし（000） */")
softprac_add_variant(Flags flags.c start_7
  "${header}"
  "/* 第3回 課題5（発展） ビット列で確かめる: 最初の flags を 7u（3 つの権限すべて）に書き換えた版 */"
  "${start_line}"
  "    unsigned int flags = 7u;            /* 初期値: 3つの権限すべて（111） */")
# 書く権限のセットを 2 行続けて行う（OR 版と，OR の代わりに加算を使う版）
softprac_add_variant(Flags flags.c set_twice_or
  "${header}"
  "/* 第3回 課題5（発展） 説明すること: 書く権限を OR で 2 回続けてセットする版（1 回のときと同じ 3） */"
  "${set_line}"
  "    flags |= write_mask;  /* セット: OR で対象ビットだけ1にする */\n    flags |= write_mask;  /* 2回目: 既に1なので変わらない */")
softprac_add_variant(Flags flags.c set_twice_add
  "${header}"
  "/* 第3回 課題5（発展） 説明すること: 書く権限を OR の代わりに加算で 2 回続けてセットする版（桁上がりして 5 になる） */"
  "${set_line}"
  "    flags += write_mask;  /* 加算でセット: 001 + 010 = 011 */\n    flags += write_mask;  /* 2回目: 011 + 010 = 101 と桁上がりする */")
# 誤りの例（README の採点のポイント）: クリアに論理否定 ! を使う → flags 全体が 0 になる
softprac_add_variant(Flags flags.c wrong_clear_not
  "${header}"
  "/* 第3回 課題5（発展） 誤りの例: 読む権限のクリアに論理否定 ! を使った版（flags 全体が 0 になる） */"
  "${clear_line}"
  "    flags &= !read_mask;  /* 誤りの例: !read_mask は論理否定で 0 なので，flags 全体が 0 になる */")
# 誤りの例: クリアに XOR を使う → 読む権限が 0 のとき（初期値 0u）に逆に 1 になる
softprac_add_variant(Flags flags.c wrong_clear_xor_start_0
  "${header}"
  "/* 第3回 課題5（発展） 誤りの例: 最初の flags を 0u にし，読む権限のクリアに XOR を使った版（逆に 1 になる） */"
  "${start_line}"
  "    unsigned int flags = 0u;            /* 初期値: 権限なし（000） */"
  "${clear_line}"
  "    flags ^= read_mask;   /* 誤りの例: XOR は反転なので，読む権限が 0 だと逆に 1 になる */")

# 説明すること: 1u + 1u と 1u | 1u（README に載せた結果をテストする）
softprac_add_variant(Flags versions/or_vs_add.c or_vs_add)
# 確認問題 7: 4u & 2u と 4u && 2u（README に載せた結果をテストする）
softprac_add_variant(Flags versions/and_vs_logical_and.c and_vs_logical_and)
