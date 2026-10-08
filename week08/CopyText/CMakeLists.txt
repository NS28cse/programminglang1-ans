# 第8回 課題3 CopyText
# 本体（添字なしのポインタ版）。途中の版・読む版を，コピー処理を書き換えた版としてテストする（生成ソースの先頭コメントも版に合わせる）
# （どちらも表のすべてのケースで本体と同じ表示になること）
#   index      … 添字版（strlen の結果を length に保存し，for で終端まで添字でコピーする）
#   short_form … さらに短い表記 while ((*dst++ = *src++) != '\0') { }
softprac_add_program(CopyText copy_text.c)

set(pointer_loop [=[    /* 1 文字代入してから，代入した値が終端か調べる．終端もコピーしてから終わる */
    while ((*dst = *src) != '\0') {
        ++dst;
        ++src;
    }]=])

softprac_add_variant(CopyText copy_text.c index
  "（添字なしのポインタ版）" "（添字版．書き換え版 index）"
  "    if (strlen(src) >= capacity) {"
  [=[    size_t length = strlen(src);
    if (length >= capacity) {]=]
  "${pointer_loop}"
  [=[    /* i == length で終端もコピーする */
    for (size_t i = 0; i <= length; ++i) {
        dst[i] = src[i];
    }]=])
softprac_add_variant(CopyText copy_text.c short_form
  "（添字なしのポインタ版）" "（さらに短い表記の版．書き換え版 short_form）"
  "${pointer_loop}"
  [=[    /* 代入 → 判定 → 更新を条件式の中で行う．本体は空 */
    while ((*dst++ = *src++) != '\0') {
    }]=])
