# 第13回 発展2 StorageCount
# 本体（static int count = 0;）に加えて，「3 種類を比較する」の残り 2 つの書き方をビルドしてテストする
softprac_add_program(StorageCount count.c)

set(storage_header [=[// 関数内の static int count は静的記憶期間を持ち，プログラム開始前に 1 度だけ 0 に初期化される。
// そのため呼び出しの間も値が保持され，1，2，3 と表示される。ヒープは使わないので free もしない。]=])
set(storage_decl [=[static int count = 0;   // この static は静的記憶期間（名前は関数内だけで使える）]=])

# static を外した通常の局所変数（自動記憶域）
softprac_add_variant(StorageCount count.c auto_count
  "${storage_header}"
  [=[// （3 種類の比較：static を外して int count = 0; に変えた版。1，1，1 と表示される）]=]
  "${storage_decl}"
  [=[int count = 0;   // static なし：自動記憶域。呼ぶたびに作られ 0 で初期化される]=])

# static int count; の後に，文として count = 0; を書く（呼ぶたびに代入される）
softprac_add_variant(StorageCount count.c static_assign
  "${storage_header}"
  [=[// （3 種類の比較：static int count; の後に文として count = 0; を書いた版。1，1，1 と表示される）]=]
  "${storage_decl}"
  [=[static int count;   // 静的記憶期間だが，次の文で呼ぶたびに 0 を代入する
    count = 0;]=])
