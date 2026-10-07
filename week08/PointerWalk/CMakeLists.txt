# 第8回 課題4 PointerWalk
# フォルダのソースは演習ページの期待する表示（3 行）を出す最終版。各確認は一部を書き換えた版としてテストする
#   reverse_diff                  … q - p を p - q に変える（-2）
#   q_a1                          … q を a + 1 へ変える（差 0，p < q は偽，p == q は真）
#   zeros / ascending             … 配列を {0, 0, 0, 0, 0}，{1, 2, 3, 4, 5} へ変える
#   length_empty / _A / _Hello    … pointer_length の入力を ""，"A"，"Hello" へ変える
#   set_one_first                 … 合計する前に set_one(a, COUNT); を呼ぶ（合計 5）
#   set_one_first_array_param     … さらに set_one の仮引数を int a[] にする（同じ結果）
#   inline                        … versions/ の，講義と同じく main の中でループを書いた版（置換なし）
softprac_add_program(PointerWalk pointer_walk.c)

set(array_line "    int a[COUNT] = {2, 4, 6, 3, 5};")

softprac_add_variant(PointerWalk pointer_walk.c reverse_diff "q - p," "p - q,")
softprac_add_variant(PointerWalk pointer_walk.c q_a1 "int *q = a + 3" "int *q = a + 1")
softprac_add_variant(PointerWalk pointer_walk.c zeros "{2, 4, 6, 3, 5}" "{0, 0, 0, 0, 0}")
softprac_add_variant(PointerWalk pointer_walk.c ascending "{2, 4, 6, 3, 5}" "{1, 2, 3, 4, 5}")
softprac_add_variant(PointerWalk pointer_walk.c length_empty [=[pointer_length("cat")]=] [=[pointer_length("")]=])
softprac_add_variant(PointerWalk pointer_walk.c length_A [=[pointer_length("cat")]=] [=[pointer_length("A")]=])
softprac_add_variant(PointerWalk pointer_walk.c length_Hello [=[pointer_length("cat")]=] [=[pointer_length("Hello")]=])
softprac_add_variant(PointerWalk pointer_walk.c set_one_first
  "${array_line}" "${array_line}
    set_one(a, COUNT);")
softprac_add_variant(PointerWalk pointer_walk.c set_one_first_array_param
  "${array_line}" "${array_line}
    set_one(a, COUNT);"
  "void set_one(int *a, int n)" "void set_one(int a[], int n)")
softprac_add_variant(PointerWalk versions/pointer_walk_inline.c inline)
