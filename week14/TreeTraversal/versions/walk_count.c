/* 第14回 発展2　別解：たどりながら数える node_count と tree_height（TreeTraversal / versions/walk_count.c）
 * 部分木の結果を戻り値で組み合わせる代わりに，行きがけ順にたどりながら，ポインタで渡した 1 つの記録を
 * 更新する（ノードに来るたびに個数を 1 増やす，根からの深さを引数で渡して最大値を覚える）。
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

/* 実ノードに来るたびに *count を 1 増やす（preorder の printf を数える処理に置き換えた形） */
static void count_walk(const Node *p, size_t *count)
{
    if (p == NULL) { return; }
    ++*count;
    count_walk(p->left, count);
    count_walk(p->right, count);
}

size_t node_count(const Node *p)
{
    size_t count = 0;                  /* 呼ぶたびに 0 から数え直す */
    count_walk(p, &count);
    return count;
}

/* depth は p の深さ（根が 1）。実ノードに来るたびに，それまでの最大値 *max と比べて更新する */
static void height_walk(const Node *p, size_t depth, size_t *max)
{
    if (p == NULL) { return; }
    if (depth > *max) {
        *max = depth;
    }
    height_walk(p->left, depth + 1, max);
    height_walk(p->right, depth + 1, max);
}

size_t tree_height(const Node *p)
{
    size_t max = 0;                    /* 空の木では一度も更新されず 0 のまま */
    height_walk(p, 1, &max);
    return max;
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

    /* 全体（nodes[0]）・葉（nodes[3]）・NULL で検証する */
    printf("count: all=%zu nodes[3]=%zu null=%zu\n",
           node_count(&nodes[0]), node_count(&nodes[3]), node_count(NULL));
    printf("height: all=%zu nodes[3]=%zu null=%zu\n",
           tree_height(&nodes[0]), tree_height(&nodes[3]), tree_height(NULL));
    return 0;
}
