# 第4回 課題1 Fee
# 本体（age = 17）に加えて，演習ページの表の age（-1, 0, 5, 6, 18）に変えた版と，
# 「条件の順序を確かめる」「別々の if にする」「負の年齢の検査を省く」の書き換え版を，表の 6 つの age でビルドしてテストする
# （ケース名の m1 は age = -1）。各版は先頭コメントの 2 行目（fee_head）を版の説明に置き換える。
# 確認問題1（if (3)）と 2（flag = -1）の確認用のコードは versions/ に置き，置換なしでビルドしてテストする
softprac_add_program(Fee fee.c)

set(fee_head "// 年齢 age から料金を表示する．負の年齢を最初に invalid として除き，残りを小さい区分から調べる．")

# age_value(<変数> <age の値>): "age = 17;" を置き換える文字列。同じ長さになるように ; の後に空白を補い，
# 行末のコメントの桁を本体とそろえる
function(age_value out value)
  set(text "age = ${value};")
  string(LENGTH "${text}" len)
  math(EXPR npad "9 - ${len}")
  set(pad "")
  if(npad GREATER 0)
    string(REPEAT " " ${npad} pad)
  endif()
  set(${out} "${text}${pad}" PARENT_SCOPE)
endfunction()

foreach(age m1 0 5 6 18)
  string(REPLACE "m" "-" value "${age}")
  age_value(age_new "${value}")
  softprac_add_variant(Fee fee.c age_${age}
    "age = 17;" "${age_new}"
    "${fee_head}" "// age を ${value} に書き換えた版（演習ページの表の値）．負の年齢を最初に invalid として除き，残りを小さい区分から調べる．")
endforeach()

# fee_variant(<ケース名> <age（m1 は -1）> <見出しの 2 行目> <置換前> <置換後>)
# 書き換えた版を 1 つの age でビルドする（age = 17 のときは置換前と置換後が同じで，値は変わらない）
function(fee_variant case age head old new)
  string(REPLACE "m" "-" value "${age}")
  age_value(age_new "${value}")
  softprac_add_variant(Fee fee.c ${case}
    "age = 17;" "${age_new}"
    "${fee_head}" "// ${head}age = ${value} で実行する．"
    "${old}" "${new}")
endfunction()

# age <= 17 を age <= 5 より前に置いた版（誤りの例。0〜5 も 500 になる）
set(swap_old [=[    } else if (age <= 5) {      // 0〜5 歳
        printf("0\n");
    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）
        printf("500\n");]=])
set(swap_new [=[    } else if (age <= 17) {     // 先に調べるので 0〜17 歳がここに入る
        printf("500\n");
    } else if (age <= 5) {      // 0〜5 は前の age <= 17 で真になるので，ここには来ない
        printf("0\n");]=])
foreach(age m1 0 5 6 17 18)
  fee_variant(swapped_age_${age} ${age}
    "age <= 17 を age <= 5 より前に置いた版（誤りの例。0〜5 も 500 になる）．"
    "${swap_old}" "${swap_new}")
endforeach()

# else if を別々の if にした版（誤りの例。-1 では 3 つ，0〜5 では 2 つの条件が真になり，複数行表示する）
set(sep_old [=[    if (age < 0) {
        printf("invalid\n");
    } else if (age <= 5) {      // 0〜5 歳
        printf("0\n");
    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）
        printf("500\n");
    } else {                    // 残りは 18 歳以上だけ
        printf("1000\n");
    }]=])
set(sep_new [=[    if (age < 0) {
        printf("invalid\n");
    }
    if (age <= 5) {             // 別々の if なので負の年齢もここが真になる
        printf("0\n");
    }
    if (age <= 17) {            // 別々の if なので 0〜5 と負の年齢もここが真になる
        printf("500\n");
    } else {                    // 直前の if (age <= 17) だけに対応する（18 歳以上）
        printf("1000\n");
    }]=])
foreach(age m1 0 5 6 17 18)
  fee_variant(separate_if_age_${age} ${age}
    "else if を別々の if にした版（誤りの例。条件がそれぞれ独立になり，-1 や 0〜5 では複数行表示する）．"
    "${sep_old}" "${sep_new}")
endforeach()

# 負の年齢の検査を省いた版（誤りの例。-1 は age <= 5 が真になり 0 の区分に入る）
fee_variant(no_check_age_m1 m1
  "負の年齢の検査（age < 0）を削除した版（誤りの例。-1 は age <= 5 が真になり 0 になる）．"
  [=[    if (age < 0) {
        printf("invalid\n");
    } else if (age <= 5) {      // 0〜5 歳]=]
  [=[    if (age <= 5) {             // 下限がないので負の年齢もここに入る]=])

# 6〜17 歳の条件を age < 17 にした版（誤りの例。17 歳が 1000 になる）
fee_variant(lt_17_age_17 17
  "6〜17 歳の条件を age < 17 にした版（誤りの例。17 歳が 1000 になる）．"
  [=[    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）
        printf("500\n");
    } else {                    // 残りは 18 歳以上だけ]=]
  [=[    } else if (age < 17) {      // 誤り: 17 を含まない（6〜16 歳だけ）
        printf("500\n");
    } else {                    // 17 歳以上（17 歳もここに入ってしまう）]=])

# 0〜5 歳の条件を age < 5 にした版（誤りの例。5 歳が 500 になる）
fee_variant(lt_5_age_5 5
  "0〜5 歳の条件を age < 5 にした版（誤りの例。5 歳が 500 になる）．"
  [=[    } else if (age <= 5) {      // 0〜5 歳
        printf("0\n");
    } else if (age <= 17) {     // 6〜17 歳（5 以下はここまでに除かれている）]=]
  [=[    } else if (age < 5) {       // 誤り: 5 を含まない（0〜4 歳だけ）
        printf("0\n");
    } else if (age <= 17) {     // 5〜17 歳（5 歳もここに入ってしまう）]=])

# 確認問題1: if (3) は真の経路へ進む（0 以外はすべて真）
softprac_add_variant(Fee versions/if_three.c if_three)
# MSVC /W4 では定数の条件式の警告（C4127 など。番号は例）や到達しないコードの警告（C4702 など）が出る可能性があるため，
# 確認用のこの版だけ抑止する（抑止を含めて CI で成功。警告番号は例）
target_compile_options(Fee_if_three PRIVATE $<$<C_COMPILER_ID:MSVC>:/wd4127> $<$<C_COMPILER_ID:MSVC>:/wd4702>)
# 確認問題2: flag = -1 のとき if (flag) は真，if (!flag) と if (flag == 1) は偽
softprac_add_variant(Fee versions/flag_minus1.c flag_minus1)
