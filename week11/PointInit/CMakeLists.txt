# 第11回 発展1 PointInit
# 本体（タグ付きの typedef）に加えて，指定初期化子を名前なしの {2.0, 10.0} に変えた版（宣言順に対応する）と，
# 演習ページの最初の形のタグなしの typedef の版（versions/point_untagged.c。本体と同じ表示）をテストする。
# 各版は先頭コメントの説明の行と書き換えた行のコメントを，その版の内容に合わせて置き換える
softprac_add_program(PointInit point_init.c)

softprac_add_variant(PointInit point_init.c positional
  "// 指定初期化子，省略したメンバ，複合リテラル，構造体を返す関数。Point はタグ付きの typedef で定義する。"
  "// a の初期化を名前を指定しない {2.0, 10.0} に書き換えた版（宣言順に x=2.0, y=10.0 となり，本体とは意味が違う）"
  "    Point a = {.y = 2.0, .x = 10.0}; // 指定した名前どおり x=10.0, y=2.0"
  "    Point a = {2.0, 10.0}; // 名前を指定しないので宣言順に x=2.0, y=10.0")

# タグなしの typedef（変数はすべて Point）でも本体と同じ表示になる
softprac_add_variant(PointInit versions/point_untagged.c untagged)
