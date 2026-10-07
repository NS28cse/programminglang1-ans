# 第11回 課題2 Students
# 本体に加えて，演習ページの表の条件（人数・点数）と，よくある誤り（整数除算・score だけの交換）の版をテストする
softprac_add_program(Students students.c)

set(scores [=[{{"Aki", 80}, {"Ren", 70}, {"Mio", 90}}]=])

softprac_add_variant(Students students.c n_1 "int n = 3;" "int n = 1;")
softprac_add_variant(Students students.c n_2 "int n = 3;" "int n = 2;")
softprac_add_variant(Students students.c all_0
  "${scores}" [=[{{"Aki", 0}, {"Ren", 0}, {"Mio", 0}}]=])
softprac_add_variant(Students students.c all_100
  "${scores}" [=[{{"Aki", 100}, {"Ren", 100}, {"Mio", 100}}]=])
softprac_add_variant(Students students.c scores_80_70_91
  "${scores}" [=[{{"Aki", 80}, {"Ren", 70}, {"Mio", 91}}]=])

# 誤り: 整数どうしの割り算（241 / 3 が 80 になる）
softprac_add_variant(Students students.c int_division
  "${scores}" [=[{{"Aki", 80}, {"Ren", 70}, {"Mio", 91}}]=]
  "return (double)sum / n; // 整数どうしの割り算にしない"
  "return sum / n; // 誤り: 整数どうしの割り算（小数部が切り捨てられる）")
# 誤り: score だけを交換すると名前と点数の対応が壊れる
softprac_add_variant(Students students.c score_only_swap
  "// 名前と点数を 1 人分まとめて交換する" "// 誤り: score だけを交換する（名前は元の位置のまま）"
  "Student temp = a[0];" "int temp = a[0].score;"
  "a[0] = a[2];" "a[0].score = a[2].score;"
  "a[2] = temp;" "a[2].score = temp;")
