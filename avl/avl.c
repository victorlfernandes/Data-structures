#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    element_t value;
    int bf;
    node_t *left;
    node_t *right;
};

node_t *create_node(element_t value) {

    node_t *new_node = malloc(sizeof(node_t));

    new_node->value = value;
    new_node->bf = 0;
    new_node->left = NULL;
    new_node->right = NULL;

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
        delete_tree(tree, root->left);
        delete_tree(tree, root->right);
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
        print_tree(tree, root->left, format);
        printf(", ");
        print_tree(tree, root->right, format);
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
    print_preorder(root->left, format); 
    print_preorder(root->right, format); 
}

void print_inorder(node_t *root, char *format) {

    if (root == NULL)
        return;

    print_inorder(root->left, format); 
    printf("(");
    printf(format, root->value);
    printf(",%d)", root->bf);
    print_inorder(root->right, format); 
}

void print_postorder(node_t *root, char *format) {

    if (root == NULL)
        return;

    print_postorder(root->left, format); 
    print_postorder(root->right, format); 
    printf(format, root->value);
}

void print_level(node_t *root, int level, char *format) {

    if (root == NULL)
        return;

    if (level == 1)
        printf(format, root->value);
    else if (level > 1) {
        print_level(root->left, level - 1, format);
        print_level(root->right, level - 1, format);
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

    int left_height = 1 + tree_height(root->left);
    int right_height = 1 + tree_height(root->right);

    return (left_height > right_height) ? left_height : right_height;
}

node_t *tree_search(node_t *root, element_t key) {

    if (root == NULL)
        return NULL;
    
    if (root->value == key)
        return root;

    if (key < root->value)
        return tree_search(root->left, key);

    return tree_search(root->right, key);
}

node_t *ll_rotate(node_t *unbalanced) {

    node_t *aux = unbalanced->right;
    unbalanced->right = aux->left;
    aux->left = unbalanced;

    return aux;
}

node_t *rr_rotate(node_t *unbalanced) {

    node_t *aux = unbalanced->left;
    unbalanced->left = aux->right;
    aux->right = unbalanced;

    return aux;
}

node_t *lr_rotate(node_t *unbalanced) {

    unbalanced->left = ll_rotate(unbalanced->left);
    unbalanced = rr_rotate(unbalanced);

    return unbalanced;
}

node_t *rl_rotate(node_t *unbalanced) {

    unbalanced->right = rr_rotate(unbalanced->right);
    unbalanced = ll_rotate(unbalanced);

    return unbalanced;
}
node_t *left_balance(node_t *root, bool *check_balance) {
	printf("Balanceamento para o lado leftuerdo\n");
	
	switch(root->bf) {
		case 1: //altura foi alterada
			root->bf = 0;
			break;
		case 0: //altura nao foi alterada
			root->bf = -1;
			*check_balance = 0;
			break;
		case -1: //altura foi alterada e desbalanceou
			if(root->right->bf <= 0) {
				root = ll_rotate(root);
				if(root->bf == 0) {
					root->left->bf = -1;
					root->bf = 1;
					*check_balance = 0; //altura nao muda apos a rotacao
				} else {
					root->left->bf = 0;
					root->bf = 0;
				}
			} else {
				printf("oi\n");
				root = rl_rotate(root);
				if(root->bf == 1) {
					root->left->bf = 0;
					root->right->bf = -1;
				} else if(root->bf == -1) {
					root->left->bf = 1;
					root->right->bf = 0;
				} else { //root->bf == 0
					root->left->bf = 0;
					root->right->bf = 0;
				}
				root->bf = 0;
			}
	}
	return root;
}


node_t *_left_balance(node_t *root, bool *check_balance) {
    
    printf("balanceamento pra leftuerda\n");

    switch (root->bf) {

        case 1:
            // right height was greater. as we inserted on the 
            // left, it became balanced. no need to rotate
            root->bf = 0;
            // *check_balance = false;
            break;

        case 0:
            // heights were equal. as we inserted on the left,
            // the right became smaller, but this root is still 
            // balanced. no need to rotate, however, must check
            // if this change unbalanced the tree
            root->bf = -1;
            *check_balance = false;
            break;

        case -1:

            // right height was smaller. as we inserted on the 
            // left, this root became unbalanced. so we must rotate
        
            // checking if its a simple or double rotate
            if (root->right->bf <= 0) {
                // equal signs, simple rotation
                root = ll_rotate(root);
                // updating balance factors
                if (root->bf == 0) {
                    root->left->bf = -1;
                    root->bf = 1;
                    *check_balance = false;
                }
                else {
                    root->left->bf = 0;
                    root->bf = 0;
                }
            }
            else {
                // different signs, double rotation
                root = rl_rotate(root);
                // updating balance factors
                if (root->bf == 1) {
                    root->left->bf = 0;
                    root->right->bf = -1;
                }
                else if (root->bf == -1) {
                    root->left->bf = 1;
                    root->right->bf = 0;
                }
                else {
                    root->left->bf = 0;
                    root->right->bf = 0;
                }
                root->bf = 0;
            }
            
            // as we rotated, the tree is balanced, no need to check
            // *check_balance = false;    
            // break;
    }

    return root;
}

node_t *right_balance(node_t *root, bool *check_balance) {

    printf("balanceamento pra righteita\n");

    switch (root->bf) {

        case -1:
            // right height was greater. as we inserted on the 
            // left, it became balanced. no need to rotate
            root->bf = 0;
            // *check_balance = false;
            break;

        case 0:
            // heights were equal. as we inserted on the left,
            // the right became smaller, but this root is still 
            // balanced. no need to rotate, however, must check
            // if this change unbalanced the tree
            root->bf = 1;
            *check_balance = false;
            break;

        case 1:

            // right height was smaller. as we inserted on the 
            // left, this root became unbalanced. so we must rotate
        
            // checking if its a simple or double rotate
            if (root->left->bf >= 0) {
                // equal signs, simple rotation
                root = rr_rotate(root);
                // updating balance factors
                if (root->bf == 0) {
                    root->right->bf = 1;
                    root->bf = -1;
                    *check_balance = false;
                }
                else {
                    root->right->bf = 0;
                    root->bf = 0;
                }
            }
            else {
                // different signs, double rotation
                root = lr_rotate(root);
                // updating balance factors
                if (root->bf == 1) {
                    root->left->bf = 0;
                    root->right->bf = -1;
                }
                else if (root->bf == -1) {
                    root->left->bf = 1;
                    root->right->bf = 0;
                }
                else {
                    root->left->bf = 0;
                    root->right->bf = 0;
                }
                root->bf = 0;
            }
            
            // as we rotated, the tree is balanced, no need to check
            // *check_balance = false;    
            break;
    }

    return root;
}

node_t *insert_avl(node_t *root, element_t value, bool *check_balance) {

    if (root != NULL) {

        if (value < root->value) {
            // going left
            root->left = insert_avl(root->left, value, check_balance);
            // after insertion, must check balance
            if (*check_balance) {

                switch (root->bf) {

                    case -1:
                        // right height was greater. as we inserted on the 
                        // left, it became balanced. no need to rotate
                        root->bf = 0;
                        *check_balance = false;
                        break;

                    case 0:
                        // heights were equal. as we inserted on the left,
                        // the right became smaller, but this root is still 
                        // balanced. no need to rotate, however, must check
                        // if this change unbalanced the tree
                        root->bf = 1;
                        *check_balance = true;
                        break;

                    case 1:

                        // right height was smaller. as we inserted on the 
                        // left, this root became unbalanced. so we must rotate
                    
                        // checking if its a simple or double rotate
                        if (root->left->bf == 1) {
                            // equal signs, simple rotation
                            root = rr_rotate(root);
                            // updating balance factor
                            root->right->bf = 0;
                            root->bf = 0;
                        }
                        else {
                            // different signs, double rotation
                            root = lr_rotate(root);
                            // updating balance factors
                            if (root->bf == -1) {
                                root->left->bf = 1;
                                root->right->bf = 0;
                            }
                            else if (root->bf == 1) {
                                root->left->bf = 0;
                                root->right->bf = -1;
                            }
                            else if (root->bf == 0) {
                                root->left->bf = 0;
                                root->right->bf = 0;
                            }
                            root->bf = 0;
                        }
                        
                        // as we rotated, the tree is balanced, no need to check
                        *check_balance = false;    
                        break;
                }
            }
        }

        else if (value > root->value) {
            // going right
            root->right = insert_avl(root->right, value, check_balance);
            // after insertion, must check balance
            if (*check_balance) {

                switch (root->bf) {

                    case 1:
                        // right height was greater. as we inserted on the 
                        // left, it became balanced. no need to rotate
                        root->bf = 0;
                        *check_balance = false;
                        break;

                    case 0:
                        // heights were equal. as we inserted on the left,
                        // the right became smaller, but this root is still 
                        // balanced. no need to rotate, however, must check
                        // if this change unbalanced the tree
                        root->bf = -1;
                        *check_balance = true;
                        break;

                    case -1:

                        // right height was smaller. as we inserted on the 
                        // left, this root became unbalanced. so we must rotate
                    
                        // checking if its a simple or double rotate
                        if (root->right->bf == -1) {
                            // equal signs, simple rotation
                            root = ll_rotate(root);
                            // updating balance factor
                            root->left->bf = 0;
                        }
                        else {
                            // different signs, double rotation
                            root = rl_rotate(root);
                            // updating balance factors
                            if (root->bf == -1) {
                                root->left->bf = 1;
                                root->right->bf = 0;
                            }
                            else if (root->bf == 1) {
                                root->left->bf = 0;
                                root->right->bf = -1;
                            }
                            else if (root->bf == 0) {
                                root->left->bf = 0;
                                root->right->bf = 0;
                            }
                        }
                        
                        // as we rotated, the tree is balanced, no need to check
                        root->bf = 0;
                        *check_balance = false;    
                        break;
                }
            }

        }

        else {
            printf("cant insert repeated\n");
            return NULL;
        }

    }
    else {
        // found a leaf node to insert
        root = create_node(value);
        *check_balance = true;
    }

    return root;
}

void tree_insert(tree_t *tree, element_t value) {
    bool check_balance = false;
    tree->root = insert_avl(tree->root, value, &check_balance);
}

node_t *search_and_remove(node_t *root, node_t *key_node, bool *check_balance) {
	node_t *aux;

	if(root->right != NULL) {
		root->right = search_and_remove(root->right, key_node, check_balance);
		if(*check_balance == 1)
			root = right_balance(root, check_balance);
	} else {
		key_node->value = root->value;
		aux = root;
		root = root->left;
		free(aux);
		*check_balance = 1;
	}
	
	return root;
}

node_t *_search_and_remove(node_t *root, node_t *key_node, bool *check_balance) {

    if (root->right != NULL) {
        root->right = search_and_remove(root->right, key_node, check_balance);
        if (*check_balance)
            root = right_balance(root, check_balance);
    }
    else {
        key_node->value = root->value;
        node_t *aux = root;
        root = root->left;
        free(aux);
        *check_balance = 1;
    }

    return root;
}

node_t *remove_avl(node_t *root, element_t value, bool *check_balance) {
	node_t *aux;
	
	if(root == NULL) {
		printf("Chave nao foi encontrada!");
		*check_balance = 0;
	} else if(value < root->value) {
		root->left = remove_avl(root->left, value, check_balance);
		if(*check_balance == 1) {
			root = left_balance(root, check_balance);
		}
	} else if(value > root->value) {
		root->right = remove_avl(root->right, value, check_balance);
		if(*check_balance == 1) {
			root = right_balance(root, check_balance);
		}
	} else { //encontrou o elemento
		if(root->right == NULL) {
			aux = root;
			root = root->left;
			free(aux);
			*check_balance = 1;
		} else if(root->left == NULL) {
			aux = root;
			root = root->right;
			*check_balance = 1;
		} else {
			root->left = search_and_remove(root->left, root, check_balance);
			if(*check_balance == 1) 
				root = left_balance(root, check_balance);
		}
	}
	
	return root;
}


node_t *_remove_avl(node_t *root, element_t value, bool *check_balance) {

    if (root == NULL) {
        printf("element doesnt exist\n");
        *check_balance = false;
    }

    else if (value < root->value) {
        root->left = remove_avl(root->left, value, check_balance);
        if (*check_balance)
            root = left_balance(root, check_balance);
    }

    else if (value > root->value) {
        root->right = remove_avl(root->right, value, check_balance);
        if (*check_balance)
            root = right_balance(root, check_balance);
    }

    else {

        if (root->left == NULL && root->right == NULL) {
            node_t *aux = root;
            root = NULL;
            free(aux);
            *check_balance = true;
        }

        else if (root->right == NULL) {
            node_t *aux = root;
            root = root->left;
            free(aux);
            *check_balance = true;
        }

        else if (root->left == NULL) {
            // node_t *aux = root;
            root = root->right;
            // free(aux);
            *check_balance = true;
        }

        else {
            root->left = search_and_remove(root->left, root, check_balance);
            if (*check_balance)
                root =  left_balance(root, check_balance);
        }
    }

    return root;
}

void tree_removal(tree_t *tree, element_t value) {
    bool check_balance = true;
    remove_avl(tree->root, value, &check_balance);
}
