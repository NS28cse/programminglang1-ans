# デバッグ題材 BugSharedCounter（第12回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力。
# 直した版はヘッダと定義の .c の 2 ファイルを書き換えるので，softprac_add_variant（1 ファイルだけを書き換える）の
# 代わりに，ここで 3 ファイルとも生成してビルドする（テストの登録のしかたは softprac_add_variant と同じ）
softprac_add_program(BugSharedCounter main.c counter.c counter.h)

set(fixed_dir "${CMAKE_CURRENT_BINARY_DIR}/variants/fixed")

# <ファイル> を [<置換前> <置換後>]... で書き換えて fixed_dir に置く（置換前はちょうど 1 回現れること）
function(bug_shared_counter_fix file)
  set(src "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
  file(READ "${src}" text)
  set(i 1)
  while(i LESS ARGC)
    math(EXPR j "${i} + 1")
    set(old "${ARGV${i}}")
    string(FIND "${text}" "${old}" first)
    string(FIND "${text}" "${old}" last REVERSE)
    if(first EQUAL -1 OR NOT first EQUAL last)
      message(FATAL_ERROR "BugSharedCounter: ${file} に「${old}」がちょうど 1 回現れません")
    endif()
    string(REPLACE "${old}" "${ARGV${j}}" text "${text}")
    math(EXPR i "${i} + 2")
  endwhile()
  set(gen "${fixed_dir}/${file}")
  set(old_text "")
  if(EXISTS "${gen}")
    file(READ "${gen}" old_text)
  endif()
  if(NOT old_text STREQUAL text)
    file(WRITE "${gen}" "${text}")
  endif()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${src}")
endfunction()

bug_shared_counter_fix(counter.h
  "// デバッグ題材: 呼び出し回数を数える（第12回）"
  "// デバッグ題材: 呼び出し回数を数える（第12回）を直した版。ヘッダには extern の宣言だけを書く。"
  "static int call_count = 0;"
  "extern int call_count;")
bug_shared_counter_fix(counter.c
  "// デバッグ題材: 呼び出し回数を数える（第12回）"
  "// デバッグ題材: 呼び出し回数を数える（第12回）を直した版。call_count の定義はこのファイルだけに置く。"
  [=[
#include "counter.h"
]=]
  [=[
#include "counter.h"

int call_count = 0;
]=])
bug_shared_counter_fix(main.c
  "// デバッグ題材: 呼び出し回数を数える（第12回）"
  "// デバッグ題材: 呼び出し回数を数える（第12回）を直した版（main.c は元のまま）。")

set(name BugSharedCounter_fixed)
set_property(GLOBAL APPEND PROPERTY SOFTPRAC_PROGRAMS ${name})
add_executable(${name} "${fixed_dir}/main.c" "${fixed_dir}/counter.c" "${fixed_dir}/counter.h")
softprac_apply_options(${name})
set_target_properties(${name} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/variants/${SOFTPRAC_WEEK}"
  FOLDER "${SOFTPRAC_WEEK}/variants")
add_test(NAME "${SOFTPRAC_WEEK}/BugSharedCounter/variant_fixed"
  COMMAND "${CMAKE_COMMAND}"
    "-DPROGRAM=$<TARGET_FILE:${name}>"
    "-DPROJECT_DIR=${CMAKE_CURRENT_SOURCE_DIR}/variants"
    "-DCASE=fixed"
    "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}/fixed"
    -P "${SOFTPRAC_RUN_TEST}")
