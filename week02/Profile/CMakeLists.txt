# 第2回 課題2 Profile
# 本体に加えて，「表示方法を変えてみる」の手順 1〜3 の版をビルドしてテストする
softprac_add_program(Profile profile.c)

# 手順 1: price の %.2f だけを %f に変える
softprac_add_variant(Profile profile.c price_f "price=%.2f" "price=%f")
# 手順 3: 続けて count を 0 に変える（%f のまま）
softprac_add_variant(Profile profile.c price_f_count_0 "price=%.2f" "price=%f" "count = 3" "count = 0")
# 参考: 書式は元のまま count だけを 0 に変える
softprac_add_variant(Profile profile.c count_0 "count = 3" "count = 0")
