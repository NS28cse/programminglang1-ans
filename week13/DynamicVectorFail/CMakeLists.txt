# 第13回 発展3「途中で失敗した場合」（DynamicVectorFail）
#   vector_main.c と vector.h は正常版（../DynamicVector）をそのまま使い，vector.c だけを試験用に差し替える。
#   本体は fail_on_call = 2（演習ページの値）。演習ページの「番号を 0，1，2，3 に変え，それぞれ新しく実行」の
#   残り 0，1，3 は，softprac_add_variant で vector.c の値を書き換えた版として作り，テストする。
set(normal_dir "${CMAKE_CURRENT_SOURCE_DIR}/../DynamicVector")

softprac_add_program(DynamicVectorFail vector.c "${normal_dir}/vector_main.c" "${normal_dir}/vector.h")
target_include_directories(DynamicVectorFail PRIVATE "${normal_dir}")

foreach(n 0 1 3)
  softprac_add_variant(DynamicVectorFail vector.c fail_on_call_${n}
    "この版は演習ページの値 2。" "この版は fail_on_call = ${n} に書き換えた版（演習ページの値は 2）。"
    "fail_on_call = 2" "fail_on_call = ${n}")
  # 書き換えた vector.c に，分割した残りのソースとヘッダの場所を加える
  target_sources(DynamicVectorFail_fail_on_call_${n} PRIVATE "${normal_dir}/vector_main.c")
  target_include_directories(DynamicVectorFail_fail_on_call_${n} PRIVATE "${normal_dir}")
endforeach()
