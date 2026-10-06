# 第6回: 「初期値・容量を変えて確かめる」小問を自動テストにするための補助関数
#
# 第6回の文字列はソース内で用意し，キーボードからは読み込まない。そのため「容量を 10 から 9，8 へ
# 変える」「初期値を "" に変える」といった確認は，学生と同じようにソースを書き換えた別の実行ファイルで
# 行う。ここでは CMake がその書き換えを行い，ビルドフォルダに生成した版をビルド・テストする
# （フォルダのソースは最終版のまま変えない）。
#
#   week06_add_variant(<プログラム名> <ソース> <ケース名> <置換前> <置換後> [<置換前> <置換後>]...)
#
#   - <置換前> がソースにちょうど 1 回現れることを確かめてから置き換える
#     （ソースを直して置換前の文字列がなくなったら，構成の段階でエラーにして気付けるようにする）
#   - 期待する出力は <プロジェクト>/variants/tests/<ケース名>.out（.err/.code なども tests/ と同じ規則）
#   - 実行ファイル名は <プログラム名>_<ケース名>，テスト名は week06/<プログラム名>/variant_<ケース名>
#   - 置換の文字列に ; は使えない。"@AZ[" のような対にならない [ も扱えるよう，
#     引数はリストにせず ARGV<n> で 1 つずつ読む
#   - 生成した版は Visual Studio の起動構成（tools/gen_launch_vs.py）には載らない（テスト専用）
include_guard(GLOBAL)

function(week06_add_variant program source case)
  set(src "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${src}")
  file(READ "${src}" text)

  math(EXPR rest "${ARGC} - 3")
  math(EXPR odd "${rest} % 2")
  if(rest EQUAL 0 OR odd)
    message(FATAL_ERROR "week06_add_variant(${program} ${case}): 置換前と置換後を組で指定してください")
  endif()
  set(i 3)
  while(i LESS ARGC)
    math(EXPR j "${i} + 1")
    set(old "${ARGV${i}}")
    set(new "${ARGV${j}}")
    string(FIND "${text}" "${old}" first)
    string(FIND "${text}" "${old}" last REVERSE)
    if(first EQUAL -1 OR NOT first EQUAL last)
      message(FATAL_ERROR "week06_add_variant(${program} ${case}): ${source} に「${old}」がちょうど 1 回現れません")
    endif()
    string(REPLACE "${old}" "${new}" text "${text}")
    math(EXPR i "${i} + 2")
  endwhile()

  # 書き換えた版を作る（内容が同じなら書き直さず，再ビルドを避ける）
  set(gen "${CMAKE_CURRENT_BINARY_DIR}/variants/${case}/${source}")
  file(WRITE "${gen}.tmp" "${text}")
  configure_file("${gen}.tmp" "${gen}" COPYONLY)

  set(name "${program}_${case}")
  get_property(used GLOBAL PROPERTY SOFTPRAC_PROGRAMS)
  if(name IN_LIST used)
    message(FATAL_ERROR "プログラム名 ${name} が重複しています")
  endif()
  set_property(GLOBAL APPEND PROPERTY SOFTPRAC_PROGRAMS ${name})

  add_executable(${name} "${gen}")
  softprac_apply_options(${name})
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${SOFTPRAC_WEEK}/variants"
    FOLDER "${SOFTPRAC_WEEK}/variants")

  set(vdir "${CMAKE_CURRENT_SOURCE_DIR}/variants")
  if(NOT EXISTS "${vdir}/tests/${case}.out")
    message(FATAL_ERROR "week06_add_variant(${program} ${case}): ${vdir}/tests/${case}.out がありません")
  endif()
  add_test(NAME "${SOFTPRAC_WEEK}/${program}/variant_${case}"
    COMMAND "${CMAKE_COMMAND}"
      "-DPROGRAM=$<TARGET_FILE:${name}>"
      "-DPROJECT_DIR=${vdir}"
      "-DCASE=${case}"
      "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}"
      -P "${SOFTPRAC_RUN_TEST}")
endfunction()
