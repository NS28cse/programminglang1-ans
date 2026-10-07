# 第13回 発展2 StorageCount
# 本体（static int count = 0;）に加えて，「3 種類を比較する」の残り 2 つの書き方をビルドしてテストする
softprac_add_program(StorageCount count.c)

# static を外した通常の局所変数（自動記憶域）
softprac_add_variant(StorageCount count.c auto_count "static int count = 0;" "int count = 0;")
# static int count; の後に，文として count = 0; を書く（呼ぶたびに代入される）
softprac_add_variant(StorageCount count.c static_assign
  "static int count = 0;   // この static は静的記憶期間（名前は関数内だけで使える）"
  "static int count;\n    count = 0;")
