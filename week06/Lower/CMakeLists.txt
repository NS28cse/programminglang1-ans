# 第6回 課題2 Lower
# 本体（"Hello C17!"）に加えて，演習ページの表の初期値に変えた版をビルドしてテストする
softprac_add_program(Lower lower.c)

softprac_add_variant(Lower lower.c empty "\"Hello C17!\"" "\"\"")
softprac_add_variant(Lower lower.c AZaz09 "\"Hello C17!\"" "\"AZaz09\"")
# "@AZ[" の [ は対にならず，後ろに ; があると CMake のリストの区切りが無視されるので，最後の引数にだけ置く
softprac_add_variant(Lower lower.c at_AZ_bracket "\"Hello C17!\"" "\"@AZ[\"")
softprac_add_variant(Lower lower.c A_space_B "\"Hello C17!\"" "\"A B\"")
