# 第11回 発展1 PointInit
# 本体（タグ付きの typedef）に加えて，指定初期化子を名前なしの {2.0, 10.0} に変えた版（宣言順に対応する）と，
# 書き換え前のタグなしの typedef の版（versions/point_untagged.c。本体と同じ表示）をテストする。
# 版は先頭コメントを版の説明に置き換え，書き換えた行のコメントも書き換え後のコードに合わせる。
# 置換前の文字列は行末のコメントまで含めた行全体にする
softprac_add_program(PointInit point_init.c)

softprac_add_variant(PointInit point_init.c positional
  "// 第11回 発展1: 指定初期化子，省略したメンバ，複合リテラル，構造体を返す関数"
  "// 第11回 発展1: a の初期化を名前を指定しない {2.0, 10.0} に書き換えた版（宣言順に x=2.0, y=10.0 となり，本体とは意味が違う）"
  "    Point a = {.y = 2.0, .x = 10.0}; // 指定した名前どおり x=10.0, y=2.0"
  "    Point a = {2.0, 10.0}; // 名前を指定しないので宣言順に x=2.0, y=10.0")

# 書き換え前（タグなしの typedef。変数はすべて Point）でも本体と同じ表示になる
softprac_add_variant(PointInit versions/point_untagged.c untagged)
