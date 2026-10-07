# 第4回 課題1 Fee
# 本体（age = 17）に加えて，演習ページの表の age（-1, 0, 5, 6, 18）に変えた版と，
# 「条件の順序を確かめる」「別々の if にする」「負の年齢の検査を省く」の書き換え版をビルドしてテストする
softprac_add_program(Fee fee.c)

softprac_add_variant(Fee fee.c age_m1 "age = 17" "age = -1")
softprac_add_variant(Fee fee.c age_0  "age = 17" "age = 0")
softprac_add_variant(Fee fee.c age_5  "age = 17" "age = 5")
softprac_add_variant(Fee fee.c age_6  "age = 17" "age = 6")
softprac_add_variant(Fee fee.c age_18 "age = 17" "age = 18")

# age <= 17 を age <= 5 より前に置いた版（age = 5 でも 500 になる）
softprac_add_variant(Fee fee.c swapped_age_5
  [=[    } else if (age <= 5) {      // 0〜5 歳
        printf("0\n");
    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）
        printf("500\n");]=]
  [=[    } else if (age <= 17) {
        printf("500\n");
    } else if (age <= 5) {
        printf("0\n");]=]
  "age = 17" "age = 5")

# else if を別々の if にした版（-1 では 3 つの条件がすべて真になり 3 行表示する）
softprac_add_variant(Fee fee.c separate_if_age_m1
  "} else if (age <= 5)" [=[}
    if (age <= 5)]=]
  "} else if (age <= 17)" [=[}
    if (age <= 17)]=]
  "age = 17" "age = -1")
softprac_add_variant(Fee fee.c separate_if_age_0
  "} else if (age <= 5)" [=[}
    if (age <= 5)]=]
  "} else if (age <= 17)" [=[}
    if (age <= 17)]=]
  "age = 17" "age = 0")

# 負の年齢の検査を省いた版（-1 は age <= 5 が真になり 0 の区分に入る）
softprac_add_variant(Fee fee.c no_check_age_m1
  [=[    if (age < 0) {
        printf("invalid\n");
    } else if (age <= 5) {]=]
  [=[    if (age <= 5) {]=]
  "age = 17" "age = -1")
