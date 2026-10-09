# 第11回 課題4 CopyMembers
# 本体に加えて，先頭 1 文字ではなく文字列全体を "fuga" へ置き換える版をテストする。
# 各版は先頭コメントの説明の行と書き換えた行のコメントを，その版の内容に合わせて置き換える
softprac_add_program(CopyMembers copy_members.c)

softprac_add_variant(CopyMembers copy_members.c replace_fuga
  "// 配列メンバ（内部に文字を持つ）とポインタメンバ（外の配列を指す）のコピーを比べる。"
  "// 先頭 1 文字を 'H' にする 2 か所を，文字列全体（終端まで）を \"fuga\" へコピーする for に書き換えた版"
  "    a1.text[0] = 'H'; // a1 の内部配列だけが変わる"
  [=[    const char replacement[] = "fuga"; // 終端を含めて 5 要素
    for (size_t i = 0; i < sizeof replacement; ++i) { // 終端までコピーする
        a1.text[i] = replacement[i]; // a1 の内部配列だけが変わる
    }]=]
  "    p1.text[0] = 'H'; // 共有している buffer を変更するので p2 からも見える"
  [=[    for (size_t i = 0; i < sizeof replacement; ++i) { // 終端までコピーする
        buffer[i] = replacement[i]; // 共有している buffer を変更するので p2 からも見える
    }]=])
