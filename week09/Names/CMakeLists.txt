# 第9回 課題2 Names
# フォルダのソースは swap_names(names, 0, 2); を呼ぶ最終版。表の他のケースなどは書き換えた版でテストする
#   direct     … 関数へ分ける前の途中版（versions/names_direct.c をそのままビルド。出力が本体と同じことを確かめるケース）
#   swap_1_1   … swap_names(names, 1, 1); にした版
#   swap_twice … swap_names(names, 0, 2); を 2 回呼ぶ版
#   city       … %s-city で表示し，続けて元の文字列と strlen を表示する版
#   editable   … 変更可能な配列 city0, city1 の断片を main に追加した版
softprac_add_program(Names names.c)

set(call "    swap_names(names, 0, 2);")
set(print [=[        printf("%s\n", names[i]);]=])

softprac_add_variant(Names versions/names_direct.c direct)
softprac_add_variant(Names names.c swap_1_1 "${call}" "    swap_names(names, 1, 1);")
softprac_add_variant(Names names.c swap_twice "${call}" "${call}
${call}")
softprac_add_variant(Names names.c city "#include <stdio.h>" "#include <stdio.h>
#include <string.h>" "${print}" [=[        printf("%s-city\n", names[i]);
        printf("%s %zu\n", names[i], strlen(names[i]));]=])
softprac_add_variant(Names names.c editable "    return 0;" [=[    char city0[] = "Tokyo";
    char city1[] = "Osaka";
    char *editable[] = {city0, city1};
    editable[0][0] = 't';
    printf("%s %s\n", city0, editable[0]);
    return 0;]=])
