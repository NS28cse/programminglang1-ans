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
#   - 置換の文字列には ; や [ も書ける（引数を 1 つずつ ARGV<n> で読むため）
#   - 同じフォルダの他の .c（main を持たないもの）も一緒にリンクし，フォルダをインクルードパスに加える
#     （分割コンパイルのプロジェクトでも，書き換えるファイルだけを指定すればよい）
#   - 期待する出力は <プロジェクト>/variants/tests/<ケース名>.out（.args/.in/.code なども同じ規則）
#     同じ版を複数の入力で試すときは <ケース名>--<名前>.out / .in / .args を並べる（実行ファイルは 1 つ）
#   - テスト名は weekNN/<プログラム名>/variant_<ケース名>
include_guard(GLOBAL)

function(softprac_add_variant base source case)
  set(src "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
  file(READ "${src}" text)
  math(EXPR n "${ARGC} - 3")
  math(EXPR odd "${n} % 2")
  if(n LESS_EQUAL 0 OR odd)
    message(FATAL_ERROR "softprac_add_variant(${base} ${case}): 置換前と置換後を組で指定してください")
  endif()
  math(EXPR last_index "${ARGC} - 1")
  foreach(i RANGE 3 ${last_index} 2)
    math(EXPR j "${i} + 1")
    set(old "${ARGV${i}}")
    set(new "${ARGV${j}}")
    string(FIND "${text}" "${old}" first)
    string(FIND "${text}" "${old}" last REVERSE)
    if(first EQUAL -1 OR NOT first EQUAL last)
      message(FATAL_ERROR "softprac_add_variant(${base} ${case}): ${source} に「${old}」がちょうど 1 回現れません")
    endif()
    string(REPLACE "${old}" "${new}" text "${text}")
  endforeach()

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

  # 同じフォルダの main を持たない .c（分割コンパイルの相手）も加える
  set(others "")
  file(GLOB siblings "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
  foreach(f IN LISTS siblings)
    get_filename_component(fname "${f}" NAME)
    if(fname STREQUAL source)
      continue()
    endif()
    file(STRINGS "${f}" has_main REGEX "^[ \t]*int[ \t]+main[ \t]*\\(")
    if(NOT has_main)
      list(APPEND others "${f}")
    endif()
  endforeach()

  add_executable(${name} "${gen}" ${others})
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  softprac_apply_options(${name})
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/variants/${SOFTPRAC_WEEK}"
    FOLDER "${SOFTPRAC_WEEK}/variants")

  # 期待値: variants/tests/<ケース>.out と，同じ版を別の入力で試す variants/tests/<ケース>--<名前>.out
  set(vdir "${CMAKE_CURRENT_SOURCE_DIR}/variants")
  file(GLOB outs CONFIGURE_DEPENDS "${vdir}/tests/${case}.out" "${vdir}/tests/${case}--*.out")
  if(NOT outs)
    message(FATAL_ERROR "softprac_add_variant(${base} ${case}): ${vdir}/tests/${case}.out がありません")
  endif()
  foreach(out IN LISTS outs)
    get_filename_component(tcase "${out}" NAME)
    string(REGEX REPLACE "\\.out$" "" tcase "${tcase}")
    add_test(NAME "${SOFTPRAC_WEEK}/${base}/variant_${tcase}"
      COMMAND "${CMAKE_COMMAND}"
        "-DPROGRAM=$<TARGET_FILE:${name}>"
        "-DPROJECT_DIR=${vdir}"
        "-DCASE=${tcase}"
        "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}/${tcase}"
        -P "${SOFTPRAC_RUN_TEST}")
  endforeach()
endfunction()
