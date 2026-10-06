# 第11回 課題4 CopyMembers
# 本体に加えて，先頭 1 文字ではなく文字列全体を "fuga" へ置き換える版をテストする
softprac_add_program(CopyMembers copy_members.c)

softprac_add_variant(CopyMembers copy_members.c replace_fuga
  "a1.text[0] = 'H';"
  [=[const char replacement[] = "fuga";
    for (size_t i = 0; i < sizeof replacement; ++i) {
        a1.text[i] = replacement[i];
    }]=]
  "p1.text[0] = 'H';"
  [=[for (size_t i = 0; i < sizeof replacement; ++i) {
        buffer[i] = replacement[i];
    }]=])
