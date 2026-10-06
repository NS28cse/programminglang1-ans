# 第2回 課題5 Temperature
# 本体に加えて，「値を変えて確かめる」（celsius = 0.0，100.0，-40.0）版をビルドしてテストする
softprac_add_program(Temperature temperature.c)

softprac_add_variant(Temperature temperature.c celsius_0 "celsius = 25.0" "celsius = 0.0")
softprac_add_variant(Temperature temperature.c celsius_100 "celsius = 25.0" "celsius = 100.0")
softprac_add_variant(Temperature temperature.c celsius_m40 "celsius = 25.0" "celsius = -40.0")
