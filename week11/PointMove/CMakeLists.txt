# 第11回 課題1 PointMove
# 本体（講義の structs.c）に加えて，移動量を変えた版・b.x を変更する版・3 つの呼び出し方の版をビルドしてテストする。
# 各版は先頭コメントの説明の行と書き換えた行のコメントを，その版の内容に合わせて置き換える
softprac_add_program(PointMove structs.c)

set(header [=[// 講義の structs.c。値渡し（moved）とポインタ渡し（move_in_place）で a の変化を比べる。
// 移動量を変えるときは，moved と move_in_place の 2 か所を同じ値に書き換える。]=])
set(call_moved "    Point b = moved(a, 3.0, -1.0);")
set(call_in_place "    move_in_place(&a, 3.0, -1.0);")
# b の宣言から move_in_place の呼び出しまで（3 つの呼び出し方の版はこの 4 行を 1 つの呼び出しに置き換える）
set(calls [=[    // b には a のコピーを移動した値が入り，a は変わらない。move_in_place は a 自体を変える
    Point b = moved(a, 3.0, -1.0);
    printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);
    move_in_place(&a, 3.0, -1.0);]=])

# 移動量を変える（moved と move_in_place の 2 か所を同じ値にする）
softprac_add_variant(PointMove structs.c move_0_0
  "${header}"
  "// moved と move_in_place の移動量を 2 か所とも 0.0, 0.0 に書き換えた版\n// a も b も (1, 2) のままなので，表示だけでは値渡しとポインタ渡しの違いが見えない"
  "${call_moved}" "    Point b = moved(a, 0.0, 0.0);"
  "${call_in_place}" "    move_in_place(&a, 0.0, 0.0);")
softprac_add_variant(PointMove structs.c move_m1_m2
  "${header}"
  "// moved と move_in_place の移動量を 2 か所とも -1.0, -2.0 に書き換えた版\n// b と，move_in_place の後の a はどちらも (0, 0) になる"
  "${call_moved}" "    Point b = moved(a, -1.0, -2.0);"
  "${call_in_place}" "    move_in_place(&a, -1.0, -2.0);")
softprac_add_variant(PointMove structs.c move_2_3
  "${header}"
  "// moved と move_in_place の移動量を 2 か所とも 2.0, 3.0 に書き換えた版\n// b と，move_in_place の後の a はどちらも (3, 5) になる"
  "${call_moved}" "    Point b = moved(a, 2.0, 3.0);"
  "${call_in_place}" "    move_in_place(&a, 2.0, 3.0);")

# 最後に b.x = 100.0; を追加して a と b を表示する（変わるのは b だけ）
softprac_add_variant(PointMove structs.c b_x_100
  "${header}"
  "// move_in_place の後に b.x = 100.0; を追加し，a と b を表示する行を足した版\n// a と b は別の保存場所なので，変わるのは b だけ"
  [=[    printf("a=(%.1f, %.1f)\n", a.x, a.y);]=]
  [=[    printf("a=(%.1f, %.1f)\n", a.x, a.y);
    b.x = 100.0; // b だけを変える。a は別の保存場所なので変わらない
    printf("a=(%.1f, %.1f) b=(%.1f, %.1f)\n", a.x, a.y, b.x, b.y);]=])

# 3 つの呼び出し方をそれぞれ独立に試す（b の宣言と表示，もう一方の呼び出しは削除）
softprac_add_variant(PointMove structs.c call_discard
  "${header}"
  "// 3 つの呼び出し方（1）: a を (1, 2) で初期化した直後に moved(a, 3.0, -1.0); だけを呼び，戻り値を受け取らない版\n// move_in_place の呼び出しと b は削除した。関数内で変わるのはコピーの p だけなので a は (1, 2) のまま"
  "${calls}"
  [=[    // 戻り値を受け取らないので a は変わらない（関数内で変わったのはコピーの p だけ）
    moved(a, 3.0, -1.0);]=])
softprac_add_variant(PointMove structs.c call_assign
  "${header}"
  "// 3 つの呼び出し方（2）: a を (1, 2) で初期化した直後に a = moved(a, 3.0, -1.0); だけを呼ぶ版\n// move_in_place の呼び出しと b は削除した。移動したコピーを戻り値で受け取って a へ代入するので a は (4, 1)"
  "${calls}"
  [=[    // 移動したコピーを戻り値で受け取り，a へ代入する
    a = moved(a, 3.0, -1.0);]=])
softprac_add_variant(PointMove structs.c call_in_place
  "${header}"
  "// 3 つの呼び出し方（3）: a を (1, 2) で初期化した直後に move_in_place(&a, 3.0, -1.0); だけを呼ぶ版\n// moved の呼び出しと b は削除した。a のアドレスを渡し，その先の a 本体を変えるので a は (4, 1)"
  "${calls}"
  [=[    // a のアドレスを渡し，a 自体を変える
    move_in_place(&a, 3.0, -1.0);]=])
