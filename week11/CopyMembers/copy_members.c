// 第11回 課題4　配列メンバとポインタメンバを比較する（CopyMembers / copy_members.c）
// 配列メンバ（内部に文字を持つ）とポインタメンバ（外の配列を指す）のコピーを比べる。
#include <stdio.h>
typedef struct {
    char text[7]; // 6 バイトまでの文字列と終端を構造体の中に持つ
} TextArray;
typedef struct {
    char *text; // 文字列本体は持たず，main の配列を借りて指す
} TextPointer;
int main(void)
{
    TextArray a1 = {"hoge"};
    TextArray a2 = a1; // 7 要素の配列ごとコピーされ，a2 は自分の配列を持つ
    a1.text[0] = 'H'; // a1 の内部配列だけが変わる
    printf("array=%s %s\n", a1.text, a2.text);

    char buffer[] = "hoge"; // p1・p2 が共有する文字列（main の終わりまで有効）
    char other[] = "fuga";
    TextPointer p1 = {0};
    p1.text = buffer;
    TextPointer p2 = p1; // アドレスだけがコピーされ，同じ buffer を指す
    p1.text[0] = 'H'; // 共有している buffer を変更するので p2 からも見える
    printf("pointer=%s %s same=%d\n", p1.text, p2.text, p1.text == p2.text);
    p1.text = other; // p1 のアドレスだけを変える。p2.text は buffer のまま
    printf("redirect=%s %s same=%d\n", p1.text, p2.text, p1.text == p2.text);
    return 0;
}
