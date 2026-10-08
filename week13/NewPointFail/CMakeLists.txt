# 第13回 課題3「失敗を模擬する」NewPointFail
# 本体は simulate_failure = 1（確保失敗の経路）。simulate_failure = 0 に戻した版（正常出力になる）もビルドしてテストする
softprac_add_program(NewPointFail new_point.c)

softprac_add_variant(NewPointFail new_point.c simulate_failure_0
  [=[// simulate_failure = 1 で確保失敗の経路（NULL を返し，main が診断を出して終了）を確かめる。]=]
  [=[// simulate_failure = 0 に戻した版（正常出力になる）。]=]
  "const int simulate_failure = 1" "const int simulate_failure = 0")
