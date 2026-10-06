# 第3回 課題5（発展） Flags
# 本体は自動の規則と同じ。値や書き方を変えて試す版（tests/variants/）を追加するためにこのファイルを置く
softprac_add_program(Flags flags.c)

include("${CMAKE_CURRENT_LIST_DIR}/../variants.cmake")
# 最初の flags を 0u，7u に変える
week03_add_variant(Flags flags.c start_0 "unsigned int flags = 1u;" "unsigned int flags = 0u;")
week03_add_variant(Flags flags.c start_7 "unsigned int flags = 1u;" "unsigned int flags = 7u;")
# 説明すること: 同じ権限を2回セットする。OR なら変わらず，加算だと桁上がりして別のビットが変わる
week03_add_variant(Flags flags.c set_twice_or
  "flags |= write_mask;" "flags |= write_mask;\n    flags |= write_mask;")
week03_add_variant(Flags flags.c set_twice_add
  "flags |= write_mask;" "flags += write_mask;\n    flags += write_mask;")
