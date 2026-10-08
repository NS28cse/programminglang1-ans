# 第2回 課題3 Exchange
# 本体に加えて，「別の値でも確認する」（a = -3, b = 8 と a = 5, b = 5）版と，
# 一時変数を使わない 2 文（a = b; b = a;）だけの誤った版，代入の順序を誤った版をビルドしてテストする。
# 各版は先頭コメントの 2 行目も版の説明に置き換える
softprac_add_program(Exchange exchange.c)

set(exchange_desc "// a = b; で a の元の値が失われるので，先に temp へ保存してから交換する")

softprac_add_variant(Exchange exchange.c a_m3_b_8
  "${exchange_desc}"
  "// 初期値を a = -3, b = 8 に書き換えた版（temp を使った交換で a=8 b=-3 になる）"
  "int a = 10" "int a = -3" "int b = 20" "int b = 8")
softprac_add_variant(Exchange exchange.c a_5_b_5
  "${exchange_desc}"
  "// 初期値を a = 5, b = 5 に書き換えた版（2 つの値が等しいので，交換しても表示は同じ）"
  "int a = 10" "int a = 5" "int b = 20" "int b = 5")

# 2 文だけの版: temp を使う 3 行と，その後の空行・after: の行を，
# a = b; b = a; と各文の後の a と b の表示に置き換える（3 つの初期値で共通）
set(two_statements_desc
  "// 誤りの例: temp を使わず a = b; b = a; の 2 文だけで交換しようとした版（a も b も元の b の値になる）")
set(two_statements_old [[int temp = a;                   // 上書きされる前の a の値を保存する
    a = b;
    b = temp;

    printf("after: a=%d b=%d\n", a, b);]])
set(two_statements_new [[a = b;
    printf("after a = b;  a=%d b=%d\n", a, b);
    b = a;
    printf("after b = a;  a=%d b=%d\n", a, b);]])

softprac_add_variant(Exchange exchange.c two_statements
  "${exchange_desc}" "${two_statements_desc}"
  "${two_statements_old}" "${two_statements_new}")
softprac_add_variant(Exchange exchange.c two_statements_a_m3_b_8
  "${exchange_desc}" "${two_statements_desc}。初期値は a = -3, b = 8"
  "int a = 10" "int a = -3" "int b = 20" "int b = 8"
  "${two_statements_old}" "${two_statements_new}")
softprac_add_variant(Exchange exchange.c two_statements_a_5_b_5
  "${exchange_desc}" "${two_statements_desc}。初期値は a = 5, b = 5"
  "int a = 10" "int a = 5" "int b = 20" "int b = 5"
  "${two_statements_old}" "${two_statements_new}")

# 採点のポイントの「代入の順序の誤り」: temp = a; の後に b = a; としてしまい，b の元の値を失う版
softprac_add_variant(Exchange exchange.c wrong_order
  "${exchange_desc}"
  "// 誤りの例: temp = a; b = a; a = temp; の順にした版（b の元の値 20 を失い a=10 b=10 になる）"
  [[    a = b;
    b = temp;]]
  [[    b = a;                          // 誤り: b の元の値 20 がここで失われる
    a = temp;]])
