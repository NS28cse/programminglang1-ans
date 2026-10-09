/* 第14回 発展3　帰りがけ順と解放の順序（TreeTraversal / versions/destroy_tree.c）
 * 参考コード（演習は構築プログラムを要求していない）。講義の木と同じ形を個別の malloc で作り，
 * destroy_tree で帰りがけ順に解放する。解放する順を見るために destroy_tree に表示を 1 行加えている。
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

void preorder(const Node *p)
{
    if (p == NULL) { return; }
    printf(" %d", p->value);
    preorder(p->left);
    preorder(p->right);
}

/* 前提：共有・循環がなく，各ノードが個別にmallocされている */
void destroy_tree(Node *p)
{
    if (p == NULL) {
        return;
    }
    destroy_tree(p->left);
    destroy_tree(p->right);
    printf(" %d", p->value);           /* 解放する順を見るための表示 */
    free(p);
}

int main(void)
{
    Node *nodes[10] = {NULL};
    for (int i = 0; i < 10; ++i) {
        nodes[i] = malloc(sizeof *nodes[i]);
        if (nodes[i] == NULL) {
            fprintf(stderr, "allocation failed\n");
            for (int j = 0; j < i; ++j) {  /* まだつないでいないので個別に解放する */
                free(nodes[j]);
            }
            return 1;
        }
        nodes[i]->value = i + 1;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }
    nodes[0]->left = nodes[1];  nodes[0]->right = nodes[6];
    nodes[1]->left = nodes[2];  nodes[1]->right = nodes[5];
    nodes[2]->left = nodes[3];  nodes[2]->right = nodes[4];
    nodes[6]->left = nodes[7];  nodes[6]->right = nodes[9];
    nodes[7]->left = nodes[8];

    Node *root = nodes[0];             /* 以後は root が木全体を所有する */
    printf("pre:");
    preorder(root);
    printf("\nfree:");
    destroy_tree(root);
    putchar('\n');
    /* destroy_tree は呼び出し元の root を変えない。
     * nodes[] の各要素にも解放済みのポインタが残るので，以後は nodes[] も使わない。 */
    root = NULL;
    return 0;
}
