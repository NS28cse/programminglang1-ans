# 第13回 発展3「途中で失敗した場合」（DynamicVectorFail）
# vector_main.c と vector.h は正常版（../DynamicVector）を使い，vector.c だけを試験用に差し替える。
# 本体は fail_on_call = 2（演習ページの値）。残りの 0，1，3 は vector.c の値を書き換えた版としてテストする
set(normal_dir "${CMAKE_CURRENT_SOURCE_DIR}/../DynamicVector")

softprac_add_program(DynamicVectorFail vector.c "${normal_dir}/vector_main.c" "${normal_dir}/vector.h")
target_include_directories(DynamicVectorFail PRIVATE "${normal_dir}")

foreach(n 0 1 3)
  softprac_add_variant(DynamicVectorFail vector.c fail_on_call_${n}
    "fail_on_call は演習ページの値 2。" "fail_on_call を ${n} に書き換えた版（演習ページの値は 2）。"
    "fail_on_call = 2" "fail_on_call = ${n}")
  # 書き換えた vector.c に，分割した残りのソースとヘッダの場所を加える
  target_sources(DynamicVectorFail_fail_on_call_${n} PRIVATE "${normal_dir}/vector_main.c")
  target_include_directories(DynamicVectorFail_fail_on_call_${n} PRIVATE "${normal_dir}")
endforeach()

# 発展3 の別解（../DynamicVector/versions/early_return.c）を同じ試験用の vector.c と組み合わせ，
# fail_on_call = 1，2，3 の経路でも作成済みのものを解放して終了することを確かめる（リークは LeakSanitizer で検出する）
softprac_add_variant(DynamicVectorFail vector.c early_return_fail_on_call_2)
foreach(n 1 3)
  softprac_add_variant(DynamicVectorFail vector.c early_return_fail_on_call_${n}
    "fail_on_call は演習ページの値 2。" "fail_on_call を ${n} に書き換えた版（演習ページの値は 2）。"
    "fail_on_call = 2" "fail_on_call = ${n}")
endforeach()
foreach(n 1 2 3)
  target_sources(DynamicVectorFail_early_return_fail_on_call_${n} PRIVATE "${normal_dir}/versions/early_return.c")
  target_include_directories(DynamicVectorFail_early_return_fail_on_call_${n} PRIVATE "${normal_dir}")
endforeach()
