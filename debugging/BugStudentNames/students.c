// デバッグ題材: 名簿を読む（第11回）
// input.txt の名前（1 行 1 人，MAX_NAME 文字まで，MAX_STUDENTS 人まで）を Student の配列へ読み込み，
// 読み終えてから番号と名前を表示する。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

enum { MAX_STUDENTS = 5, MAX_NAME = 20 };

typedef struct {
    int number;
    char *name;
} Student;

int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        return 1;
    }

    Student students[MAX_STUDENTS];
    char line[MAX_NAME + 2];   // 名前 + 改行 + 終端
    int count = 0;
    while (count < MAX_STUDENTS && fgets(line, sizeof line, fp) != NULL) {
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[--length] = '\0';
        }
        if (length > MAX_NAME) {
            fprintf(stderr, "name too long\n");
            fclose(fp);
            return 1;
        }
        students[count].number = count + 1;
        students[count].name = line;
        ++count;
    }
    fclose(fp);

    for (int i = 0; i < count; ++i) {
        printf("%d %s\n", students[i].number, students[i].name);
    }
    return 0;
}
