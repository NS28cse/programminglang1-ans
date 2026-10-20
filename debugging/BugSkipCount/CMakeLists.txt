# デバッグ題材 BugSkipCount（第4回）
# バグ入りの版は終わらない（3 で止まり続ける）ので，テストは直した版だけ（variants/tests/）
softprac_add_program(BugSkipCount skip_count.c)

softprac_add_variant(BugSkipCount skip_count.c fixed
  "// デバッグ題材: 3 の倍数を飛ばす（第4回）"
  "// デバッグ題材: 3 の倍数を飛ばす（第4回）を直した版。continue の前でも i を更新する。"
  [=[
            continue;]=]
  [=[
            ++i;
            continue;]=])
