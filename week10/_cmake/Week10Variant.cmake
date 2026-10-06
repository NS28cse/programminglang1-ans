# 第10回: 演習ページで段階的に書き換える前の版（途中の版）もビルドしてテストする補助関数
#
# フォルダのソースは最終版（CONTRIBUTING.md）。演習ページの「最初は w で実行」「講義の binary.c のまま」
# などの途中の版は，最終版のソースの一部を置き換えて生成し，別の実行ファイルとしてビルド・テストする。
# README に載せた途中の版のコードと実行結果は，この生成物と同じ内容。
#
#   week10_add_variant(<プログラム名> <ソース> <版の名前> <置換前の変数名> <置換後の変数名> [...])
#
#   - 置換の文字列は「変数名」で渡す（; を含むコード断片もリストとして分割されないように）
#   - <置換前> がソースにちょうど 1 回現れることを確かめてから置き換える（ソースを直したら構成エラーで気付ける）
#   - テストは <プロジェクト>/variants/<版の名前>/tests/<ケース>.out など（形式は tests/ と同じ）。
#     作業フォルダへは variants/<版の名前>/ のデータファイルと <ケース>.setup/ がコピーされる
#   - 実行ファイル名は <プログラム名>_<版の名前>，テスト名は weekNN/<プログラム名>/<版の名前>/<ケース>
include_guard(GLOBAL)

function(week10_add_variant base source variant)
  set(src "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${src}")
  file(READ "${src}" text)

  set(names ${ARGN})
  list(LENGTH names n)
  math(EXPR odd "${n} % 2")
  if(n EQUAL 0 OR odd)
    message(FATAL_ERROR "week10_add_variant(${base} ${variant}): 置換前と置換後の変数名を組で指定してください")
  endif()
  while(names)
    list(POP_FRONT names old_var new_var)
    set(old "${${old_var}}")
    set(new "${${new_var}}")
    string(FIND "${text}" "${old}" first)
    string(FIND "${text}" "${old}" last REVERSE)
    if(first EQUAL -1 OR NOT first EQUAL last)
      message(FATAL_ERROR "week10_add_variant(${base} ${variant}): ${source} に ${old_var} の文字列がちょうど 1 回現れません")
    endif()
    string(REPLACE "${old}" "${new}" text "${text}")
  endwhile()

  set(gen "${CMAKE_CURRENT_BINARY_DIR}/variants/${variant}/${source}")
  file(CONFIGURE OUTPUT "${gen}" CONTENT "${text}" @ONLY)

  set(name "${base}_${variant}")
  get_property(used GLOBAL PROPERTY SOFTPRAC_PROGRAMS)
  if(name IN_LIST used)
    message(FATAL_ERROR "プログラム名 ${name} が重複しています")
  endif()
  set_property(GLOBAL APPEND PROPERTY SOFTPRAC_PROGRAMS ${name})

  add_executable(${name} "${gen}")
  softprac_apply_options(${name})
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/variants/${SOFTPRAC_WEEK}"
    FOLDER "${SOFTPRAC_WEEK}/variants")

  set(vdir "${CMAKE_CURRENT_SOURCE_DIR}/variants/${variant}")
  file(GLOB outs CONFIGURE_DEPENDS "${vdir}/tests/*.out")
  if(NOT outs)
    message(FATAL_ERROR "week10_add_variant(${base} ${variant}): ${vdir}/tests/*.out がありません")
  endif()
  foreach(out IN LISTS outs)
    get_filename_component(case "${out}" NAME_WE)
    add_test(NAME "${SOFTPRAC_WEEK}/${base}/${variant}/${case}"
      COMMAND "${CMAKE_COMMAND}"
        "-DPROGRAM=$<TARGET_FILE:${name}>"
        "-DPROJECT_DIR=${vdir}"
        "-DCASE=${case}"
        "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}/${case}"
        -P "${SOFTPRAC_RUN_TEST}")
  endforeach()
endfunction()
