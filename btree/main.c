#include "btree.h"
#include <stdio.h>

int main() {

    tree_t *tree = create_tree();

    create_root(tree, 1);

    new_left_child(tree, 2, 1);
    new_right_child(tree, 3, 1);
    new_left_child(tree, 4, 3);
    new_right_child(tree, 5, 3);
    new_left_child(tree, 6, 4);

    print_tree(tree, tree->root, "%d");

    // tree_removal(tree, 1);
    // print_tree(tree, tree->root, "%d");

    print_preorder(tree->root, "%d ");
    printf("\n");
    print_inorder(tree->root, "%d ");
    printf("\n");
    print_postorder(tree->root, "%d ");
    printf("\n");
    print_in_width(tree->root, "%d ");
    printf("\n");

    delete_tree(tree, tree->root); 

    return 0;
}
