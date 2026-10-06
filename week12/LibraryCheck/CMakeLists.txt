# 第12回 発展3 LibraryCheck: ソースは library_check.c だけ（自作の calc.c などは入れない）
softprac_add_program(LibraryCheck library_check.c)
# Linux などの GCC/Clang では sqrt・pow の実装が数学ライブラリ libm にあり，-lm に当たる指定が要る．
# 授業の Visual Studio（MSVC）では標準の実行時ライブラリに含まれるので不要（講義 5 の「-lm を入力しない」）
if(NOT MSVC)
  target_link_libraries(LibraryCheck PRIVATE m)
endif()

# 追加の観察1「先頭で NDEBUG を定義する（assert.h より前）」版．assert が無効でも表示は同じになる（variants/tests/ndebug.out）
softprac_add_variant(LibraryCheck library_check.c ndebug
  "#define _CRT_SECURE_NO_WARNINGS" "#define _CRT_SECURE_NO_WARNINGS\n#define NDEBUG")
if(NOT MSVC)
  target_link_libraries(LibraryCheck_ndebug PRIVATE m)
endif()
