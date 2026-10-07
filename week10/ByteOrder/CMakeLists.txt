# 第10回 課題3「バイト順を調べる」ByteOrder（演習ページの「別の main」。プロジェクト名は解答で付けた）
# 本体は講義の断片どおり value = 1。値を 0x1234 へ変更した版を value_0x1234 としてテストする（期待値: variants/tests/value_0x1234.*）
softprac_add_program(ByteOrder byte_order.c)

softprac_add_variant(ByteOrder byte_order.c value_0x1234
  "unsigned short value = 1;" "unsigned short value = 0x1234;")
