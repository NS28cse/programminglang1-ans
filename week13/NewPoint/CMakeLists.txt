# 第13回 課題3 NewPoint
# 本体（(3.0, 4.0) を生成）に加えて，「値を (0,0)，(-2,5) へ変更して」の版をビルドしてテストする
softprac_add_program(NewPoint new_point.c)

softprac_add_variant(NewPoint new_point.c point_0_0 "new_point(3.0, 4.0)" "new_point(0.0, 0.0)")
softprac_add_variant(NewPoint new_point.c point_m2_5 "new_point(3.0, 4.0)" "new_point(-2.0, 5.0)")
