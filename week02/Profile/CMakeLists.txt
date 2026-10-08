# 第2回 課題2 Profile
# 本体に加えて，「表示方法を変えてみる」の手順 1〜3 の版と，total を int にした誤りの版をビルドしてテストする。
# 各版は先頭コメントの 2 行目（と，書式を変えた版では %.2f の説明）も版の説明に置き換える
softprac_add_program(Profile profile.c)

set(profile_desc "// 整数は int と %d，小数は double と %f，1 文字は char と %c を対応させる")
set(profile_format_comment "// %.2f は表示する桁数の指定であり，変数の値は変えない")

# 手順 1: price の %.2f だけを %f に変える
softprac_add_variant(Profile profile.c price_f
  "${profile_desc}"
  "// price の %.2f を %f に書き換えた版（表示は 6 桁になるが price の値は変わらない）"
  "${profile_format_comment}" "// price だけ %f（小数点以下 6 桁）。total は %.2f のまま"
  "price=%.2f" "price=%f")
# 手順 3: 続けて count を 0 に変える（%f のまま）
softprac_add_variant(Profile profile.c price_f_count_0
  "${profile_desc}"
  "// price の %.2f を %f に書き換え，続けて count を 0 にした版（total は 0 × 125.5 で 0.00）"
  "${profile_format_comment}" "// price だけ %f（小数点以下 6 桁）。total は %.2f のまま"
  "price=%.2f" "price=%f" "count = 3" "count = 0")
# 参考: 書式は元のまま count だけを 0 に変える
softprac_add_variant(Profile profile.c count_0
  "${profile_desc}"
  "// count を 3 から 0 に書き換えた版（書式は元のまま。total は 0 × 125.5 で 0.00）"
  "count = 3" "count = 0")

# 採点のポイントの「total を int にする」: 376.5 が 376 に切り捨てられ，%d で total=376 と表示される。
# 誤りを示すための版なので，MSVC /W4 /WX でエラーになる C4244（double から int への変換で情報が失われる。
# 番号は Microsoft のドキュメントによる）をこの版だけ抑止する（GCC/Clang の -Wall -Wextra -Wpedantic は
# -Wconversion を含まないので警告しない）。警告の抑止を含めて CI で成功。警告の文面はドキュメントによる例
softprac_add_variant(Profile profile.c int_total
  "${profile_desc}"
  "// 誤りの例: total を int にした版（376.5 が 376 に切り捨てられ，%d で total=376 と表示される）"
  "double total = count * price;   // int と double の積は double になる"
  "int total = count * price;      // 誤り: double の 376.5 を int に入れると 376 に切り捨てられる"
  "${profile_format_comment}" "// price は %.2f のまま。total は int にしたので %d で表示する"
  [[printf("total=%.2f\n", total);]]
  [[printf("total=%d\n", total);]])
target_compile_options(Profile_int_total PRIVATE $<$<C_COMPILER_ID:MSVC>:/wd4244>)
