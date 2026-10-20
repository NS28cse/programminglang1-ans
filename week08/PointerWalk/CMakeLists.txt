# 第8回 課題4 PointerWalk
# 本体は演習ページの期待する表示（3 行）を出す版（set_one は定義だけ）。各確認は一部を書き換えた版としてテストする
#   reverse_diff                  … q - p を p - q に変える（-2）
#   q_a1                          … q を a + 1 へ変える（差 0，p < q は偽，p == q は真）
#   zeros / ascending             … 配列を {0, 0, 0, 0, 0}，{1, 2, 3, 4, 5} へ変える
#   length_empty / _A / _Hello    … pointer_length の入力を ""，"A"，"Hello" へ変える
#   set_one_first                 … 合計する前に set_one(a, COUNT); を呼ぶ（合計 5）
#   inline                        … versions/ の，講義と同じ書き方の版（main の中でループ，set_one の仮引数は int a[]。置換なし）
#   post_increment                … versions/ の，確認問題4（(*p)++ と *p++）の確かめ（置換なし）
softprac_add_program(PointerWalk pointer_walk.c)

# 本体の先頭コメントの最後の行。書き換えた版ではこれを版の説明に置き換える
set(head [=[ * set_one は講義のとおり main より前に定義している（期待する表示を保つため，main からは呼ばない）．]=])
set(array_line "    int a[COUNT] = {2, 4, 6, 3, 5};")

softprac_add_variant(PointerWalk pointer_walk.c reverse_diff
  "${head}" " * 差を p - q に変えた版（向きが逆なので -2）．"
  "q - p," "p - q,")
softprac_add_variant(PointerWalk pointer_walk.c q_a1
  "${head}" " * q を a + 1 へ変えた版（p と同じ要素を指すので差 0，p < q は偽，p == q は真）．"
  "int *q = a + 3" "int *q = a + 1")
softprac_add_variant(PointerWalk pointer_walk.c zeros
  "${head}" " * 配列を {0, 0, 0, 0, 0} へ変えた版（合計 0）．"
  "{2, 4, 6, 3, 5}" "{0, 0, 0, 0, 0}")
softprac_add_variant(PointerWalk pointer_walk.c ascending
  "${head}" " * 配列を {1, 2, 3, 4, 5} へ変えた版（合計 15）．"
  "{2, 4, 6, 3, 5}" "{1, 2, 3, 4, 5}")
foreach(spec "length_empty;;0" "length_A;A;1" "length_Hello;Hello;5")
  list(GET spec 0 tag)
  list(GET spec 1 text)
  list(GET spec 2 count)
  softprac_add_variant(PointerWalk pointer_walk.c ${tag}
    "${head}" " * pointer_length の入力を \"${text}\" へ変えた版（s は ${count} 回進む）．"
    [=[pointer_length("cat")]=] "pointer_length(\"${text}\")")
endforeach()
softprac_add_variant(PointerWalk pointer_walk.c set_one_first
  "${head}" [=[ * 演習ページの指示どおり，合計する前に set_one(a, COUNT); を呼ぶ版．
 * 元の配列の全要素が 1 になるので，添字版・ポインタ版とも合計は 5 になる．]=]
  "${array_line}" "${array_line}
    set_one(a, COUNT);")
softprac_add_variant(PointerWalk versions/pointer_walk_inline.c inline)
softprac_add_variant(PointerWalk versions/post_increment.c post_increment)
