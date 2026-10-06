# 第4回用: 固定値を書き換えた版（バリアント）をビルドしてテストに登録する
#
# 第4回の演習は入力関数を使わず，「ソース内の初期値を 1 か所変えてビルド・実行する」ことで
# 境界の値を確かめる。その手順をそのまま自動化するため，ソースの文字列を置き換えたコピーを
# ビルドフォルダに作り，別の実行ファイル <プロジェクト名>_<名前> としてビルドする。
# 学生が開くプロジェクト（softprac_add_program で作る本体）には影響しない。
#
#   week04_add_variant(<名前> <ソース> <期待値のケース> [<置換前> <置換後>]...)
#
#   <名前>            バリアントの名前。実行ファイルは <プロジェクト名>_<名前>，
#                     テスト名は weekNN/<プロジェクト名>/<名前>
#   <ソース>          プロジェクトフォルダからの相対パス（fee.c，versions/powers_while.c など）
#   <期待値のケース>   tests/ からの相対パス（拡張子なし）。tests/<ケース>.out と比べる
#   <置換前> <置換後>  ソース中の文字列の置き換え。置換前はソース中にちょうど 1 回現れること
#                     （CMake のリストを壊さないよう，セミコロンは含めない）
function(week04_add_variant name source expect)
  get_filename_component(project_name "${SOFTPRAC_PROJECT_DIR}" NAME)
  get_filename_component(source_name "${source}" NAME)
  set(src "${SOFTPRAC_PROJECT_DIR}/${source}")
  set(target "${project_name}_${name}")
  if(NOT EXISTS "${src}")
    message(FATAL_ERROR "${target}: ソース ${src} がありません")
  endif()
  if(NOT EXISTS "${SOFTPRAC_PROJECT_DIR}/tests/${expect}.out")
    message(FATAL_ERROR "${target}: 期待値 tests/${expect}.out がありません")
  endif()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${src}")

  file(READ "${src}" text)
  set(pairs ${ARGN})
  list(LENGTH pairs count)
  math(EXPR odd "${count} % 2")
  if(odd)
    message(FATAL_ERROR "${target}: 置換前と置換後は組で指定してください")
  endif()
  while(pairs)
    list(POP_FRONT pairs old new)
    string(LENGTH "${old}" old_length)
    string(FIND "${text}" "${old}" pos)
    if(pos EQUAL -1)
      message(FATAL_ERROR "${target}: 「${old}」が ${source} にありません")
    endif()
    math(EXPR rest_begin "${pos} + ${old_length}")
    string(SUBSTRING "${text}" ${rest_begin} -1 rest)
    string(FIND "${rest}" "${old}" pos2)
    if(NOT pos2 EQUAL -1)
      message(FATAL_ERROR "${target}: 「${old}」が ${source} に複数あります")
    endif()
    string(REPLACE "${old}" "${new}" text "${text}")
  endwhile()

  # 内容が変わったときだけ書き出す（不要な再ビルドを避ける）
  set(out "${CMAKE_CURRENT_BINARY_DIR}/variants/${name}/${source_name}")
  set(old_text "")
  if(EXISTS "${out}")
    file(READ "${out}" old_text)
  endif()
  if(NOT "${old_text}" STREQUAL "${text}")
    file(WRITE "${out}" "${text}")
  endif()

  add_executable(${target} "${out}")
  softprac_apply_options(${target})
  set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${SOFTPRAC_WEEK}/variants"
    FOLDER "${SOFTPRAC_WEEK}/variants")
  add_test(NAME "${SOFTPRAC_WEEK}/${project_name}/${name}"
    COMMAND "${CMAKE_COMMAND}"
      "-DPROGRAM=$<TARGET_FILE:${target}>"
      "-DPROJECT_DIR=${SOFTPRAC_PROJECT_DIR}"
      "-DCASE=${expect}"
      "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${project_name}/${name}"
      -P "${SOFTPRAC_RUN_TEST}")
endfunction()
