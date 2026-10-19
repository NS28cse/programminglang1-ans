# デバッグ題材 BugReverseWord（第7回）
# バグ入りの版は 8 文字以上の入力で配列の外へ書く（未定義動作）ので実行しない。テストは直した版だけ
softprac_add_program(BugReverseWord reverse_word.c)

softprac_add_variant(BugReverseWord reverse_word.c fixed
  "// デバッグ題材: 単語を逆順に表示する（第7回）"
  "// デバッグ題材: 単語を逆順に表示する（第7回）を直した版。配列に終端の 1 要素を足す。"
  "char word[MAX_WORD];"
  "char word[MAX_WORD + 1];")
