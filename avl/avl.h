#ifndef _AVL_H_
#define _AVL_H_

#include <stdbool.h>

typedef int element_t;
typedef struct node node_t;
typedef struct tree {
    node_t *root;
} tree_t;

tree_t *create_tree();
void delete_tree(tree_t *tree, node_t *root);

void tree_insert(tree_t *tree, element_t value);
void tree_removal(tree_t *tree, element_t value);

node_t *tree_search(node_t *root, element_t key);

void print_tree(tree_t *tree, node_t *root, char *format);
void print_preorder(node_t *root, char *format);
void print_inorder(node_t *root, char *format);
void print_postorder(node_t *root, char *format);
void print_in_width(node_t *root, char *format);

bool empty_tree(tree_t *tree);
int tree_height(node_t *root);

#endif
