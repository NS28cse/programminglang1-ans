# 第4回 課題3 Table
# 本体（3 行 3 列）に加えて，列の上限と列間の判定を 3 から 4 に変えた版（3 行 4 列）と，
# 改行の位置を変えた版・列の上限だけを変えた版（誤りの例）などをビルドしてテストする。
# 各版は先頭コメントの 2 行目（table_head）を版の説明に置き換える
softprac_add_program(Table table.c)

set(table_head "// 外側の for を行 row，内側の for を列 col として 1〜3 の掛け算表を表示する．")
# 行末のコメントまで含めた 1 行全体（置換でコメントが別の行に付かないように，行ごと置き換える）
set(row_line "    for (int row = 1; row <= 3; ++row) {\n")
set(col_line "        for (int col = 1; col <= 3; ++col) {   // 行が変わるたびに col は 1 から始まる\n")
set(space_line "            if (col < 3) {                      // 列の間だけ区切りを入れ，行末には付けない\n")

# （見出しの説明に col <= 3 などを含むので，見出しは最後に置き換える）
softprac_add_variant(Table table.c cols_4
  "col <= 3" "col <= 4" "col < 3" "col < 4"
  "${table_head}" "// 列の上限 col <= 3 と列間の判定 col < 3 を 4 に変えた版（3 行 4 列の掛け算表を表示する）．")
softprac_add_variant(Table table.c cols_4_bound_only
  "col <= 3" "col <= 4"
  "${table_head}" "// 列の上限だけを 4 にして列間の判定 col < 3 を変え忘れた版（誤りの例。3 列目と 4 列目の間の区切りがなくなる）．")

# 改行を内側のループの本体の最後へ移した版（1 要素ずつ別の行）
softprac_add_variant(Table table.c newline_inner
  "${table_head}" "// 改行を内側のループの本体の最後へ移した版（1 要素ずつ別の行になる）．"
  [=[            }
        }
        printf("\n");                           // 内側のループが終わった後に 1 回だけ改行する
]=]
  [=[            }
            printf("\n");                       // 内側の本体の最後へ移したので，要素ごとに改行する
        }
]=])

# 改行を外側のループより後へ移した版（全要素が 1 行）
softprac_add_variant(Table table.c newline_after
  "${table_head}" "// 改行を外側のループより後へ移した版（全要素が 1 行に並ぶ）．"
  [=[        printf("\n");                           // 内側のループが終わった後に 1 回だけ改行する
    }
]=]
  [=[    }
    printf("\n");                               // 外側のループの後へ移したので，全体で 1 回だけ改行する
]=])

# 回数の確認: 外側・内側の条件判定（test）と本体（body），区切りの空白（space）の回数を数えて最後に表示する版
# （確認用。判定のたびに数えるため，継続条件の前にコンマ演算子で ++outer_test などを入れている）
set(count_decl [=[    int outer_test = 0;     // 外側の条件判定の回数
    int outer_body = 0;     // 外側の本体の回数
    int inner_test = 0;     // 内側の条件判定の回数
    int inner_body = 0;     // 内側の本体の回数
    int space = 0;          // 区切りの空白の回数
]=])
set(count_print [=[    printf("outer: test=%d body=%d\n", outer_test, outer_body);
    printf("inner: test=%d body=%d space=%d\n", inner_test, inner_body, space);
    return 0;]=])
foreach(cols 3 4)
  softprac_add_variant(Table table.c count_cols_${cols}
    "${table_head}" "// 外側・内側の条件判定（test）と本体（body），区切りの空白（space）の回数を数えて最後に表示する版（確認用．3 行 ${cols} 列）．"
    "${row_line}"
    "${count_decl}    for (int row = 1; ++outer_test, row <= 3; ++row) {\n        ++outer_body;\n"
    "${col_line}"
    "        for (int col = 1; ++inner_test, col <= ${cols}; ++col) {   // 行が変わるたびに col は 1 から始まる\n            ++inner_body;\n"
    "${space_line}"
    "            if (col < ${cols}) {                      // 列の間だけ区切りを入れ，行末には付けない\n                ++space;\n"
    "    return 0;" "${count_print}")
endforeach()

# 9 組の (row, col) を実行順に書き出す版（内側の表示を組にし，区切りと行末の改行をなくす）
softprac_add_variant(Table table.c pairs
  "${table_head}" "// 内側の表示を (row, col) の組にし，区切りと行末の改行をなくして，9 組を実行順に 1 行ずつ書き出す版（確認用）．"
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

# 誤りの例: 内側のカウンタ col を外側のループの前で 1 回だけ初期化し，内側を while にした版
# （1 行目で col が 4 になったまま戻らないので，2・3 行目は内側の本体を 1 回も実行せず空行になる）
softprac_add_variant(Table table.c col_not_reset
  "${table_head}" "// 内側のカウンタ col を外側のループの前で 1 回だけ初期化し，内側を while にした版（誤りの例。2・3 行目が空行になる）．"
  "${row_line}"
  "    int col = 1;                                // 誤り: 外側のループの前で 1 回だけ初期化する\n${row_line}"
  "${col_line}"
  "        while (col <= 3) {                      // 行が変わっても col は 1 に戻らない\n"
  [=[                printf(" ");
            }
]=]
  [=[                printf(" ");
            }
            ++col;
]=])

# 確認問題6: 3 行 4 列で，内側が毎回 1 回目に break する版（内側・外側の本体の回数を表示する）
softprac_add_variant(Table table.c break_first_cols_4
  "${table_head}" "// 確認問題6: 3 行 4 列で，内側が毎回 1 回目に break する版（数値は表示されず，内側・外側の本体の回数を表示する）．"
  "${row_line}"
  "    int outer_body = 0;     // 外側の本体の回数\n    int inner_body = 0;     // 内側の本体の回数\n${row_line}        ++outer_body;\n"
  "${col_line}"
  "        for (int col = 1; col <= 4; ++col) {   // 行が変わるたびに col は 1 から始まる\n            ++inner_body;\n            if (col == 1) {                     // 毎回 1 回目に内側のループだけを抜ける\n                break;\n            }\n"
  "if (col < 3) {" "if (col < 4) {"
  "    return 0;"
  "    printf(\"outer body=%d inner body=%d\\n\", outer_body, inner_body);\n    return 0;")
