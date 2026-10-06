# 第10回 課題3 Binary
# 本体（フォルダのソース）は data を UTF-8 の「あ」と LF へ置き換えた最終版。
# 置き換える前の講義の binary.c（41 00 42 0A）も sample としてビルドしてテストする（期待値: variants/tests/sample.*）
softprac_add_program(Binary binary.c)

softprac_add_variant(Binary binary.c sample
  "{0xE3, 0x81, 0x82, 0x0A}" "{0x41, 0x00, 0x42, 0x0A}")
