#include "treap.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    tree_t *tree = create_tree();

    int n_ops = read_int_until(stdin, NONE_CHAR);

    for (int i = 0; i < n_ops; i++) {

        string_t op = read_until(stdin, ' ');

        if (str_cmp(op, "insercao")) {
            int key = read_int_until(stdin, ' ');
            int priority = read_int_until(stdin, NONE_CHAR);
            tree_insert(tree, key, priority);
        }

        else if (str_cmp(op, "remocao")) {
            int key = read_int_until(stdin, NONE_CHAR);
            tree_removal(tree, key);
        }

        else if (str_cmp(op, "buscar")) {
            int key = read_int_until(stdin, NONE_CHAR);
            printf("%d\n", tree_search(tree, key));
        }

        else if (str_cmp(op, "impressao")) {
            string_t mode = read_str(stdin);
            if (str_cmp(mode, "ordem")) 
                print_inorder(tree->root);
            else if (str_cmp(mode, "posordem")) 
                print_postorder(tree->root);
            else if (str_cmp(mode, "preordem")) 
                print_preorder(tree->root);
            else if (str_cmp(mode, "largura")) 
                print_in_width(tree->root);
            printf("\r\n");
            free(mode);
        }

        free(op);
    }

    delete_tree(tree); 

    return 0;
}
