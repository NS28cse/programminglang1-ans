# 第4回 課題3 Table
# 本体（3 行 3 列）に加えて，列の上限と列間の判定を 3 から 4 に変えた版（3 行 4 列）をビルドしてテストする
softprac_add_program(Table table.c)

softprac_add_variant(Table table.c cols_4 "col <= 3" "col <= 4" "col < 3" "col < 4")
