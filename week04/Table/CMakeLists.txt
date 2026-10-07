# 第4回 課題3 Table
# 本体（3 行 3 列）に加えて，列の上限と列間の判定を 3 から 4 に変えた版（3 行 4 列）と，
# 改行の位置を変えた版・列の上限だけを変えた版（誤りの例）をビルドしてテストする
softprac_add_program(Table table.c)

softprac_add_variant(Table table.c cols_4 "col <= 3" "col <= 4" "col < 3" "col < 4")
softprac_add_variant(Table table.c cols_4_bound_only "col <= 3" "col <= 4")

# 改行を内側のループの本体の最後へ移した版（1 要素ずつ別の行）
softprac_add_variant(Table table.c newline_inner
  [=[            }
        }
        printf("\n");                           // 内側のループが終わった後に 1 回だけ改行する
]=]
  [=[            }
            printf("\n");
        }
]=])

# 改行を外側のループより後へ移した版（全要素が 1 行）
softprac_add_variant(Table table.c newline_after
  [=[        printf("\n");                           // 内側のループが終わった後に 1 回だけ改行する
    }
]=]
  [=[    }
    printf("\n");
]=])
