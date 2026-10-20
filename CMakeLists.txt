# プログラミング言語I・ソフトウェア演習I 解答
#
# weekNN/<プロジェクト名>/ の 1 フォルダ = 1 つの実行ファイル <プロジェクト名>
#   - フォルダ直下の *.c をまとめてビルドする（versions/ などのサブフォルダは含まない）
#   - 名前が _ で始まるフォルダはビルドしない（意図的にエラーを含むコード）
#   - フォルダに CMakeLists.txt があれば，それを使う（第12回のライブラリなど）
#   - 実行ファイルは <ビルド先>/bin/weekNN/<プロジェクト名>/ にでき，フォルダの input.txt などのデータファイルもそこへコピーする
cmake_minimum_required(VERSION 3.21)
project(softprac1_answers LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 授業と同じ警告設定（MSVC は警告レベル4 と UTF-8 のソース）
function(softprac_apply_options target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /utf-8)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(${target} PRIVATE m)   # math.h の関数（sqrt など）
  endif()
endfunction()

#   softprac_add_program(<名前> <ソース>...)
function(softprac_add_program name)
  set(out_dir "${CMAKE_BINARY_DIR}/bin/${SOFTPRAC_WEEK}/${name}")
  add_executable(${name} ${ARGN})
  softprac_apply_options(${name})
  # $<0:> は，Visual Studio のソリューションでも Debug/ などのサブフォルダを作らないためのもの
  # VS_DEBUGGER_WORKING_DIRECTORY: Visual Studio のソリューション（.sln）から実行したときも，同じフォルダを作業ディレクトリにする
  set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${out_dir}$<0:>" VS_DEBUGGER_WORKING_DIRECTORY "${out_dir}")
  # CONFIGURE_DEPENDS: プロジェクトフォルダにデータファイルを足すと，次のビルドで構成し直してコピーする
  # （ソース・設定と，コンパイラを直接使って作った a.out・*.exe など，第10回のプログラムが書き出すファイルはコピーしない）
  file(GLOB data_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "${SOFTPRAC_PROJECT_DIR}/*")
  foreach(f IN LISTS data_files)
    get_filename_component(fname "${f}" NAME)
    if(NOT fname MATCHES "(\\.c|\\.h|^CMakeLists\\.txt|^README.*|^run\\.args|^a\\.out|\\.exe|\\.obj|\\.o|\\.pdb|\\.ilk)$"
       AND NOT f MATCHES "/week10/(WriteSquares/squares.*\\.txt|WriteText/scores\\.txt|NumberFormats/numbers\\..*|Binary/bytes\\.bin)$")
      configure_file("${f}" "${out_dir}/${fname}" COPYONLY)
    endif()
  endforeach()
endfunction()

# CONFIGURE_DEPENDS: フォルダや .c を足すと，次のビルドで構成し直して加える
file(GLOB project_dirs LIST_DIRECTORIES true CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/week[0-9][0-9]/*")
list(SORT project_dirs)
foreach(dir IN LISTS project_dirs)
  get_filename_component(name "${dir}" NAME)
  get_filename_component(week_dir "${dir}" DIRECTORY)
  get_filename_component(SOFTPRAC_WEEK "${week_dir}" NAME)
  set(SOFTPRAC_PROJECT_DIR "${dir}")
  if(NOT IS_DIRECTORY "${dir}" OR name MATCHES "^[_.]")
    continue()
  elseif(EXISTS "${dir}/CMakeLists.txt")
    add_subdirectory("${dir}" "${CMAKE_BINARY_DIR}/projects/${SOFTPRAC_WEEK}/${name}")
  else()
    file(GLOB sources CONFIGURE_DEPENDS "${dir}/*.c" "${dir}/*.h")
    if(sources)
      softprac_add_program(${name} ${sources})
    endif()
  endif()
endforeach()
