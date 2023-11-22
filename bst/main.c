#include "bst.h"
#include <stdio.h>

int main() {

    tree_t *tree = create_tree();

    tree_insert(&tree->root, 5);
    tree_insert(&tree->root, 3);
    tree_insert(&tree->root, 7);
    tree_insert(&tree->root, 9);
    tree_insert(&tree->root, 8);
    tree_insert(&tree->root, 2);

    print_tree(tree, tree->root, "%d");
    print_inorder(tree->root, "%d ");
    printf("\n");

    tree_removal(&tree->root, 5);
    print_tree(tree, tree->root, "%d");

    // print_preorder(tree->root, "%d ");
    // printf("\n");
    print_inorder(tree->root, "%d ");
    printf("\n");
    // print_postorder(tree->root, "%d ");
    // printf("\n");
    // print_in_width(tree->root, "%d ");
    // printf("\n");

    delete_tree(tree, tree->root); 

    return 0;
}
