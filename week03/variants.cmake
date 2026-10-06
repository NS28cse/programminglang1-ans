# 第3回: 「初期値を変えて試す」小問を自動テストにするための補助関数
#
# 第3回のプログラムは入力をソースに直接書く（scanf も引数も使わない）ので，値を変えた結果は
# ソースを書き換えて作り直した実行ファイルでしか確かめられない。そこで，ソースの一部の文字列を
# 置き換えた版をビルドフォルダに生成してビルドし，<プロジェクト>/tests/variants/<版>.out などを
# その版のテストとして登録する（形式は tests/ と同じ。cmake/RunTest.cmake で実行する）。
#
#   week03_add_variant(<プログラム名> <ソース> <版の名前> <置き換え前> <置き換え後>
#                      [<置き換え前2> <置き換え後2>])
#
# - 置き換え前の文字列がソースにちょうど 1 回だけ現れることを確かめ，そうでなければ構成エラーにする
#   （ソースを直した後に，元の版を別の版として誤ってテストしないため）。
# - 生成した版は Visual Studio の起動構成（tools/gen_launch_vs.py）には載らない。
include_guard(GLOBAL)

function(_week03_replace_once var source from to)
  string(FIND "${${var}}" "${from}" first)
  string(FIND "${${var}}" "${from}" last REVERSE)
  if(first EQUAL -1)
    message(FATAL_ERROR "${source} に「${from}」が見つかりません（week03_add_variant）")
  endif()
  if(NOT first EQUAL last)
    message(FATAL_ERROR "${source} に「${from}」が複数あります（week03_add_variant）")
  endif()
  string(REPLACE "${from}" "${to}" replaced "${${var}}")
  set(${var} "${replaced}" PARENT_SCOPE)
endfunction()

# ARGN を使わないのは，置き換える文字列に含まれる ; がリストの区切りとして分割されないようにするため
function(week03_add_variant program source variant from to)
  set(src "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${src}")
  file(READ "${src}" text)
  _week03_replace_once(text "${source}" "${from}" "${to}")
  if(ARGC GREATER 5)
    if(NOT ARGC EQUAL 7)
      message(FATAL_ERROR "week03_add_variant: 置き換え前と置き換え後は組で指定してください")
    endif()
    _week03_replace_once(text "${source}" "${ARGV5}" "${ARGV6}")
  endif()

  # 内容が変わったときだけ書き換える（毎回の再構成で再ビルドしないように）
  set(gen "${CMAKE_CURRENT_BINARY_DIR}/variants/${variant}/${source}")
  file(WRITE "${gen}.tmp" "${text}")
  configure_file("${gen}.tmp" "${gen}" COPYONLY)

  set(target "${program}_${variant}")
  add_executable(${target} "${gen}")
  softprac_apply_options(${target})
  set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${SOFTPRAC_WEEK}/variants"
    FOLDER "${SOFTPRAC_WEEK}/variants")
  add_test(NAME "${SOFTPRAC_WEEK}/${program}/variants/${variant}"
    COMMAND "${CMAKE_COMMAND}"
      "-DPROGRAM=$<TARGET_FILE:${target}>"
      "-DPROJECT_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
      "-DCASE=variants/${variant}"
      "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${program}/variants/${variant}"
      -P "${SOFTPRAC_RUN_TEST}")
endfunction()
