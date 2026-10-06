# 第7回 課題1 Echo
# 本体（講義の echo.c）に加えて，putchar(ch) の前に putchar('/') とその戻り値の確認を加えた版をテストする。
# 置換文字列に ; を書けないため，同じ動作になる「||」でつないだ 1 行の条件に置き換える
# （'/' の出力に失敗したら ch は出力せずにエラー。README の版と同じ動作）
softprac_add_program(Echo echo.c)

foreach(case slash_ab slash_two_lines slash_newline_only slash_empty)
  softprac_add_variant(Echo echo.c ${case}
    "if (putchar(ch) == EOF) {" "if (putchar('/') == EOF || putchar(ch) == EOF) {")
endforeach()
