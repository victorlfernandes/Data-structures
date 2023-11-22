#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    element_t value;
    node_t *left_child;
    node_t *right_child;
};

node_t *create_node(element_t value) {

    node_t *new_node = malloc(sizeof(node_t));

    new_node->value = value;
    new_node->left_child = NULL;
    new_node->right_child = NULL;

    return new_node;
}

tree_t *create_tree() {

    tree_t *tree = malloc(sizeof(tree_t));
    tree->root = NULL;
 
    return tree;
}

void delete_node(node_t *node) {

    assert(node != NULL);

    free(node);
}

void delete_tree(tree_t *tree, node_t *root) {

    if (root != NULL) {
        delete_tree(tree, root->left_child);
        delete_tree(tree, root->right_child);
        delete_node(root);
    }

    if (root == tree->root)
        free(tree);

}

bool empty_tree(tree_t *tree) {

    assert(tree != NULL);

    if (tree->root == NULL)
        return true;
    else
        return false;

}

void print_tree(tree_t *tree, node_t *root, char *format) {

    if (root != NULL) {
        printf(format, root->value);
        printf(" (");
        print_tree(tree, root->left_child, format);
        printf(", ");
        print_tree(tree, root->right_child, format);
        printf(")");
    }
    else
        printf("null");

    if (root == tree->root)
        printf("\n");
}

void print_preorder(node_t *root, char *format) {

    if (root == NULL)
        return;

    printf(format, root->value);
    print_preorder(root->left_child, format); 
    print_preorder(root->right_child, format); 
}

void print_inorder(node_t *root, char *format) {

    if (root == NULL)
        return;

    print_inorder(root->left_child, format); 
    printf(format, root->value);
    print_inorder(root->right_child, format); 
}

void print_postorder(node_t *root, char *format) {

    if (root == NULL)
        return;

    print_postorder(root->left_child, format); 
    print_postorder(root->right_child, format); 
    printf(format, root->value);
}

void print_level(node_t *root, int level, char *format) {

    if (root == NULL)
        return;

    if (level == 1)
        printf(format, root->value);
    else if (level > 1) {
        print_level(root->left_child, level - 1, format);
        print_level(root->right_child, level - 1, format);
    }
}

void print_in_width(node_t *root, char *format) {

    int height = tree_height(root);

    for (int i = 1; i <= height; i++) 
        print_level(root, i, format);
}

int tree_height(node_t *root) {

    if (root == NULL)
        return 0;

    int left_height = 1 + tree_height(root->left_child);
    int right_height = 1 + tree_height(root->right_child);

    return (left_height > right_height) ? left_height : right_height;
}

node_t *tree_search(node_t *root, element_t key) {

    if (root == NULL)
        return NULL;
    
    if (root->value == key)
        return root;

    if (key < root->value)
        return tree_search(root->left_child, key);

    return tree_search(root->right_child, key);
}

void tree_insert(node_t **root, element_t value) {

    // using double pointer because the address is gonna be changed
    // by the function (when assigning with malloc)
    
    if (*root == NULL) {
        // inserting the first element
        *root = create_node(value);
        return;
    }

    if (value == (*root)->value)
        // cannot insert repeated element
        return;

    if (value < (*root)->value) 
        tree_insert(&(*root)->left_child, value);
    else
        tree_insert(&(*root)->right_child, value);
}

void tree_removal(node_t **root, element_t value) {

    if (*root == NULL)
        return;

    else if (value < (*root)->value)
        tree_removal(&(*root)->left_child, value);

    else if (value > (*root)->value)
        tree_removal(&(*root)->right_child, value);

    else {
            
        if ((*root)->left_child == NULL && (*root)->right_child == NULL) {
            free(*root);
            *root = NULL;
            return;
        }

        if ((*root)->left_child == NULL) {
            node_t *aux = *root;
            *root = (*root)->right_child;
            free(aux);
            return;
        }

        if ((*root)->right_child == NULL) {
            node_t *aux = *root;
            *root = (*root)->left_child;
            free(aux);
            return;
        }

        node_t *aux = (*root)->left_child;
        while (aux->right_child != NULL)
            aux = aux->right_child;
        (*root)->value = aux->value;
        tree_removal(&(*root)->left_child, aux->value);
    }
}
