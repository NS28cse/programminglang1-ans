# 第12回 発展1 CalcLib: 静的ライブラリ（Visual Studio の「構成の種類: スタティック ライブラリ (.lib)」に当たる）
# MSVC では CalcLib.lib，GCC/Clang では libCalcLib.a を <ビルドフォルダ>/lib/week12/ に作る
add_library(CalcLib STATIC calc.c calc.h)
softprac_apply_options(CalcLib)
set_target_properties(CalcLib PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${SOFTPRAC_WEEK}"
  FOLDER "${SOFTPRAC_WEEK}")
