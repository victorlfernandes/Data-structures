#include "treap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    element_t value;
    int priority;
    node_t *left_child;
    node_t *right_child;
};

// returns the pointer to a new node
node_t *create_node(element_t value, int priority) {

    // allocating
    node_t *new_node = malloc(sizeof(node_t));
    assert(new_node != NULL);

    // assigning
    new_node->value = value;
    new_node->priority = priority;
    new_node->left_child = NULL;
    new_node->right_child = NULL;

    return new_node;
}

// returns the pointer to a new tree
tree_t *create_tree() {

    // allocating
    tree_t *tree = malloc(sizeof(tree_t));
    assert(tree != NULL);

    // assigning
    tree->root = NULL;
 
    return tree;
}

// recursively delete the left and right child, and then the node itself
void delete_nodes(node_t *node) {

    if (node != NULL) {
        delete_nodes(node->left_child);
        delete_nodes(node->right_child);
        free(node);
    }

}

// given the pointer to a tree, delete all of its nodes and the data structure
void delete_tree(tree_t *tree) {

    assert(tree != NULL);

    delete_nodes(tree->root);

    free(tree);
}

// recursively find a leaf node to insert and checks balance after it
// using double pointer because the address is gonna be changed by the function
node_t *insert_node(node_t **node, element_t value, int priority) {

    if (*node == NULL) { 
        // found leaf node to insert
        *node = create_node(value, priority);
        return *node;
    }

    if (value == (*node)->value)
        // cannot insert repeated element
        return NULL;

    if (value < (*node)->value) {
        // searching the leaf node on the left
        (*node)->left_child = insert_node(&(*node)->left_child, value, priority);
        // verifying if the insertion has unbalanced the tree
        if ((*node)->left_child->priority > (*node)->priority)
            (*node) = right_rotate(*node);
    }

    else {
        // searching the leaf node on the right
        (*node)->right_child = insert_node(&(*node)->right_child, value, priority);
        // verifying if the insertion has unbalanced the tree
        if ((*node)->right_child->priority > (*node)->priority)
            (*node) = left_rotate(*node);
    }

    return *node;
}

// given a tree, a value and its priority, creates a new node on the data 
// structure with this info
void tree_insert(tree_t *tree, element_t value, int priority) {

    assert(tree != NULL);

    if (tree_search(tree, value)) {
        // the value already exists on the tree
        printf("Elemento ja existente\n");
        return;
    }

    insert_node(&tree->root, value, priority);    
}

// recursively find the node with the given value and checks balance after it
// using double pointer because the address is gonna be changed by the function
node_t *remove_node(node_t **node, element_t value) {

    if (*node == NULL)
        // the value doesnt exist 
        return *node;

    else if (value < (*node)->value)
        // searching the value on the left
        (*node)->left_child = remove_node(&(*node)->left_child, value);

    else if (value > (*node)->value)
        // searching the value on the right
        (*node)->right_child = remove_node(&(*node)->right_child, value);

    else {
        
        // found the removal node

        // if the node has only the right child, must update the pointer from 
        // its parent's child to the node's right child
        if ((*node)->left_child == NULL) {
            node_t *aux = *node;
            *node = (*node)->right_child;
            free(aux);
        }

        // if the node has only the left child, must update the pointer from 
        // its parent's child to the node's left child
        else if ((*node)->right_child == NULL) {
            node_t *aux = *node;
            *node = (*node)->left_child;
            free(aux);
        }

        // if the node has two children, must rotate it until it becomes
        // a leaf or semi leaf
        
        else if ((*node)->left_child->priority < (*node)->right_child->priority) {
            *node = left_rotate(*node);
            (*node)->left_child = remove_node(&(*node)->left_child, value);
        }

        else {
            *node = right_rotate(*node);
            (*node)->right_child = remove_node(&(*node)->right_child, value);
        }
    }

    return *node;
}

// remove the value from the tree
void tree_removal(tree_t *tree, element_t value) {

    assert(tree != NULL);

    if (!tree_search(tree, value)) {
        // value doesnt exist
        printf("Chave nao localizada\n");
        return;
    }

    remove_node(&tree->root, value);
}

// recursively search a node on tree
node_t *search_node(node_t *node, element_t key) {

    // base case
    if (node == NULL)
        return NULL;
    
    // found the node
    if (node->value == key)
        return node;

    // recursive calls
    if (key < node->value)
        return search_node(node->left_child, key);

    return search_node(node->right_child, key);
}

// search the key on tree
bool tree_search(tree_t *tree, element_t key) {

    assert(tree != NULL);

    node_t *aux = search_node(tree->root, key);

    // unsuccessfull search
    if (aux == NULL)
        return false;
    // successfull search
    else
        return true;
}

// print value and priority of a given node
void print_node(node_t *node) {

    printf("(%d, %d) ", node->value, node->priority);

}

// recursively print tree in preorder traversal
void print_preorder(node_t *root) {

    if (root == NULL)
        return;

    print_node(root);
    print_preorder(root->left_child); 
    print_preorder(root->right_child); 
}

// recursively print tree in order traversal
void print_inorder(node_t *root) {

    if (root == NULL)
        return;

    print_inorder(root->left_child); 
    print_node(root);
    print_inorder(root->right_child); 
}

// recursively print tree in postorder traversal
void print_postorder(node_t *root) {

    if (root == NULL)
        return;

    print_postorder(root->left_child); 
    print_postorder(root->right_child); 
    print_node(root);
}

// recursively print a level of a tree
void print_level(node_t *root, int level) {

    if (root == NULL)
        return;

    if (level == 1)
        print_node(root);
    else if (level > 1) {
        print_level(root->left_child, level - 1);
        print_level(root->right_child, level - 1);
    }
}

// print tree in width traversal
void print_in_width(node_t *root) {

    int height = tree_height(root);

    for (int i = 1; i <= height; i++) 
        print_level(root, i);
}

// returns the height of a tree
int tree_height(node_t *root) {

    if (root == NULL)
        return 0;

    int left_height = 1 + tree_height(root->left_child);
    int right_height = 1 + tree_height(root->right_child);

    return (left_height > right_height) ? left_height : right_height;
}

// simple rotate of an unbalanced node to the left
node_t *left_rotate(node_t *unbalanced) {

    node_t *aux = unbalanced->right_child;
    unbalanced->right_child = aux->left_child;
    aux->left_child = unbalanced;

    return aux;
}

// simple rotate of an unbalanced node to the right
node_t *right_rotate(node_t *unbalanced) {

    node_t *aux = unbalanced->left_child;
    unbalanced->left_child = aux->right_child;
    aux->right_child = unbalanced;

    return aux;
}
