# 第2回 課題3 Exchange
# 本体に加えて，「別の値でも確認する」（a = -3, b = 8 と a = 5, b = 5）版と，
# 一時変数を使わない 2 文（a = b; b = a;）だけの誤った版をビルドしてテストする
softprac_add_program(Exchange exchange.c)

softprac_add_variant(Exchange exchange.c a_m3_b_8 "int a = 10" "int a = -3" "int b = 20" "int b = 8")
softprac_add_variant(Exchange exchange.c a_5_b_5 "int a = 10" "int a = 5" "int b = 20" "int b = 5")

# 2 文だけの版: temp を使う 3 行を a = b; b = a; に変え，各文の後の a と b を表示する（最後の after: 行は消す）
softprac_add_variant(Exchange exchange.c two_statements
  [[int temp = a;                   // 上書きされる前の a の値を保存する
    a = b;
    b = temp;]]
  [[a = b;
    printf("after a = b;  a=%d b=%d\n", a, b);
    b = a;
    printf("after b = a;  a=%d b=%d\n", a, b);]]
  [[    printf("after: a=%d b=%d\n", a, b);
]] "")
softprac_add_variant(Exchange exchange.c two_statements_a_m3_b_8
  "int a = 10" "int a = -3" "int b = 20" "int b = 8"
  [[int temp = a;                   // 上書きされる前の a の値を保存する
    a = b;
    b = temp;]]
  [[a = b;
    printf("after a = b;  a=%d b=%d\n", a, b);
    b = a;
    printf("after b = a;  a=%d b=%d\n", a, b);]]
  [[    printf("after: a=%d b=%d\n", a, b);
]] "")
softprac_add_variant(Exchange exchange.c two_statements_a_5_b_5
  "int a = 10" "int a = 5" "int b = 20" "int b = 5"
  [[int temp = a;                   // 上書きされる前の a の値を保存する
    a = b;
    b = temp;]]
  [[a = b;
    printf("after a = b;  a=%d b=%d\n", a, b);
    b = a;
    printf("after b = a;  a=%d b=%d\n", a, b);]]
  [[    printf("after: a=%d b=%d\n", a, b);
]] "")
