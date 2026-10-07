// 第9回 発展2　型の説明（ArrayTypes / array_types.c。演習ページに名前の指定がないため解答用に命名）
// 型は「警告なしで初期化できる変数」で確かめ，sizeof は処理系依存のバイト数ではなく式との比較（1 なら成り立つ）で表示する。
#include <stdio.h>

int main(void)
{
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int *rows[2] = {a[0], a[1]};  // ポインタ2個。行の内容はコピーしない

    // sizeof は何を数えるか
    printf("sizeof a == 2 * 3 * sizeof(int): %d\n", sizeof a == 2 * 3 * sizeof(int));
    printf("sizeof rows == 2 * sizeof(int *): %d\n", sizeof rows == 2 * sizeof(int *));
    printf("sizeof a[0] == 3 * sizeof(int): %d\n", sizeof a[0] == 3 * sizeof(int));
    printf("sizeof rows[0] == sizeof(int *): %d\n", sizeof rows[0] == sizeof(int *));

    // 各式の型：次の初期化はどれも型が一致するので警告が出ない
    int (*row_ptr)[3] = a + 0;      // 1行（int 3個）を1単位とするポインタ
    int *int_ptr = a[0] + 0;        // int 1個を1単位とするポインタ
    int (*whole)[2][3] = &a;        // 配列全体を指す
    int (*first_row)[3] = &a[0];    // 1行を指す
    int *first_int = &a[0][0];      // 整数1個を指す
    int (*q)[3] = a;
    int (**qq)[3] = &q;             // q というポインタ変数自身を指す
    int **pp = rows;                // ポインタ配列なら int ** で指せる

    // +1 で進む単位（差は要素数で表される）
    printf("(row_ptr + 1) - row_ptr = %td, sizeof *row_ptr == 3 * sizeof(int): %d\n",
           (row_ptr + 1) - row_ptr, sizeof *row_ptr == 3 * sizeof(int));
    printf("(int_ptr + 1) - int_ptr = %td, sizeof *int_ptr == sizeof(int): %d\n",
           (int_ptr + 1) - int_ptr, sizeof *int_ptr == sizeof(int));
    printf("sizeof *whole == sizeof a: %d\n", sizeof *whole == sizeof a);
    printf("sizeof *first_row == 3 * sizeof(int): %d\n", sizeof *first_row == 3 * sizeof(int));
    printf("sizeof *first_int == sizeof(int): %d\n", sizeof *first_int == sizeof(int));
    printf("*qq == a: %d, (*qq)[1][2] = %d\n", *qq == a, (*qq)[1][2]);

    // 同じ位置から始まるが型は違う（比較のため void * へ変換）
    // &a と &a[0]，&a[0] と &a[0][0]，a + 0 と a[0] + 0，a + 0 と &a の 4 組を比べる
    printf("same start: %d %d %d %d\n", (void *)whole == (void *)first_row,
           (void *)first_row == (void *)first_int, (void *)row_ptr == (void *)int_ptr,
           (void *)row_ptr == (void *)whole);
    printf("&q is not &a: (void *)qq == (void *)whole is %d\n", (void *)qq == (void *)whole);

    // 同じ添字でも途中に何があるかが違う
    printf("a[1][2]=%d rows[1][2]=%d pp[1][2]=%d\n", a[1][2], rows[1][2], pp[1][2]);

    // 一次元として扱うなら最初から一次元配列を宣言し，flat[r * 3 + c] で読む
    int flat[6] = {1, 2, 3, 4, 5, 6};
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 3; ++c) {
            printf(" flat[%d]=%d", r * 3 + c, flat[r * 3 + c]);
        }
        printf("\n");
    }
    return 0;
}
