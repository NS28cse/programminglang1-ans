# 第4回 発展（BreakContinue）: 本体と，i == 4 の break を continue に変えた版をビルドしてテストする
softprac_add_program(BreakContinue break_continue.c)

include("${CMAKE_CURRENT_SOURCE_DIR}/../_cmake/variants.cmake")
week04_add_variant(continue_at_4 break_continue.c variants/continue_at_4 "break" "continue")
