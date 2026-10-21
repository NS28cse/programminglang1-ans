# 第13回 発展3「途中で失敗した場合」DynamicVectorFail
# vector_main.c と vector.h は正常版（../DynamicVector）を使い，vector.c だけを失敗を模擬する版に差し替える
set(normal_dir "${CMAKE_CURRENT_SOURCE_DIR}/../DynamicVector")
softprac_add_program(DynamicVectorFail vector.c "${normal_dir}/vector_main.c" "${normal_dir}/vector.h")
target_include_directories(DynamicVectorFail PRIVATE "${normal_dir}")
