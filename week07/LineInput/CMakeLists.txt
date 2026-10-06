# 第7回 課題3 LineInput
# 本体（講義の line.c，容量 32）に加えて，「容量を小さくして仕組みを見る」（line[32] を line[8] に変える）版をテストする
# 期待値は variants/tests/line8--<入力の名前>.*
softprac_add_program(LineInput line.c)

softprac_add_variant(LineInput line.c line8 "char line[32];" "char line[8];")
