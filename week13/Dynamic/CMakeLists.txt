# 第13回 課題1・2 Dynamic
# 本体に加えて，課題2の考察「全要素について交換すると元の順序へ戻る」を確かめる版（i < n / 2 を i < n に変える）をテストする
softprac_add_program(Dynamic dynamic.c)

softprac_add_variant(Dynamic dynamic.c swap_all "i < n / 2" "i < n")
