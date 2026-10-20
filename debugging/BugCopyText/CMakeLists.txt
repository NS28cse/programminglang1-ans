# デバッグ題材 BugCopyText（第8回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugCopyText copy_text.c)

softprac_add_variant(BugCopyText copy_text.c fixed
  "// デバッグ題材: 文字列をコピーする（第8回）"
  "// デバッグ題材: 文字列をコピーする（第8回）を直した版。ループの後で終端もコピーする。"
  [=[
        ++src;
    }
}]=]
  [=[
        ++src;
    }
    *dst = '\0';
}]=])
