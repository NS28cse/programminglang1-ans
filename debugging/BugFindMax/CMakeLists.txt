# デバッグ題材 BugFindMax（第9回）
# tests/ はバグ入りの版の出力（症状），variants/tests/ は直した版の出力
softprac_add_program(BugFindMax find_max.c)

softprac_add_variant(BugFindMax find_max.c fixed
  "// デバッグ題材: 最大の要素の場所を返す（第9回）"
  "// デバッグ題材: 最大の要素の場所を返す（第9回）を直した版。呼び出し元のポインタ変数の場所（int **）を受け取る。"
  "int find_max(int a[], int n, int *out)"
  "int find_max(int a[], int n, int **out)"
  [=[
    out = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > *out) {
            out = &a[i];
        }
    }]=]
  [=[
    *out = &a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > **out) {
            *out = &a[i];
        }
    }]=]
  "find_max(scores, COUNT, best)"
  "find_max(scores, COUNT, &best)")
