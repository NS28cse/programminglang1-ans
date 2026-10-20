# 第11回 発展3 StructLayout
# 本体（演習ページの断片どおりの Record）に加えて，メンバを tag，flag，count の順に並べ替えた比較用ソース
# （versions/record_reordered.c）をテストする。配置は処理系依存だが，x64 の GCC・Clang・MSVC（既定）と
# macOS arm64 では同じ値になるのでテストにしている（他の処理系では違ってよい）
softprac_add_program(StructLayout struct_layout.c)

# 比較用: メンバの順序を変えると隙間が 6 バイトから 2 バイトに減る
softprac_add_variant(StructLayout versions/record_reordered.c record_reordered)
