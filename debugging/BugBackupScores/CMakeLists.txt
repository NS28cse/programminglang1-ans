# デバッグ題材 BugBackupScores（第13回）
# バグ入りの版は解放した領域を読み，同じ領域を 2 回解放する（未定義動作）ので実行しない。テストは直した版だけ
softprac_add_program(BugBackupScores main.c scores.c scores.h)

softprac_add_variant(BugBackupScores main.c fixed
  "// デバッグ題材: 点数の控え（第13回）"
  "// デバッグ題材: 点数の控え（第13回）を直した版。backup に別の領域を確保して中身をコピーする。"
  "    Scores backup = today;\n"
  [=[
    Scores backup;
    if (!scores_create(&backup, today.count)) {
        fprintf(stderr, "allocation failed\n");
        scores_destroy(&today);
        return 1;
    }
    for (size_t i = 0; i < today.count; ++i) {
        backup.data[i] = today.data[i];
    }
]=])
