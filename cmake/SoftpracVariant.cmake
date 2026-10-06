# 「値を変えて確かめる」の版（ソースの一部を置き換えた版）をビルドしてテストする補助関数
#
# 入力を使わない回（第1〜5回など）では，演習ページの「初期値を 0 に変える」などの確認は
# ソースを書き換えて行う。ここでは学生と同じ書き換えを CMake が行い，別の実行ファイルとして
# ビルド・テストする（フォルダのソースは最終版のまま変えない）。
#
#   softprac_add_variant(<プログラム名> <ソース> <ケース名> <置換前> <置換後> [<置換前> <置換後>]...)
#
#   - <ソース> の中で <置換前> がちょうど 1 回現れることを確認してから <置換後> に置き換える
#     （ソースを直して置換前の文字列がなくなったら，構成の段階でエラーにして気付けるようにする）
#   - 置換の文字列には ; を含めない（CMake のリストの区切りになるため）
#   - 期待する出力は <プロジェクト>/variants/tests/<ケース名>.out（.args/.in/.code なども同じ規則）
#   - テスト名は weekNN/<プログラム名>/variant_<ケース名>
include_guard(GLOBAL)

function(softprac_add_variant base source case)
  set(src "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
  file(READ "${src}" text)
  set(pairs ${ARGN})
  list(LENGTH pairs n)
  math(EXPR odd "${n} % 2")
  if(n EQUAL 0 OR odd)
    message(FATAL_ERROR "softprac_add_variant(${base} ${case}): 置換前と置換後を組で指定してください")
  endif()
  while(pairs)
    list(POP_FRONT pairs old new)
    string(FIND "${text}" "${old}" first)
    string(FIND "${text}" "${old}" last REVERSE)
    if(first EQUAL -1 OR NOT first EQUAL last)
      message(FATAL_ERROR "softprac_add_variant(${base} ${case}): ${source} に「${old}」がちょうど 1 回現れません")
    endif()
    string(REPLACE "${old}" "${new}" text "${text}")
  endwhile()

  # 書き換えた版を作る（内容が同じなら書き直さない）。元のソースが変わったら構成し直す
  set(gen "${CMAKE_CURRENT_BINARY_DIR}/variants/${case}/${source}")
  set(old_text "")
  if(EXISTS "${gen}")
    file(READ "${gen}" old_text)
  endif()
  if(NOT old_text STREQUAL text)
    file(WRITE "${gen}" "${text}")
  endif()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${src}")

  set(name "${base}_${case}")
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

  set(vdir "${CMAKE_CURRENT_SOURCE_DIR}/variants")
  if(NOT EXISTS "${vdir}/tests/${case}.out")
    message(FATAL_ERROR "softprac_add_variant(${base} ${case}): ${vdir}/tests/${case}.out がありません")
  endif()
  add_test(NAME "${SOFTPRAC_WEEK}/${base}/variant_${case}"
    COMMAND "${CMAKE_COMMAND}"
      "-DPROGRAM=$<TARGET_FILE:${name}>"
      "-DPROJECT_DIR=${vdir}"
      "-DCASE=${case}"
      "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}"
      -P "${SOFTPRAC_RUN_TEST}")
endfunction()
