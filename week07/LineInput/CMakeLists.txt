# 第7回 課題3 LineInput
# 本体（講義の line.c，容量 32）に加えて，「容量を小さくして仕組みを見る」（line[32] を line[8] に変える）版をテストする
softprac_add_program(LineInput line.c)

foreach(case line8_abcdef line8_abcdefg line8_abcdefgh line8_empty_line line8_eof_only line8_abcdefg_no_newline)
  softprac_add_variant(LineInput line.c ${case} "char line[32]" "char line[8]")
endforeach()
