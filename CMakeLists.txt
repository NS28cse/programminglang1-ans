# プログラミング言語I・ソフトウェア演習I 解答リポジトリ
#
# 規則（詳しくは README.md）
#   weekNN/<プロジェクト名>/ の 1 フォルダ = Visual Studio の 1 プロジェクト = 1 つの実行ファイル
#   - フォルダ内の *.c をすべてまとめて <プロジェクト名>.exe を作る（分割コンパイルもそのまま動く）
#   - フォルダに CMakeLists.txt があれば，自動の規則の代わりにそれを使う（ライブラリを作る回など）
#   - 名前が _ で始まるフォルダはビルドしない（意図的にエラーを含むコードの置き場所）
#   - tests/ フォルダがあれば，その内容を CTest のテストとして登録する（cmake/RunTest.cmake）
cmake_minimum_required(VERSION 3.21)
project(softprac1_answers LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SOFTPRAC_WERROR   "警告をエラーとして扱う（CI 用）" OFF)
option(SOFTPRAC_SANITIZE "AddressSanitizer/UBSan を有効にする（GCC/Clang のみ，CI 用）" OFF)
set(SOFTPRAC_WEEKS "" CACHE STRING "ビルドする回を限定する（例: week01;week02）。空ならすべて")

enable_testing()

set(SOFTPRAC_RUN_TEST "${CMAKE_CURRENT_SOURCE_DIR}/cmake/RunTest.cmake")

# 授業と同じ警告設定（警告レベル4，UTF-8 ソース）を 1 つのターゲットに付ける
function(softprac_apply_options target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /utf-8)
    if(SOFTPRAC_WERROR)
      target_compile_options(${target} PRIVATE /WX)
    endif()
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    if(SOFTPRAC_WERROR)
      target_compile_options(${target} PRIVATE -Werror)
    endif()
    if(SOFTPRAC_SANITIZE)
      target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
      target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
  endif()
endfunction()

# 実行ファイルを 1 つ作る。名前はプロジェクト名（= フォルダ名）
#   softprac_add_program(<名前> <ソース>...)
function(softprac_add_program name)
  get_property(used GLOBAL PROPERTY SOFTPRAC_PROGRAMS)
  if(name IN_LIST used)
    message(FATAL_ERROR "プロジェクト名 ${name} が重複しています（${CMAKE_CURRENT_SOURCE_DIR}）。"
                        "実行ファイル名を一意にするため，フォルダ名を変えてください。")
  endif()
  set_property(GLOBAL APPEND PROPERTY SOFTPRAC_PROGRAMS ${name})

  add_executable(${name} ${ARGN})
  softprac_apply_options(${name})
  # 実行ファイルは out/build/<プリセット>/bin/weekNN/ にまとめる
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${SOFTPRAC_WEEK}"
    VS_DEBUGGER_WORKING_DIRECTORY "${SOFTPRAC_PROJECT_DIR}"
    FOLDER "${SOFTPRAC_WEEK}")
  softprac_add_tests(${name} "${SOFTPRAC_PROJECT_DIR}")
endfunction()

# <プロジェクト>/tests/<ケース>.out があれば CTest に登録する
#   <ケース>.args  コマンドライン引数（1 行に 1 つ。空行は空文字列の引数）
#   <ケース>.in    標準入力
#   <ケース>.out   期待する標準出力（必須。改行コードの違いは無視）
#   <ケース>.err   期待する標準エラー出力（任意）
#   <ケース>.code  期待する終了コード（省略時 0）
#   <ケース>.files/ 実行後に作業フォルダにあるべきファイル（バイト単位で比較）
# プログラムは「プロジェクトフォルダのデータファイルをコピーした作業フォルダ」で実行される
function(softprac_add_tests name project_dir)
  file(GLOB outs CONFIGURE_DEPENDS "${project_dir}/tests/*.out")
  foreach(out IN LISTS outs)
    get_filename_component(case "${out}" NAME_WE)
    add_test(NAME "${SOFTPRAC_WEEK}/${name}/${case}"
      COMMAND "${CMAKE_COMMAND}"
        "-DPROGRAM=$<TARGET_FILE:${name}>"
        "-DPROJECT_DIR=${project_dir}"
        "-DCASE=${case}"
        "-DWORK_DIR=${CMAKE_BINARY_DIR}/testwork/${SOFTPRAC_WEEK}/${name}/${case}"
        -P "${SOFTPRAC_RUN_TEST}")
  endforeach()
endfunction()

# weekNN/ を走査してプロジェクトを登録する
file(GLOB week_dirs LIST_DIRECTORIES true RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
     "${CMAKE_CURRENT_SOURCE_DIR}/week[0-9][0-9]")
list(SORT week_dirs)
foreach(week IN LISTS week_dirs)
  if(SOFTPRAC_WEEKS AND NOT week IN_LIST SOFTPRAC_WEEKS)
    continue()
  endif()
  set(SOFTPRAC_WEEK "${week}")
  file(GLOB project_dirs LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/${week}/*")
  list(SORT project_dirs)
  foreach(dir IN LISTS project_dirs)
    get_filename_component(project_name "${dir}" NAME)
    if(NOT IS_DIRECTORY "${dir}" OR project_name MATCHES "^[_.]")
      continue()
    endif()
    set(SOFTPRAC_PROJECT_DIR "${dir}")
    if(EXISTS "${dir}/CMakeLists.txt")
      add_subdirectory("${dir}" "${CMAKE_BINARY_DIR}/projects/${week}/${project_name}")
    else()
      file(GLOB sources CONFIGURE_DEPENDS "${dir}/*.c" "${dir}/*.h")
      if(sources)
        softprac_add_program(${project_name} ${sources})
      endif()
    endif()
  endforeach()
endforeach()
