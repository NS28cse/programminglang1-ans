# 第10回 課題3「バイト順を調べる」ByteOrder（演習ページの「別の main」。プロジェクト名は解答で付けた）
# 本体（フォルダのソース）は value を 0x1234 へ変更した最終版。
# 変更前（value = 1）も value_1 としてテストする（期待値: variants/tests/value_1.*）
softprac_add_program(ByteOrder byte_order.c)

softprac_add_variant(ByteOrder byte_order.c value_1
  "unsigned short value = 0x1234;" "unsigned short value = 1;")
