// 第9回 発展1　長さが異なる行を扱う（RaggedRows / ragged_rows.c）
// 配列本体（row0, row1），先頭を集めたポインタ配列（rows），長さの配列（lengths）の3種類を区別する。
// show_original が演習ページの表示，show_swapped が長さも一緒に交換した版，以降は平均と二重ポインタの別の使い方。
#include <stdio.h>

enum { ROW_COUNT = 2 };

/* p[r] の先頭から lengths[r] 個の合計を行ごとに表示する。長さは型に含まれないので別に受け取る */
void print_sums(int **p, const int lengths[], int n)
{
    for (int r = 0; r < n; ++r) {
        int sum = 0;
        for (int c = 0; c < lengths[r]; ++c) {
            sum += p[r][c];
        }
        printf("row%d sum=%d\n", r, sum);
    }
}

/* 演習ページの例：p[1][0] の変更は row1[0] に反映される（内容はコピーされていない） */
void show_original(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int *rows[] = {row0, row1};
    int lengths[] = {3, 2};
    int **p = rows;
    print_sums(p, lengths, ROW_COUNT);
    p[1][0] = 40;
    printf("original=%d\n", row1[0]);
}

/* 反復処理の前に rows と lengths を一組で交換した版 */
void show_swapped(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int *rows[] = {row0, row1};
    int lengths[] = {3, 2};
    int **p = rows;

    int *temp_row = rows[0];
    rows[0] = rows[1];
    rows[1] = temp_row;
    int temp_length = lengths[0];  /* 長さも交換しないと，2要素の row1 を長さ3で読んでしまう */
    lengths[0] = lengths[1];
    lengths[1] = temp_length;

    printf("swapped rows and lengths:\n");
    print_sums(p, lengths, ROW_COUNT);
    p[1][0] = 40;  /* p[1] は row0 を指しているので row0[0] が変わる */
    printf("original=%d\n", row1[0]);
    printf("row0[0]=%d\n", row0[0]);
}

/* 全要素の平均と，行平均の単純な平均の違い */
void show_means(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int *rows[] = {row0, row1};
    int lengths[] = {3, 2};
    int total = 0;
    int count = 0;
    double sum_of_means = 0.0;
    printf("means:\n");
    for (int r = 0; r < ROW_COUNT; ++r) {
        int sum = 0;
        for (int c = 0; c < lengths[r]; ++c) {
            sum += rows[r][c];
        }
        printf("row%d mean=%.2f\n", r, (double)sum / lengths[r]);
        total += sum;
        count += lengths[r];
        sum_of_means += (double)sum / lengths[r];
    }
    printf("all elements: %d / %d = %.2f\n", total, count, (double)total / count);
    printf("mean of row means = %.2f\n", sum_of_means / ROW_COUNT);
}

/* 二重ポインタの別の使い方1：p が指すのはポインタ変数 animal の1個だけ（p を進めない） */
void show_pointer_to_pointer(void)
{
    const char *animal = "dog";
    const char **p = &animal;
    printf("%s\n", *p);
    *p = "cat";  /* animal の指す先が変わる。"dog" の文字は変わらない */
    printf("%s\n", animal);
}

/* 二重ポインタの別の使い方2：各要素は1文字だけを指す（終端はないので %s に渡さない） */
void show_letters(void)
{
    char first = 'a', second = 'b';
    char *letters[] = {&first, &second};
    char **p = letters;
    for (int i = 0; i < 2; ++i) {
        printf("%c\n", *p[i]);
    }
}

int main(void)
{
    show_original();
    show_swapped();
    show_means();
    show_pointer_to_pointer();
    show_letters();
    return 0;
}
