# 第12回 発展1 CalcApp: CalcLib（静的ライブラリ）を使うアプリ．ソースは main.c だけ
# Visual Studio の手順との対応
#   手順4「参照 → 参照の追加」で CalcLib を選ぶ             → target_link_libraries
#   手順5「追加のインクルード ディレクトリ」に CalcLib の実フォルダ → target_include_directories
softprac_add_program(CalcApp main.c)
target_include_directories(CalcApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../CalcLib")
# CalcLib は ../CalcLib/CMakeLists.txt で定義する．フォルダ名順では CalcApp より後に読まれるが，
# target_link_libraries のターゲット名は全体を読み終えた後で解決されるので参照できる
target_link_libraries(CalcApp PRIVATE CalcLib)

# 「まず講義の加算・乗算だけの 3 ファイルで確認」: subtract の呼び出しを除いた版（variants/tests/lecture.out）
softprac_add_variant(CalcApp main.c lecture
  [=[    printf("subtract=%.1f\n", subtract(5.0, 2.0));
]=] ""
  "静的ライブラリ CalcLib の関数を呼び出すアプリ．このプロジェクトには main.c だけを入れる"
  "講義の加算・乗算だけを呼ぶ版（subtract の呼び出しを除いた版）")
target_include_directories(CalcApp_lecture PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../CalcLib")
target_link_libraries(CalcApp_lecture PRIVATE CalcLib)
