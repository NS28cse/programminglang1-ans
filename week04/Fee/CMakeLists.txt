# 第4回 課題1 Fee
# 本体（age = 17）に加えて，演習ページの表の age（-1, 0, 5, 6, 18）に変えた版と，
# 「条件の順序を確かめる」「別々の if にする」「負の年齢の検査を省く」の書き換え版を，表の 6 つの age でビルドしてテストする
softprac_add_program(Fee fee.c)

foreach(age m1 0 5 6 18)
  string(REPLACE "m" "-" value "${age}")
  softprac_add_variant(Fee fee.c age_${age} "age = 17" "age = ${value}")
endforeach()

# age <= 17 を age <= 5 より前に置いた版（0〜5 でも 500 になる）
foreach(age m1 0 5 6 17 18)
  string(REPLACE "m" "-" value "${age}")
  softprac_add_variant(Fee fee.c swapped_age_${age}
    [=[    } else if (age <= 5) {      // 0〜5 歳
        printf("0\n");
    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）
        printf("500\n");]=]
    [=[    } else if (age <= 17) {
        printf("500\n");
    } else if (age <= 5) {
        printf("0\n");]=]
    "int age = 17;" "int age = ${value};")
endforeach()

# else if を別々の if にした版（-1 では 3 つ，0〜5 では 2 つの条件が真になり，複数行表示する）
foreach(age m1 0 5 6 17 18)
  string(REPLACE "m" "-" value "${age}")
  softprac_add_variant(Fee fee.c separate_if_age_${age}
    "} else if (age <= 5)" [=[}
    if (age <= 5)]=]
    "} else if (age <= 17)" [=[}
    if (age <= 17)]=]
    "int age = 17;" "int age = ${value};")
endforeach()

# 負の年齢の検査を省いた版（-1 は age <= 5 が真になり 0 の区分に入る）
softprac_add_variant(Fee fee.c no_check_age_m1
  [=[    if (age < 0) {
        printf("invalid\n");
    } else if (age <= 5) {]=]
  [=[    if (age <= 5) {]=]
  "age = 17" "age = -1")
