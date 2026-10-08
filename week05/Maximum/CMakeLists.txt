# 第5回 課題1 Maximum
# 本体に加えて，「異なる配列で確かめる」の表の 4 つの配列（COUNT と初期化子を書き換えた版）と，
# return をループの中へ移した誤りの版をビルドしてテストする。各版は先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(Maximum maximum.c)

softprac_add_variant(Maximum maximum.c zero
  "// 配列の最大値を返す関数 max_score を作り，main で戻り値を表示する。"
  "// 「異なる配列で確かめる」の表の {0}，n = 1 に書き換えた版（本体を 0 回で終え，max=0）。"
  "COUNT = 5" "COUNT = 1" "{72, 85, 60, 93, 80}" "{0}")

softprac_add_variant(Maximum maximum.c same
  "// 配列の最大値を返す関数 max_score を作り，main で戻り値を表示する。"
  "// 「異なる配列で確かめる」の表の {60, 60, 60}，n = 3 に書き換えた版（等しい値で候補が変わらず，max=60）。"
  "COUNT = 5" "COUNT = 3" "{72, 85, 60, 93, 80}" "{60, 60, 60}")

softprac_add_variant(Maximum maximum.c first
  "// 配列の最大値を返す関数 max_score を作り，main で戻り値を表示する。"
  "// 「異なる配列で確かめる」の表の {100, 20, 30}，n = 3 に書き換えた版（最初が最大，max=100）。"
  "COUNT = 5" "COUNT = 3" "{72, 85, 60, 93, 80}" "{100, 20, 30}")

softprac_add_variant(Maximum maximum.c last
  "// 配列の最大値を返す関数 max_score を作り，main で戻り値を表示する。"
  "// 「異なる配列で確かめる」の表の {20, 30, 100}，n = 3 に書き換えた版（最後が最大，max=100）。"
  "COUNT = 5" "COUNT = 3" "{72, 85, 60, 93, 80}" "{20, 30, 100}")

# 誤りの例: return best; をループの中へ移した版（i = 1 だけ調べて max=85）。
# ループを抜けて関数の終わりに達する経路（n が 1 以下）ができるのでコンパイラが警告する（GCC/Clang -Wreturn-type，MSVC は例: C4715）。
# この版の入力は n = 5 で，i = 1 の繰り返しの中で必ず return するため，その経路は通らない（未定義動作にならない）。
# 誤りを示すための版なので，この版だけその警告を抑止する。
softprac_add_variant(Maximum maximum.c return_in_loop
  "// 配列の最大値を返す関数 max_score を作り，main で戻り値を表示する。"
  "// 誤りの例: return best; をループの中へ移した版（i = 1 だけ調べて max=85 になる）。\n// n = 5 なので必ずループ内で返り，値を返さずに関数の終わりに達する経路は通らない。"
  [=[        }
    }
    return best;  // 全要素を調べ終えてから返す]=]
  [=[        }
        return best;  // 誤り: 最初の比較の後で返してしまう
    }]=])
# MSVC は値を返さない経路の警告（番号は Microsoft Learn の説明に基づく例: C4715）に加えて，
# C4702（ループの ++i に到達しない）も出す。C4702 は CI（コミット 25e4f69 の実行）で MSVC 19.51 が実際に出した。両方抑止する
target_compile_options(Maximum_return_in_loop PRIVATE $<IF:$<C_COMPILER_ID:MSVC>,/wd4715,-Wno-return-type> $<$<C_COMPILER_ID:MSVC>:/wd4702>)
