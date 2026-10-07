# 第13回 課題2「追加：独立したコピー」DynamicCopy
# 本体に加えて，copy の確保に失敗した経路（先に確保した values を解放して終了する）を確かめる版をビルドしてテストする。
# 確保を NULL に置き換えるだけなので，課題3 の point_allocate と同じく実際のメモリ不足は起こさない。
softprac_add_program(DynamicCopy dynamic.c)

softprac_add_variant(DynamicCopy dynamic.c copy_alloc_fail
  "    copy = malloc(n * sizeof *copy);"
  "    copy = NULL;   // 試験用：copy の確保失敗を模擬")
