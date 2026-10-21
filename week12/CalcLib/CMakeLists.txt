# 第12回 発展1 CalcLib: 静的ライブラリ（Visual Studio の Configuration Type: Static library (.lib) に当たる）
# MSVC では CalcLib.lib，GCC/Clang では libCalcLib.a ができる
add_library(CalcLib STATIC calc.c calc.h)
softprac_apply_options(CalcLib)
