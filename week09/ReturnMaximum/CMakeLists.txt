# 第9回 課題1 ReturnMaximum: 本体は演習ページの表示（before=12 12, after=12 99）どおり。書き換えた版もテストする
#   negative    … 配列を {-7, -12, -4} にした版
#   pointer_n0  … 場所を返す版だけ n を 0 にした版（何も表示しない）
#   best_zero   … {-7, -12, -4} で，max_value の最大候補を 0 から始めた（誤った）版
# 各版は先頭コメントの 2 行目を版の説明に置き換え，書き換えた行のコメントも合わせる（置換前の文字列は行全体）
softprac_add_program(ReturnMaximum return_maximum.c)

set(desc [=[// 最大値のコピーを返す max_value と，最大要素の場所を返す max_pointer を比べる（表示は before=12 12 と after=12 99）。]=])
set(init "    int a[] = {7, 12, 4};")
set(init_negative "    int a[] = {-7, -12, -4};  // 全要素が負")

softprac_add_variant(ReturnMaximum return_maximum.c negative
  "${desc}"
  "// 配列を全要素が負の {-7, -12, -4} にした版。\n// max_value は先頭要素から始めるので最大値 -4 を返す。表示は before=-4 -4 と after=-4 99。"
  "${init}" "${init_negative}")
softprac_add_variant(ReturnMaximum return_maximum.c pointer_n0
  "${desc}"
  "// 場所を返す max_pointer だけ n を 0 にした版（max_value は n=3 のまま）。\n// max_pointer は NULL を返すので，if の中は実行されず何も表示しない。"
  "    int *found = max_pointer(a, 3);   // 元の配列の要素を指す"
  "    int *found = max_pointer(a, 0);   // n=0 なので NULL（何も表示しない）")
softprac_add_variant(ReturnMaximum return_maximum.c best_zero
  "${desc}"
  "// 誤りの例: 配列を {-7, -12, -4} にし，max_value の最大候補を 0 から始めた版。\n// 0 より大きい要素がないので配列にない 0 を返す。表示は before=0 -4 と after=0 99（誤り）。"
  "${init}" "${init_negative}"
  "    int best = a[0];  // 0 からではなく先頭要素から始める（全要素が負でも正しい）"
  "    int best = 0;  // 誤りの例: 全要素が負だと配列にない 0 を返す")
