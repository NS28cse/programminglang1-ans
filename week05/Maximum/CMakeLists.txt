# 第5回 課題1 Maximum
# 本体に加えて，「異なる配列で確かめる」の表の 4 つの配列（COUNT と初期化子を書き換えた版）をビルドしてテストする
softprac_add_program(Maximum maximum.c)

softprac_add_variant(Maximum maximum.c zero  "COUNT = 5" "COUNT = 1" "{72, 85, 60, 93, 80}" "{0}")
softprac_add_variant(Maximum maximum.c same  "COUNT = 5" "COUNT = 3" "{72, 85, 60, 93, 80}" "{60, 60, 60}")
softprac_add_variant(Maximum maximum.c first "COUNT = 5" "COUNT = 3" "{72, 85, 60, 93, 80}" "{100, 20, 30}")
softprac_add_variant(Maximum maximum.c last  "COUNT = 5" "COUNT = 3" "{72, 85, 60, 93, 80}" "{20, 30, 100}")
