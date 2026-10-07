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

# 回数の確認: 外側・内側の条件判定（test）と本体（body），区切りの空白（space）の回数を数えて最後に表示する版
# （確認用。判定のたびに数えるため，継続条件の前にコンマ演算子で ++outer_test などを入れている）
foreach(cols 3 4)
  softprac_add_variant(Table table.c count_cols_${cols}
    "    for (int row = 1; row <= 3; ++row) {"
    "    int outer_test = 0;\n    int outer_body = 0;\n    int inner_test = 0;\n    int inner_body = 0;\n    int space = 0;\n    for (int row = 1; ++outer_test, row <= 3; ++row) {\n        ++outer_body;"
    "for (int col = 1; col <= 3; ++col) {" "for (int col = 1; ++inner_test, col <= ${cols}; ++col) {\n            ++inner_body;"
    "if (col < 3) {" "if (col < ${cols}) {\n                ++space;"
    "    return 0;"
    "    printf(\"outer: test=%d body=%d\\n\", outer_test, outer_body);\n    printf(\"inner: test=%d body=%d space=%d\\n\", inner_test, inner_body, space);\n    return 0;")
endforeach()

# 9 組の (row, col) を実行順に書き出す版（内側の表示を組にし，区切りと行末の改行をなくす）
softprac_add_variant(Table table.c pairs
  [=[            printf("%2d", row * col);
            if (col < 3) {                      // 列の間だけ区切りを入れ，行末には付けない
                printf(" ");
            }
        }
        printf("\n");                           // 内側のループが終わった後に 1 回だけ改行する
]=]
  [=[            printf("(%d, %d)\n", row, col);
        }
]=])

# 確認問題6: 3 行 4 列で，内側が毎回 1 回目に break する版（内側・外側の本体の回数を表示する）
softprac_add_variant(Table table.c break_first_cols_4
  "    for (int row = 1; row <= 3; ++row) {"
  "    int outer_body = 0;\n    int inner_body = 0;\n    for (int row = 1; row <= 3; ++row) {\n        ++outer_body;"
  "for (int col = 1; col <= 3; ++col) {" "for (int col = 1; col <= 4; ++col) {\n            ++inner_body;\n            if (col == 1) {\n                break;\n            }"
  "if (col < 3) {" "if (col < 4) {"
  "    return 0;"
  "    printf(\"outer body=%d inner body=%d\\n\", outer_body, inner_body);\n    return 0;")
