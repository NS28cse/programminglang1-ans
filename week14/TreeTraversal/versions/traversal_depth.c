/* 第14回 発展2　走査の呼び出し回数と深さを数える（TreeTraversal / versions/traversal_depth.c）
 * 講義の木と右へ一直線の木で，行きがけ順の 1 回の走査の呼び出し回数（NULL を含む）と
 * 最大深さ（NULL の呼び出しを含む場合と実ノードだけの場合）を数える。最初の呼び出しを深さ 1 とする。
 */
#include <stdio.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

typedef struct {
    unsigned int calls;                /* NULL を含む呼び出し回数 */
    unsigned int null_calls;
    unsigned int max_depth;            /* NULL の呼び出しを含む最大深さ */
    unsigned int max_real_depth;       /* 実ノードの呼び出しだけの最大深さ */
} Count;

void preorder_count(const Node *p, unsigned int depth, Count *c)
{
    ++c->calls;
    if (depth > c->max_depth) {
        c->max_depth = depth;
    }
    if (p == NULL) {
        ++c->null_calls;
        return;
    }
    if (depth > c->max_real_depth) {
        c->max_real_depth = depth;
    }
    preorder_count(p->left, depth + 1, c);
    preorder_count(p->right, depth + 1, c);
}

int main(void)
{
    Node orig[10] = {0};
    Node line[10] = {0};
    for (int i = 0; i < 10; ++i) {
        orig[i].value = i + 1;
        line[i].value = i + 1;
    }
    orig[0].left = &orig[1];  orig[0].right = &orig[6];
    orig[1].left = &orig[2];  orig[1].right = &orig[5];
    orig[2].left = &orig[3];  orig[2].right = &orig[4];
    orig[6].left = &orig[7];  orig[6].right = &orig[9];
    orig[7].left = &orig[8];
    for (int i = 0; i < 9; ++i) {
        line[i].right = &line[i + 1];  /* 最後のノードの right は NULL のまま */
    }

    Count a = {0, 0, 0, 0};
    preorder_count(&orig[0], 1, &a);
    printf("orig calls=%u null=%u maxdepth(incl NULL)=%u real=%u\n",
           a.calls, a.null_calls, a.max_depth, a.max_real_depth);
    Count b = {0, 0, 0, 0};
    preorder_count(&line[0], 1, &b);
    printf("line calls=%u null=%u maxdepth(incl NULL)=%u real=%u\n",
           b.calls, b.null_calls, b.max_depth, b.max_real_depth);
    return 0;
}
