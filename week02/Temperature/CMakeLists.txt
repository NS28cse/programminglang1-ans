# 第2回 課題5 Temperature
# 本体に加えて，「値を変えて確かめる」（celsius = 0.0，100.0，-40.0）版と，
# 計算後に celsius を変えた版（再計算の前後を表示する）をビルドしてテストする
softprac_add_program(Temperature temperature.c)

softprac_add_variant(Temperature temperature.c celsius_0 "celsius = 25.0" "celsius = 0.0")
softprac_add_variant(Temperature temperature.c celsius_100 "celsius = 25.0" "celsius = 100.0")
softprac_add_variant(Temperature temperature.c celsius_m40 "celsius = 25.0" "celsius = -40.0")

# 計算後に celsius を 100.0 へ変える: 再計算前は 77.0 のまま，再計算後に 212.0 になる
softprac_add_variant(Temperature temperature.c change_after
  [[    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
]]
  [[    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    celsius = 100.0;
    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("Celsius=%.1f Fahrenheit=%.1f\n", celsius, fahrenheit);
]])
