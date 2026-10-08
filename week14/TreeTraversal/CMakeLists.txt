# 第14回 発展2 TreeTraversal
# 本体に加えて，「小さい木で基底条件を確認する」（main の preorder の引数だけを変える）版と，
# 「木の形を変える」（右へ一直線の 10 ノードの木）版をビルドしてテストする
softprac_add_program(TreeTraversal tree.c)

softprac_add_variant(TreeTraversal tree.c start_null
  [=[ * 講義の tree.c に，ノード数を返す node_count と高さを返す tree_height を追加した版。]=]
  [=[ * 書き換え版: main の preorder の開始位置を NULL にした版（「小さい木で基底条件を確認する」）。]=]
  "    preorder(&nodes[0]);" [=[    preorder(NULL);                  /* 書き換え版: 開始位置だけを変えた */]=])
softprac_add_variant(TreeTraversal tree.c start_nodes3
  [=[ * 講義の tree.c に，ノード数を返す node_count と高さを返す tree_height を追加した版。]=]
  [=[ * 書き換え版: main の preorder の開始位置を nodes[3]（葉） にした版（「小さい木で基底条件を確認する」）。]=]
  "    preorder(&nodes[0]);" [=[    preorder(&nodes[3]);                  /* 書き換え版: 開始位置だけを変えた */]=])
softprac_add_variant(TreeTraversal tree.c start_nodes2
  [=[ * 講義の tree.c に，ノード数を返す node_count と高さを返す tree_height を追加した版。]=]
  [=[ * 書き換え版: main の preorder の開始位置を nodes[2]（3 4 5 の部分木） にした版（「小さい木で基底条件を確認する」）。]=]
  "    preorder(&nodes[0]);" [=[    preorder(&nodes[2]);                  /* 書き換え版: 開始位置だけを変えた */]=])
softprac_add_variant(TreeTraversal tree.c start_nodes6
  [=[ * 講義の tree.c に，ノード数を返す node_count と高さを返す tree_height を追加した版。]=]
  [=[ * 書き換え版: main の preorder の開始位置を nodes[6]（7 8 9 10 の部分木） にした版（「小さい木で基底条件を確認する」）。]=]
  "    preorder(&nodes[0]);" [=[    preorder(&nodes[6]);                  /* 書き換え版: 開始位置だけを変えた */]=])

# ノードをつなぐ代入文をすべて外し，0〜8 の各 i について nodes[i].right = &nodes[i + 1]; だけを設定する
softprac_add_variant(TreeTraversal tree.c line
  [=[ * 講義の tree.c に，ノード数を返す node_count と高さを返す tree_height を追加した版。]=]
  [=[ * 書き換え版: ノードをつなぐ代入文を外し，右へ一直線の 10 ノードの木にした版（「木の形を変える」）。]=]
  [=[    nodes[0].left = &nodes[1];  nodes[0].right = &nodes[6];
    nodes[1].left = &nodes[2];  nodes[1].right = &nodes[5];
    nodes[2].left = &nodes[3];  nodes[2].right = &nodes[4];
    nodes[6].left = &nodes[7];  nodes[6].right = &nodes[9];
    nodes[7].left = &nodes[8];
]=]
  [=[    /* 書き換え版: 右へ一直線の 10 ノードの木（nodes[9].right は NULL のまま） */
    for (int i = 0; i < 9; ++i) {
        nodes[i].right = &nodes[i + 1];
    }
]=]
  "/* 全体（nodes[0]）・葉（nodes[3]）・NULL で検証する */"
  "/* 一直線の木では nodes[3]（値 4）は葉ではなく，4〜10 の部分木の根 */")

# 確認用: 元の木と一直線の木で，行きがけ順の走査の呼び出し回数と最大深さを数える
softprac_add_variant(TreeTraversal versions/traversal_depth.c depth)

# 発展3 の参考: 個別に malloc した木を destroy_tree で帰りがけ順に解放する（LeakSanitizer でリークがないことも確かめる）
softprac_add_variant(TreeTraversal versions/destroy_tree.c destroy)
