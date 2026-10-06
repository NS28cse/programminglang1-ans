# 第8回 課題3 CopyText
# 本体（ポインタを進める while 版）に加えて，コピーを短い表記
#   while ((*dst++ = *src++) != '\0') { }
# に書き換えた版が，表のすべてのケースで同じ結果になることをテストする
softprac_add_program(CopyText copy_text.c)

softprac_add_variant(CopyText copy_text.c short_form
                     "(*dst = *src)" "(*dst++ = *src++)"
                     "++dst" "/* 短い表記では条件式の中で進める */"
                     "++src" "/* 同上 */")
