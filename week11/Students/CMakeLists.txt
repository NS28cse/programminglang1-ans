# 第11回 課題2 Students
# 本体（平均と，演習ページの交換の断片の表示）に加えて，演習ページの表の条件（人数・点数）と，
# よくある誤り（整数除算・score だけの交換）の版，名前を比較する確認用ソース（versions/same_student.c）をテストする。
# 各版は先頭コメントの説明の行と書き換えた行のコメントを，その版の内容に合わせて置き換える
softprac_add_program(Students students.c)

set(header "// Student 配列の平均と，構造体全体の代入による 1 人分の交換。")
set(scores [=[    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 90}}; // 点数は 0〜100]=])
set(count "    int n = 3; // 平均に使う人数（1〜3）。4 や 0 にはしない")
set(swap_comment "    // 名前と点数を 1 人分まとめて交換する")
set(swap [=[    Student temp = a[0];
    a[0] = a[2];
    a[2] = temp;]=])
set(swap_score_only [=[    int temp = a[0].score;
    a[0].score = a[2].score;
    a[2].score = temp;]=])

# 表の条件: 人数 n を 1，2 にする
softprac_add_variant(Students students.c n_1
  "${header}"
  "// 平均に使う人数 n を 1 に書き換えた版（Aki だけの平均 80.0。交換後は先頭の Mio だけで 90.0）"
  "${count}"
  "    int n = 1; // 平均に使う人数を 1 にした（a[0] だけ）")
softprac_add_variant(Students students.c n_2
  "${header}"
  "// 平均に使う人数 n を 2 に書き換えた版（(80+70)/2 = 75.0）"
  "${count}"
  "    int n = 2; // 平均に使う人数を 2 にした（a[0] と a[1]）")
# 表の条件: 点数を全員 0，全員 100，80・70・91 にする
softprac_add_variant(Students students.c all_0
  "${header}"
  "// 点数を全員 0 に書き換えた版（平均 0.0）"
  "${scores}"
  [=[    Student a[COUNT] = {{"Aki", 0}, {"Ren", 0}, {"Mio", 0}}; // 点数を全員 0 にした]=])
softprac_add_variant(Students students.c all_100
  "${header}"
  "// 点数を全員 100 に書き換えた版（合計 300 でも int で表せ，平均 100.0）"
  "${scores}"
  [=[    Student a[COUNT] = {{"Aki", 100}, {"Ren", 100}, {"Mio", 100}}; // 点数を全員 100 にした]=])
softprac_add_variant(Students students.c scores_80_70_91
  "${header}"
  "// 点数を 80，70，91 に書き換えた版（241/3 = 80.333… を %.1f で 80.3 と表示）"
  "${scores}"
  [=[    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 91}}; // 合計 241 で割り切れない]=])

# 誤り: 整数どうしの割り算（241 / 3 が 80 になる）
softprac_add_variant(Students students.c int_division
  "${header}"
  "// 誤りの例: 点数を 80，70，91 にし，平均を整数どうしの割り算にした版（80.3 ではなく 80.0 になる）"
  "${scores}"
  [=[    Student a[COUNT] = {{"Aki", 80}, {"Ren", 70}, {"Mio", 91}}; // 合計 241 で割り切れない]=]
  "    return (double)sum / n; // 整数どうしの割り算にしない"
  "    return sum / n; // 誤り: 整数どうしの割り算（小数部が切り捨てられる）")
# 誤り: score だけを交換すると名前と点数の対応が壊れる
softprac_add_variant(Students students.c score_only_swap
  "${header}"
  "// 誤りの例: a[0] と a[2] の score だけを交換する版（名前は元の位置のままで，名前と点数の対応が壊れる）"
  "${swap_comment}"
  "    // 誤り: score だけを交換する（名前は元の位置のまま）"
  "${swap}" "${swap_score_only}")

# 名前を比較する: 交換前の 1 人目のコピーと交換後の a[0]・a[2] を same_student で比べる
softprac_add_variant(Students versions/same_student.c same_student)
# score だけを交換すると，交換前の Aki 80 と同じ学生がどこにもいなくなる（両方 0）
softprac_add_variant(Students versions/same_student.c same_student_score_only_swap
  "// 交換前の 1 人目のコピー first を，交換後の a[0]・a[2] と same_student で比べる。"
  "// 誤りの例: score だけを交換してから first と a[0]・a[2] を比べる版（どちらとも一致しない）"
  "${swap_comment}"
  "    // 誤り: score だけを交換する（名前は元の位置のまま）"
  "${swap}" "${swap_score_only}"
  "    // first と a[2] は別の保存場所だが，内容（名前と点数）が同じなので 1"
  "    // a[2] は名前が Mio のまま点数だけ 80 になったので，first（Aki 80）とは一致しない")
