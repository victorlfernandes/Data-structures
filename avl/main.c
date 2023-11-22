#include "avl.h"
#include <stdio.h>

int main() {

    tree_t *tree = create_tree();

    tree_insert(tree, 5);
    tree_insert(tree, 3);
    tree_insert(tree, 8);
    tree_insert(tree, 2);
    tree_insert(tree, 7);
    tree_insert(tree, 10);
    tree_insert(tree, 15);

    print_tree(tree, tree->root, "%d");
    print_inorder(tree->root, "%d ");
    printf("\n");

    tree_removal(tree, 2);
    print_tree(tree, tree->root, "%d");
    print_inorder(tree->root, "%d ");
    printf("\n");

    // print_preorder(tree->root, "%d ");
    // printf("\n");
    // print_inorder(tree->root, "%d ");
    // printf("\n");
    // print_postorder(tree->root, "%d ");
    // printf("\n");
    // print_in_width(tree->root, "%d ");
    // printf("\n");

    delete_tree(tree, tree->root); 

    return 0;
}
