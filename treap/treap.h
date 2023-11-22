#ifndef _TREAP_H_
#define _TREAP_H_

#include <stdbool.h>

typedef int element_t;
typedef struct node node_t;
typedef struct tree {
    node_t *root;
} tree_t;

tree_t *create_tree();
void delete_tree(tree_t *tree);

void tree_insert(tree_t *tree, element_t value, int priority);
void tree_removal(tree_t *tree, element_t value);

bool tree_search(tree_t *tree, element_t key);

void print_preorder(node_t *root);
void print_inorder(node_t *root);
void print_postorder(node_t *root);
void print_in_width(node_t *root);

int tree_height(node_t *root);

node_t *left_rotate(node_t *unbalanced);
node_t *right_rotate(node_t *unbalanced);

#endif
