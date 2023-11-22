#include "btree.h"
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

    node_t *node = tree_search(root->left_child, key);
    if (node == NULL)
        node = tree_search(root->right_child, key);

    return node;
}

node_t *root_search(node_t *root, element_t key) {

    if (root == NULL)
        return NULL;
    
    if (root->left_child != NULL && root->left_child->value == key)
        return root;
    
    if (root->right_child != NULL && root->right_child->value == key)
        return root;

    node_t *node = root_search(root->left_child, key);
    if (node == NULL)
        node = root_search(root->right_child, key);

    return node;
}

void create_root(tree_t *tree, element_t value) {

    assert(tree != NULL);

    if (tree->root != NULL)
        return;

    node_t *new_root = create_node(value);
    tree->root = new_root;

}

void new_left_child(tree_t *tree, element_t value, element_t root) {

    assert(tree != NULL);

    node_t *new_node = create_node(value);

    if (empty_tree(tree)) 
        return;

    node_t *node = tree_search(tree->root, root);
    if (node != NULL && node->left_child == NULL) {
        node->left_child = new_node;
        return;
    }

    free(new_node);
}

void new_right_child(tree_t *tree, element_t value, element_t root) {

    assert(tree != NULL);

    node_t *new_node = create_node(value);

    if (empty_tree(tree)) 
        return;

    node_t *node = tree_search(tree->root, root);
    if (node != NULL && node->right_child == NULL) {
        node->right_child = new_node;
        return;
    }

    free(new_node);
}

void tree_removal(tree_t *tree, element_t value) {

    assert(tree != NULL);

    // first step: find the removal node and its parent
    node_t *removal = NULL;
    node_t *parent  = NULL;

    bool is_left_child  = false;
    bool is_right_child = false;

    if (tree->root != NULL && tree->root->value == value) {
        // removal node is the root
        removal = tree->root;
        parent  = NULL;
    }
    else {
        // as it isnt the root, we can find its parent
        parent = root_search(tree->root, value);
        if (parent == NULL)
            // the value we are trying to remove doesnt exist on tree
            removal = NULL;
        else {
            // checking whether the node is a left or right child
            if (parent->left_child != NULL && parent->left_child->value == value) {
                removal = parent->left_child;
                is_left_child = true;
            }
            else {
                removal = parent->right_child;
                is_right_child = true;
            }
        }
    }

    // second step: remove the obtained node

    if (removal == NULL)
        // the node doesnt exist
        return;

    if (removal->left_child == NULL && removal->right_child == NULL) {
        // removing leaf
        if (parent == NULL) 
            // this leaf is also the root, there is only this node on tree
            tree->root = NULL;
        else if (is_left_child) 
            // removing left child of the parent
            parent->left_child = NULL;
        else if (is_right_child) 
            // removing right child of the parent
            parent->right_child = NULL;
        free(removal);
        return;
    }

    // if we got here, it means that the removal node has at least one child
    // so we are gonna swap the node value with his child's and call 
    // recursively the function to the down node
    // this process will repeat until the swap hits a leaf node

    if (removal->left_child != NULL) {
        // swapping with left child
        removal->value = removal->left_child->value;
        removal->left_child->value = value;
    }
    else if (removal->right_child != NULL) {
        // swapping with right child
        removal->value = removal->right_child->value;
        removal->right_child->value = value;
    }
    
    // recursive call
    tree_removal(tree, value); 
}
