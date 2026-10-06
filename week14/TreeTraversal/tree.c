/* 第14回 発展2 二分木の3つの走査（TreeTraversal）
 * 講義の tree.c に，部分木からの走査，node_count，tree_height と，
 * 右へ一直線の木との比較を追加した版。
 * ノードはすべて main の局所配列の要素なので free しない。
 */
#include <stdio.h>
#include <stddef.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

/* p は有限で循環のない木（または NULL）を前提とする。NULL の判定を参照より先に置く */
void preorder(const Node *p)
{
    if (p == NULL) { return; }
    printf(" %d", p->value);           /* 自分 → 左 → 右 */
    preorder(p->left);
    preorder(p->right);
}

void inorder(const Node *p)
{
    if (p == NULL) { return; }
    inorder(p->left);
    printf(" %d", p->value);           /* 左 → 自分 → 右 */
    inorder(p->right);
}

void postorder(const Node *p)
{
    if (p == NULL) { return; }
    postorder(p->left);
    postorder(p->right);
    printf(" %d", p->value);           /* 左 → 右 → 自分 */
}

/* 部分木のノード数: 空の木は 0，それ以外は 1 + 左の個数 + 右の個数 */
size_t node_count(const Node *p)
{
    if (p == NULL) { return 0; }
    return 1 + node_count(p->left) + node_count(p->right);
}

/* 高さ = 根から葉までの最長経路に含まれる実ノードの個数（空の木は 0，葉は 1） */
size_t tree_height(const Node *p)
{
    if (p == NULL) { return 0; }
    size_t left = tree_height(p->left);
    size_t right = tree_height(p->right);
    return 1 + (left > right ? left : right); /* 長い方の部分木に自分の 1 を足す */
}

int main(void)
{
    Node nodes[10] = {0};              /* 省略したポインタメンバは NULL になる */
    for (int i = 0; i < 10; ++i) {
        nodes[i].value = i + 1;
    }
    nodes[0].left = &nodes[1];  nodes[0].right = &nodes[6];
    nodes[1].left = &nodes[2];  nodes[1].right = &nodes[5];
    nodes[2].left = &nodes[3];  nodes[2].right = &nodes[4];
    nodes[6].left = &nodes[7];  nodes[6].right = &nodes[9];
    nodes[7].left = &nodes[8];

    printf("pre:");
    preorder(&nodes[0]);
    printf("\nin:");
    inorder(&nodes[0]);
    printf("\npost:");
    postorder(&nodes[0]);
    putchar('\n');

    /* 小さい木で基底条件を確認する（行きがけ順の開始位置だけを変える） */
    printf("pre NULL:");
    preorder(NULL);
    printf("\npre nodes[3]:");
    preorder(&nodes[3]);
    printf("\npre nodes[2]:");
    preorder(&nodes[2]);
    printf("\npre nodes[6]:");
    preorder(&nodes[6]);
    putchar('\n');

    /* 全体・葉・NULL で検証する */
    printf("count: all=%zu leaf=%zu null=%zu\n",
           node_count(&nodes[0]), node_count(&nodes[3]), node_count(NULL));
    printf("height: all=%zu leaf=%zu null=%zu\n",
           tree_height(&nodes[0]), tree_height(&nodes[3]), tree_height(NULL));

    /* 右へ一直線の 10 ノードの木。元の nodes の接続は変えずに別の配列で作る */
    Node line[10] = {0};
    for (int i = 0; i < 10; ++i) {
        line[i].value = i + 1;
    }
    for (int i = 0; i < 9; ++i) {
        line[i].right = &line[i + 1];  /* 最後のノードの right は NULL のまま（循環を作らない） */
    }
    printf("line pre:");
    preorder(&line[0]);
    printf("\nline in:");
    inorder(&line[0]);
    printf("\nline post:");
    postorder(&line[0]);
    printf("\nline count=%zu height=%zu\n", node_count(&line[0]), tree_height(&line[0]));
    return 0;
}
