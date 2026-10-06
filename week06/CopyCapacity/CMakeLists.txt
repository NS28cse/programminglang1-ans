# 第6回 発展 CopyCapacity（講義の strings.c）
# フォルダのソースは copy[3] の最終版。講義の元の容量16と，演習ページの容量4の版もビルドしてテストする
softprac_add_program(CopyCapacity strings.c)

softprac_add_variant(CopyCapacity strings.c capacity_16 "char copy[3]" "char copy[16]")
softprac_add_variant(CopyCapacity strings.c capacity_4 "char copy[3]" "char copy[4]")
