# 第13回 発展3「途中で失敗した場合」：vector_create の確保を fail_on_call 回目だけ失敗させる版
#   vector_main.c と vector.h は正常版（../DynamicVector）をそのまま使い，vector.c だけを試験用に差し替える。
#   fail_on_call = 0〜3 の 4 つの実行ファイルを作る（演習ページの「番号を変え，それぞれ新しく実行」に相当）。
#   テストは実行ファイルごとに callN/tests/ に置く（SOFTPRAC_PROJECT_DIR を切り替えて登録する）。
set(normal_dir "${CMAKE_CURRENT_SOURCE_DIR}/../DynamicVector")
set(fail_sources vector.c "${normal_dir}/vector_main.c" "${normal_dir}/vector.h")

set(SOFTPRAC_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/call0")
softprac_add_program(DynamicVectorFail0 ${fail_sources})
target_compile_definitions(DynamicVectorFail0 PRIVATE FAIL_ON_CALL=0)
target_include_directories(DynamicVectorFail0 PRIVATE "${normal_dir}")

set(SOFTPRAC_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/call1")
softprac_add_program(DynamicVectorFail1 ${fail_sources})
target_compile_definitions(DynamicVectorFail1 PRIVATE FAIL_ON_CALL=1)
target_include_directories(DynamicVectorFail1 PRIVATE "${normal_dir}")

set(SOFTPRAC_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/call2")
softprac_add_program(DynamicVectorFail2 ${fail_sources})
target_compile_definitions(DynamicVectorFail2 PRIVATE FAIL_ON_CALL=2)
target_include_directories(DynamicVectorFail2 PRIVATE "${normal_dir}")

set(SOFTPRAC_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/call3")
softprac_add_program(DynamicVectorFail3 ${fail_sources})
target_compile_definitions(DynamicVectorFail3 PRIVATE FAIL_ON_CALL=3)
target_include_directories(DynamicVectorFail3 PRIVATE "${normal_dir}")
