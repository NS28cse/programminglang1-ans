# 第13回 課題3 NewPoint
# 本体（(3.0, 4.0) を生成）に加えて，「値を (0,0)，(-2,5) へ変更して」の版をビルドしてテストする
softprac_add_program(NewPoint new_point.c)

softprac_add_variant(NewPoint new_point.c point_0_0 "new_point(3.0, 4.0)" "new_point(0.0, 0.0)")
softprac_add_variant(NewPoint new_point.c point_m2_5 "new_point(3.0, 4.0)" "new_point(-2.0, 5.0)")
# 複合リテラルに置き換える前の 2 文の版（同じ出力になることを確かめる）
softprac_add_variant(NewPoint new_point.c two_statements
  "    *p = (Point){.x = x, .y = y};   // 左辺は p ではなく本体の *p"
  "    p->x = x;\n    p->y = y;")
# 課題3「戻り方を比較する」：3 つの方法を並べた比較用の別ソース（置換なしでそのままビルドする）
softprac_add_variant(NewPoint versions/return_styles.c return_styles)
