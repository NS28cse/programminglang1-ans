# 第2回 課題5 Temperature
# 本体に加えて，「値を変えて確かめる」（celsius = 0.0，100.0，-40.0）版と，
# 計算後に celsius を変えた版（再計算の前後を表示する），9 / 5 を整数で計算する誤りの版をビルドしてテストする。
# 各版は先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(Temperature temperature.c)

set(temperature_desc "// 摂氏 celsius から華氏 fahrenheit を計算する。77.0 を直接書かず，式で求める")

softprac_add_variant(Temperature temperature.c celsius_0
  "${temperature_desc}"
  "// celsius の初期値を 0.0 に書き換えた版（華氏は 32.0）"
  "celsius = 25.0" "celsius = 0.0")
softprac_add_variant(Temperature temperature.c celsius_100
  "${temperature_desc}"
  "// celsius の初期値を 100.0 に書き換えた版（華氏は 212.0）"
  "celsius = 25.0" "celsius = 100.0")
softprac_add_variant(Temperature temperature.c celsius_m40
  "${temperature_desc}"
  "// celsius の初期値を -40.0 に書き換えた版（摂氏と華氏が等しく -40.0）"
  "celsius = 25.0" "celsius = -40.0")

# 計算後に celsius を 100.0 へ変える: 再計算前は 77.0 のまま，再計算後に 212.0 になる
softprac_add_variant(Temperature temperature.c change_after
  "${temperature_desc}"
  "// 計算後に celsius を 100.0 へ変えた版（再計算前は 77.0 のまま）"
  [[    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
]]
  [[    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    celsius = 100.0;
    // 再計算する前なので fahrenheit は 77.0 のまま
    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
]])

# 採点のポイントの「整数の割り算」: 9 / 5 が整数どうしの割り算で 1 になり，25.0 で 57.0 と表示される
softprac_add_variant(Temperature temperature.c int_division
  "${temperature_desc}"
  "// 誤りの例: 9 / 5 を整数どうしで先に計算した版（1 になり 57.0 と表示される）"
  "celsius * 9.0 / 5.0 + 32.0;    // 9.0 / 5.0 で小数の計算にする"
  "9 / 5 * celsius + 32;          // 誤り: 9 / 5 は整数の割り算で 1")
