# 第6回 ウォームアップ CharCode
# 本体に加えて，c を '0'，'9'，'A' に変えた版をビルドしてテストする（'A' では digit の行を出さない）
softprac_add_program(CharCode char_code.c)

# 各版は 1 行目のコメントにも「c を '0' に変えた版」のような説明を足す
set(title [[（CharCode / char_code.c）]])
foreach(c IN ITEMS 0 9 A)
  softprac_add_variant(CharCode char_code.c c_${c} "char c = '3'" "char c = '${c}'"
                       "${title}" "${title}。c を '${c}' に変えた版")
endforeach()
