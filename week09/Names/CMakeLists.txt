# 第9回 課題2 Names
# フォルダのソースは本体（演習ページの指示をすべて反映した版。swap_names(names, 0, 2); を呼ぶ）。
# 表の他のケースなどは書き換えた版でテストする
#   direct     … 関数へ分ける前の途中版（versions/names_direct.c をそのままビルド。出力が本体と同じことを確かめるケース）
#   swap_1_1   … swap_names(names, 1, 1); にした版
#   swap_twice … swap_names(names, 0, 2); を 2 回呼ぶ版
#   city       … %s-city で表示し，続けて元の文字列と strlen を表示する版（string.h を追加）
#   editable   … 変更可能な配列 city0, city1 の断片を main に追加した版
# 各版は先頭コメント（1〜3 行目）を版の説明に置き換え，書き換えた行のコメントも書き換え後のコードに合わせる。
# 置換前の文字列は行末のコメントまで含めた行全体にする
softprac_add_program(Names names.c)

set(header [=[// 第9回 課題2　表示順を変更する（Names / names.c）
// ポインタ配列の要素（ポインタ値）を交換する。文字列本体はコピーも変更もしない。
// 表の他の呼び出し・-city の表示・変更可能な配列の例は CMakeLists.txt の variant でテストする。]=])
set(call "    swap_names(names, 0, 2);")
set(print [=[        printf("%s\n", names[i]);]=])

softprac_add_variant(Names versions/names_direct.c direct)
softprac_add_variant(Names names.c swap_1_1
  "${header}"
  "// 第9回 課題2　書き換え版 swap_1_1: swap_names(names, 0, 2); を swap_names(names, 1, 1); にした版（Names）\n// 同じ添字どうしの交換なので，names[1] を自分自身と入れ替えるだけで順番は変わらない。"
  "${call}"
  "    swap_names(names, 1, 1);  // 同じ添字: 何も変わらない")
softprac_add_variant(Names names.c swap_twice
  "${header}"
  "// 第9回 課題2　書き換え版 swap_twice: swap_names(names, 0, 2); を 2 回続けて呼ぶ版（Names）\n// 2 回目で元の順番に戻る。文字列本体はコピーも変更もしない。"
  "${call}"
  "    swap_names(names, 0, 2);\n    swap_names(names, 0, 2);  // 2 回目: 元の順番に戻る")
softprac_add_variant(Names names.c city
  "${header}"
  "// 第9回 課題2　書き換え版 city（Names）: strlen を使う版（string.h を追加）\n// 交換後に各文字列を %s-city で表示し，続けて元の文字列と strlen の値を表示する（\"-city\" は表示だけで，文字列本体は変わらない）。"
  "#include <stdio.h>"
  "#include <stdio.h>\n#include <string.h>  // strlen を使うので追加する"
  "${print}"
  [=[        printf("%s-city\n", names[i]);                   // 表示に -city を付けるだけ
        printf("%s %zu\n", names[i], strlen(names[i]));  // 元の文字列と長さは変わらない]=])
softprac_add_variant(Names names.c editable
  "${header}"
  "// 第9回 課題2　書き換え版 editable: main の最後に，変更可能な配列 city0, city1 の断片を追加した版（Names）\n// editable[0] は配列 city0 を指すので，editable[0][0] への代入で city0 が tokyo になる（文字列リテラルは変更しない）。"
  "    return 0;"
  [=[    char city0[] = "Tokyo";  // リテラルの内容で初期化した変更可能な配列
    char city1[] = "Osaka";
    char *editable[] = {city0, city1};
    editable[0][0] = 't';  // city0[0] が変わる
    printf("%s %s\n", city0, editable[0]);
    return 0;]=])
