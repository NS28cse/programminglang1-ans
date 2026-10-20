# 第12回 発展1 CalcApp: CalcLib（静的ライブラリ）を使うアプリ。ソースは main.c だけ
#   Add > Reference で CalcLib を選ぶ                    → target_link_libraries
#   Additional Include Directories に CalcLib のフォルダ → target_include_directories
softprac_add_program(CalcApp main.c)
target_include_directories(CalcApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../CalcLib")
target_link_libraries(CalcApp PRIVATE CalcLib)
