# 第12回 発展3 LibraryCheck: ソースは library_check.c だけ（自作の calc.c などは入れない）
softprac_add_program(LibraryCheck library_check.c)

# 追加の観察1「先頭で NDEBUG を定義する（assert.h より前）」版（variants/tests/ndebug.out）
# わざと偽になる assert に変えても，NDEBUG では式が評価されず終了コード 0・同じ表示になる
softprac_add_variant(LibraryCheck library_check.c ndebug
  "#define _CRT_SECURE_NO_WARNINGS" "#define _CRT_SECURE_NO_WARNINGS\n#define NDEBUG"
  "assert(bytes[3] == 'c');"
  "assert(bytes[3] == 'x');  /* わざと偽の式．NDEBUG では評価されないので異常終了しない */"
  "標準ライブラリの契約（ヘッダ・入力条件・戻り値）を確かめる．演習ページのコードのまま"
  "追加の観察1: 先頭で NDEBUG を定義した版（assert が無効になる）")
