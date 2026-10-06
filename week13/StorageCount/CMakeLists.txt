# 第13回 発展2 StorageCount
# 本体（static int count = 0;）に加えて，「3 種類を比較する」のうち static を外した版をビルドしてテストする
# （3 つ目の「static int count; の後に文として count = 0;」は ; を含む置換になるため README に実行結果を載せる）
softprac_add_program(StorageCount count.c)

softprac_add_variant(StorageCount count.c auto_count "static int count = 0" "int count = 0")
