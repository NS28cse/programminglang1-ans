# 第13回 課題3 NewPoint
# 本体は (3.0, 4.0) を生成する。「値を (0,0)，(-2,5) へ変更して」の版などをテストする
softprac_add_program(NewPoint new_point.c)

softprac_add_variant(NewPoint new_point.c point_0_0
  "// main は NULL を検査し，成功時だけ両メンバを表示してから解放する。"
  "// new_point(0.0, 0.0) に書き換えた版。"
  "new_point(3.0, 4.0)" "new_point(0.0, 0.0)")
softprac_add_variant(NewPoint new_point.c point_m2_5
  "// main は NULL を検査し，成功時だけ両メンバを表示してから解放する。"
  "// new_point(-2.0, 5.0) に書き換えた版。"
  "new_point(3.0, 4.0)" "new_point(-2.0, 5.0)")
# 複合リテラルの代わりに 2 文で初期化する版（同じ出力になる）
softprac_add_variant(NewPoint new_point.c two_statements
  "// main は NULL を検査し，成功時だけ両メンバを表示してから解放する。"
  "// 複合リテラルの代わりに p->x = x; p->y = y; の 2 文で初期化する版（表示は同じ）。"
  "    *p = (Point){.x = x, .y = y};   // 左辺は p ではなく本体の *p"
  "    p->x = x;\n    p->y = y;")
# 課題3「戻り方を比較する」：3 つの方法を並べた比較用の別ソース（置換なし）
softprac_add_variant(NewPoint versions/return_styles.c return_styles)
