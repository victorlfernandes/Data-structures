#ifndef _BTREE_H_
#define _BTREE_H_

#include <stdbool.h>

typedef int element_t;
typedef struct node node_t;
typedef struct tree {
    node_t *root;
} tree_t;



tree_t *create_tree();
void delete_tree(tree_t *tree, node_t *root);

void print_tree(tree_t *tree, node_t *root, char *format);
void print_preorder(node_t *root, char *format);
void print_inorder(node_t *root, char *format);
void print_postorder(node_t *root, char *format);
void print_in_width(node_t *root, char *format);

bool empty_tree(tree_t *tree);
int tree_height(node_t *root);

node_t *tree_search(node_t *root, element_t key);
node_t *root_search(node_t *root, element_t key);

void create_root(tree_t *tree, element_t value);
void new_left_child(tree_t *tree, element_t value, element_t root);
void new_right_child(tree_t *tree, element_t value, element_t root);
void tree_removal(tree_t *tree, element_t value);

#endif
