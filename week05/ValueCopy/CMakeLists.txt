# 第5回 課題3 ValueCopy
# 本体は演習ページのプログラム（10 11 を表示）。演習ページの各実験は main の一部を書き換えた版としてビルドしてテストする
#   x_0 / x_m1    … 初期値を 0，-1 に変えた版
#   call_discard / call_assign / assign_twice … 3 つの呼び出し方の表と，x = increment(x); を 2 回続ける実験
#   add_z         … 最初の呼び出しの後に int z = increment(x); を追加し，x y z を表示する版
#   scope_blocks  … スコープの読解の 2 つのブロックを main 内に書いた版
# 各版は先頭コメントの 2〜3 行目も版の説明に置き換える。
# 確認問題5・6 の確認用の別ソース versions/ も，置換なしの版としてビルドしてテストする
softprac_add_program(ValueCopy valuecopy.c)

set(body [=[    int y = increment(x);
    printf("%d %d\n", x, y);]=])

softprac_add_variant(ValueCopy valuecopy.c x_0
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// 初期値を 0 に書き換えた版（0 1）。\n// 仮引数 x は main の x のコピーなので，main の x は 0 のまま。"
  "int x = 10;" "int x = 0;")

softprac_add_variant(ValueCopy valuecopy.c x_m1
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// 初期値を -1 に書き換えた版（-1 0）。\n// 仮引数 x は main の x のコピーなので，main の x は -1 のまま。"
  "int x = 10;" "int x = -1;")

softprac_add_variant(ValueCopy valuecopy.c call_discard
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// 呼び出しを increment(x); だけに書き換えた版（10）。\n// 戻り値 11 は捨てられ，main の x は 10 のまま。"
  "${body}"
  [=[    increment(x);  // 戻り値は使われない
    printf("%d\n", x);]=])

softprac_add_variant(ValueCopy valuecopy.c call_assign
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// 呼び出しを x = increment(x); に書き換えた版（11）。\n// 関数の中ではコピーが変わるだけで，main の x が 11 になるのは戻り値の代入による。"
  "${body}"
  [=[    x = increment(x);  // 戻り値を main の x へ代入する
    printf("%d\n", x);]=])

softprac_add_variant(ValueCopy valuecopy.c assign_twice
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// 呼び出しを x = increment(x); の 2 回に書き換えた版（12）。\n// main の x が 10 → 11 → 12 と変わるのは，呼び出し元の代入が 2 回行われるから。"
  "${body}"
  [=[    x = increment(x);
    x = increment(x);
    printf("%d\n", x);]=])

softprac_add_variant(ValueCopy valuecopy.c add_z
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// 最初の呼び出しの後に int z = increment(x); を追加した版（10 11 11）。\n// 仮引数 x は呼び出しごとに作り直されるので，2 回目も main の x の値 10 から始まる。"
  "${body}"
  [=[    int y = increment(x);
    int z = increment(x);  // x は 10 のままなので，z も 11
    printf("%d %d %d\n", x, y, z);]=])

softprac_add_variant(ValueCopy valuecopy.c scope_blocks
  "// 演習ページのプログラムそのもの（その後の実験は README 参照）。\n// 仮引数 x は呼び出しごとに作られる別の局所変数なので，main の x は 10 のまま。"
  "// main の本体をスコープの読解の 2 つのブロックに書き換えた版（123 と 345）。\n// 2 つの a は別々のブロックの別の局所変数（increment はこの版では呼ばない）。"
  "    int x = 10;
${body}"
  [=[    {
        int a = 123;
        printf("%d\n", a);
    }
    {
        int a = 345;
        printf("%d\n", a);
    }]=])

# 確認問題5: plus_one の戻り値を使わない・別の変数に保存する・代入する
softprac_add_variant(ValueCopy versions/plus_one.c plus_one)
# 確認問題6: グローバル変数 count を同名の局所変数で隠す。隠蔽を示すための版なので，
# MSVC /W4 /WX でエラーになる「グローバル宣言を隠す」警告（番号は Microsoft Learn の説明に基づく例: C4459）を
# この版だけ抑止する（GCC/Clang の -Wall -Wextra は -Wshadow を含まない）
softprac_add_variant(ValueCopy versions/shadow_count.c shadow_count)
target_compile_options(ValueCopy_shadow_count PRIVATE $<$<C_COMPILER_ID:MSVC>:/wd4459>)
