# 第13回 課題3「失敗を模擬する」NewPointFail
# 本体は simulate_failure = 1（確保失敗の経路）。simulate_failure = 0 にした版（正常出力になる）もビルドしてテストする
softprac_add_program(NewPointFail new_point.c)

softprac_add_variant(NewPointFail new_point.c simulate_failure_0 "const int simulate_failure = 1" "const int simulate_failure = 0")
