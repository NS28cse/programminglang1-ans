# 第6回 発展 CopyCapacity（講義の strings.c）
# 本体は講義の strings.c そのもの（copy の容量16）。演習ページの「copy の容量を4，3に変更」した版をビルドしてテストする
softprac_add_program(CopyCapacity strings.c)

softprac_add_variant(CopyCapacity strings.c capacity_4 "char copy[16]" "char copy[4]"
                     [[講義の strings.c そのもの]] [[講義の strings.c で copy の容量を 4 に変えた版]])
softprac_add_variant(CopyCapacity strings.c capacity_3 "char copy[16]" "char copy[3]"
                     [[講義の strings.c そのもの]] [[講義の strings.c で copy の容量を 3 に変えた版]])
